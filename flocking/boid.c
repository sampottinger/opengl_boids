/**
 * Name: boid.c
 * Desc: Implementation of structures and logic in boid.h
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "boid.h"

void Boid_init(Boid * boid, float x, float y, float z)
{
    Boid_initFull(boid, x, y, z, BOID_MIN_X, BOID_MIN_Y, BOID_MIN_Z,
        BOID_MAX_X, BOID_MAX_Y, BOID_MAX_Z);
}

void Boid_initFull(Boid * boid, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ)
{
    PhysicsObject_init(&(boid->physicsObject), 1, x, y, z);
    boid->r = START_BOID_ANGLE;
    boid->maxForce = MAX_BOID_FORCE;
    boid->maxSpeed = MAX_BOID_SPEED;
    boid->minX = minX;
    boid->minY = minY;
    boid->minZ = minZ;
    boid->maxX = maxX;
    boid->maxY = maxY;
    boid->maxZ = maxZ;
    boid->seperationWeight = SEPERATION_WEIGHT;
    boid->alignWeight = ALIGN_WEIGHT;
    boid->cohesionWeight = COHESION_WEIGHT;
}

void Boid_setWeights(Boid * boid, float seperationWeight, float alignWeight,
    float cohesionWeight)
{
    boid->seperationWeight = seperationWeight;
    boid->alignWeight = alignWeight;
    boid->cohesionWeight = cohesionWeight;
}

void Boid_setPos(Boid * boid, float x, float y, float z)
{
    boid->physicsObject.position.x = x;
    boid->physicsObject.position.y = y;
    boid->physicsObject.position.z = z;
}

void Boid_step(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, float timestep,
    char ignoreSight)
{
    PhysicsVector * acceleration;
    Boid_respondToFlock(boid, boids, numBoids, obstacles, numObstacles,
        ignoreSight);
    Boid_updatePosition(boid, timestep);

    // Reset acceleration for next sum of forces
    acceleration = &(boid->physicsObject.acceleration);
    acceleration->x = 0;
    acceleration->y = 0;
    acceleration->z = 0;

    PhysicsVector_normalize(&(boid->heading), &(boid->physicsObject.velocity));
}

void Boid_respondToFlock(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, char ignoreSight)
{
    Boid_calculateSeperation(boid, boids, numBoids, obstacles, numObstacles,
        boid->seperationWeight, ignoreSight);
    Boid_calculateAlign(boid, boids, numBoids, boid->alignWeight, ignoreSight);
    Boid_calculateCohesion(boid, boids, numBoids, boid->cohesionWeight,
        ignoreSight);
}

char Boid_inSight(Boid * boid, PhysicsVector * otherPos)
{
    PhysicsVector * curPos = &(boid->physicsObject.position);
    float angle;

    angle = PhysicsVector_angle(curPos, otherPos);
    return angle > IN_SIGHT_MIN && angle < IN_SIGHT_MAX;
}

void Boid_calculateSeperation(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, float weight, char ignoreSight)
{
    int i;
    int count;
    float distance;
    float steeringMagnitude;
    float maxSpeed;
    char inRange;
    char inSight;

    Boid * curFlockBoid;
    PhysicsVector steerVector;
    PhysicsVector diff;

    PhysicsVector * curPos;
    PhysicsVector * otherPos;
    PhysicsVector * steerVectorPtr;
    PhysicsVector * diffPtr;
    PhysicsVector * velocityPtr;

    steerVectorPtr = &steerVector;
    diffPtr = &diff;
    curPos = &(boid->physicsObject.position);

    count = 0;
    PhysicsVector_init(steerVectorPtr, 0, 0, 0);

    // Look for boitds which are too close
    for(i=0; i<numBoids; i++)
    {
        curFlockBoid = boids + i;
        otherPos = &(curFlockBoid->physicsObject.position);

        distance = PhysicsVector_dist(curPos, otherPos);
        inSight = Boid_inSight(boid, otherPos) || ignoreSight;

        // If the distance is larger than 0 but less than desired seperation
        inRange = (distance > 0) && (distance < DESIRED_SEPERATION);

        if(inRange && inSight)
        {
            // Find way to pull current boid away
            PhysicsVector_sub(diffPtr, curPos, otherPos);
            PhysicsVector_normalize(diffPtr, diffPtr);
            PhysicsVector_divScalar(diffPtr, diffPtr, distance);
            PhysicsVector_add(steerVectorPtr, steerVectorPtr, diffPtr);

            // Indicate that a boid was too close
            count++;
        }
    }

    // Look for obstacles which are too close
    for(i=0; i<numObstacles; i++)
    {
        otherPos = (obstacles+i);
        distance = PhysicsVector_dist(curPos, otherPos);

        inRange = (distance > 0) && (distance < DESIRED_SEPERATION*10);
        inSight = Boid_inSight(boid, otherPos);

        if(inRange && inSight)
        {
            // Find way to pull current boid away
            PhysicsVector_sub(diffPtr, curPos, otherPos);
            PhysicsVector_normalize(diffPtr, diffPtr);
            PhysicsVector_divScalar(diffPtr, diffPtr, distance);
            PhysicsVector_add(steerVectorPtr, steerVectorPtr, diffPtr);
            PhysicsVector_add(steerVectorPtr, steerVectorPtr, diffPtr);

            // Indicate that a boid was too close
            count += 2;
        }
    }

    // Average the steering force so the boid doesn't over-compensate
    if(count > 1)
        PhysicsVector_divScalar(steerVectorPtr, steerVectorPtr, count);

    // If the boid has a place to go to increase desired separation, apply a
    // force.
    maxSpeed = boid->maxSpeed;
    steeringMagnitude = PhysicsVector_length(steerVectorPtr);
    velocityPtr = &(boid->physicsObject.velocity);
    // Reynolds orig algorithm: Steering = Desired - Velocity
    if(steeringMagnitude > 0)
    {
        // Calculate appropriate desired steer velocity
        PhysicsVector_normalize(steerVectorPtr, steerVectorPtr);
        PhysicsVector_multScalar(steerVectorPtr, steerVectorPtr, maxSpeed);
        PhysicsVector_sub(steerVectorPtr, steerVectorPtr, velocityPtr);
        PhysicsVector_limit(steerVectorPtr, steerVectorPtr, MAX_BOID_FORCE);

        // Apply force
        PhysicsVector_multScalar(steerVectorPtr, steerVectorPtr, weight);
        PhysicsObject_addForce(&(boid->physicsObject), steerVectorPtr);
    }
}

void Boid_calculateAlign(Boid * boid, Boid * boids, int numBoids, float weight,
    char ignoreSight)
{
    int i;
    int count;
    float distance;
    PhysicsVector nearbySumVelocity;
    PhysicsVector nearbyAvgVelocity;
    PhysicsVector steerForce;
    Boid * curFlockBoidPtr;
    PhysicsVector * curPosPtr;
    PhysicsVector * otherPosPtr;
    PhysicsVector * otherVelPtr;
    char inRange;
    char inSight;

    PhysicsVector * nearbySumVelocityPtr = &nearbySumVelocity;
    PhysicsVector * nearbyAvgVelocityPtr = &nearbyAvgVelocity;
    PhysicsVector * steerForcePtr = &steerForce;
    PhysicsVector * myVelocityPtr = &(boid->physicsObject.velocity);

    PhysicsVector_init(nearbySumVelocityPtr, 0, 0, 0);
    PhysicsVector_init(nearbyAvgVelocityPtr, 0, 0, 0);

    count = 0;

    curPosPtr = &(boid->physicsObject.position);

    // Look for boids which are too close
    for(i=0; i<numBoids; i++)
    {
        curFlockBoidPtr = boids + i;
        otherPosPtr = &(curFlockBoidPtr->physicsObject.position);
        distance = PhysicsVector_dist(curPosPtr, otherPosPtr);

        otherVelPtr = &(curFlockBoidPtr->physicsObject.velocity);

        inRange = (distance > 0) && (distance < MAX_NEIGHBOR_DISTANCE);
        inSight = Boid_inSight(boid, otherPosPtr) || ignoreSight;

        if(inRange && inSight)
        {
            PhysicsVector_add(nearbySumVelocityPtr, nearbySumVelocityPtr,
                otherVelPtr);
            count++;
        }
    }

    // If there were no boids found closeby, we are done
    if(count == 0)
        return;

    // Average the sum position force so the boid doesn't over-compensate
    PhysicsVector_divScalar(nearbyAvgVelocityPtr, nearbySumVelocityPtr, count);
    
    // Calculate steering force
    PhysicsVector_normalize(steerForcePtr, nearbyAvgVelocityPtr);
    PhysicsVector_multScalar(nearbyAvgVelocityPtr, nearbyAvgVelocityPtr,
        boid->maxSpeed);
    PhysicsVector_sub(steerForcePtr, steerForcePtr, myVelocityPtr);
    PhysicsVector_limit(steerForcePtr, steerForcePtr, MAX_BOID_FORCE);

    // Apply force
    PhysicsVector_multScalar(steerForcePtr, steerForcePtr, weight);
    PhysicsObject_addForce(&(boid->physicsObject), steerForcePtr);
}

void Boid_calculateCohesion(Boid * boid, Boid * boids, int numBoids,
    float weight, char ignoreSight)
{
    int i;
    float distance;
    Boid * curFlockBoid;
    PhysicsVector nearbySumPosition;
    PhysicsVector steerForce;
    char inRange;
    char inSight;

    PhysicsVector * nearbySumPositionPtr = &nearbySumPosition;
    PhysicsVector * steerForcePtr = &steerForce;
    PhysicsVector * curPosPtr = &(boid->physicsObject.position);
    PhysicsVector * otherPosPtr;

    int count = 0;

    PhysicsVector_init(nearbySumPositionPtr, 0, 0, 0);
    // Look for boids which are too close
    for(i=0; i<numBoids; i++)
    {
        curFlockBoid = boids + i;
        otherPosPtr = &(curFlockBoid->physicsObject.position);
        distance = PhysicsVector_dist(curPosPtr, otherPosPtr);

        inRange = (distance > 0) && (distance < MAX_NEIGHBOR_DISTANCE);
        inSight = Boid_inSight(boid, otherPosPtr) || ignoreSight;

        if(inRange && inSight)
        {
            PhysicsVector_add(nearbySumPositionPtr, nearbySumPositionPtr,
                otherPosPtr);
            count++;
        }
    }

    // If no nearby boids found
    if(count == 0)
        return;

    // Calculate steering force
    PhysicsVector_divScalar(steerForcePtr, nearbySumPositionPtr, count);

    // Steer towards the center
    Boid_steerTowardsLocation(boid, steerForcePtr, weight);
}

void Boid_steerTowardsLocation(Boid * boid, PhysicsVector * location,
    float weight)
{
    PhysicsVector directionToDesired;
    PhysicsVector steeringForce;
    PhysicsVector * directionToDesiredPtr = &directionToDesired;
    PhysicsVector * curLocationPtr = &(boid->physicsObject.position);
    PhysicsVector * curVelocityPtr = &(boid->physicsObject.velocity);
    PhysicsVector * steeringForcePtr = &steeringForce;

    PhysicsVector_distVector(directionToDesiredPtr, location, curLocationPtr);

    PhysicsVector_normalize(directionToDesiredPtr, directionToDesiredPtr);
    PhysicsVector_multScalar(directionToDesiredPtr, directionToDesiredPtr,
        boid->maxSpeed);

    PhysicsVector_sub(steeringForcePtr, directionToDesiredPtr, curVelocityPtr);
    PhysicsVector_limit(steeringForcePtr, steeringForcePtr, MAX_BOID_FORCE);

    PhysicsVector_multScalar(steeringForcePtr, steeringForcePtr, weight);
    PhysicsObject_addForce(&(boid->physicsObject), steeringForcePtr);
}

void Boid_updatePosition(Boid * boid, float timestep)
{
    PhysicsObject * physicsObject = &(boid->physicsObject);
    PhysicsVector * velocity;

    // Apply acceleration to velocity
    PhysicsObject_updateVelocity(physicsObject, timestep);

    // Limit velocity
    velocity = &(physicsObject->velocity);
    PhysicsVector_limit(velocity, velocity, boid->maxSpeed);

    // Apply velocity to position
    PhysicsObject_updatePosition(physicsObject, timestep);

    // Wrap on borders
    Boid_wrapOnBorders(boid);
}

void Boid_wrapOnBorders(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    PhysicsVector * velocity = &(boid->physicsObject.velocity);
    
    if(position->x < boid->minX)
    {
        position->x = boid->minX;
        velocity->x = -velocity->x;
    }

    if(position->y < boid->minY) 
    {
        position->y = boid->minY;
        velocity->y = -velocity->y;
    }

    if(position->z < boid->minZ) 
    {
        position->z = boid->minZ;
        velocity->z = -velocity->z;
    }

    if(position->x > boid->maxX)
    {
        position->x = boid->maxX;
        velocity->x = -velocity->x;
    }

    if(position->y > boid->maxY)
    {
        position->y = boid->maxY;
        velocity->y = -velocity->y;
    }

    if(position->z > boid->maxZ)
    {
        position->z = boid->maxZ;
        velocity->z = -velocity->z;
    }
}

float Boid_getX(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->x;
}

float Boid_getY(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->y;
}

float Boid_getZ(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->z;
}

void Boid_setVel(Boid * boid, float x, float y, float z)
{
    PhysicsVector * velocity = &(boid->physicsObject.velocity);
    velocity->x = x;
    velocity->y = y;
    velocity->z = z;
}
