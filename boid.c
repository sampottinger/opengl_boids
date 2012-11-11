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
}

void Boid_step(Boid * boid, Boid * boids, int numBoids, float timestep)
{
    PhysicsVector * acceleration;
    Boid_respondToFlock(boid, boids, numBoids);
    Boid_updatePosition(boid, timestep);

    // Reset acceleration for next sum of forces
    acceleration = &(boid->physicsObject.acceleration);
    acceleration->x = 0;
    acceleration->y = 0;
    acceleration->z = 0;
}

void Boid_respondToFlock(Boid * boid, Boid * boids, int numBoids)
{
    Boid_calculateSeperation(boid, boids, numBoids, SEPERATION_WEIGHT);
    Boid_calculateAlign(boid, boids, numBoids, ALIGN_WEIGHT);
    Boid_calculateCohesion(boid, boids, numBoids, COHESION_WEIGHT);
}

void Boid_calculateSeperation(Boid * boid, Boid * boids, int numBoids,
    float weight)
{
    int i;
    int count;
    float distance;
    float steeringMagnitude;
    float maxSpeed;

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

        // If the distance is larger than 0 but less than desired seperation
        if((distance > 0) && (distance < DESIRED_SEPERATION))
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

void Boid_calculateAlign(Boid * boid, Boid * boids, int numBoids, float weight)
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

        if((distance > 0) && (distance < MAX_NEIGHBOR_DISTANCE))
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
    float weight)
{
    int i;
    float distance;
    Boid * curFlockBoid;
    PhysicsVector nearbySumPosition;
    PhysicsVector steerForce;

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

        if((distance > 0) && (distance < MAX_NEIGHBOR_DISTANCE))
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
    float r = boid->r;

    if(position->x < boid->minX - r)
        position->x = boid->maxX + r;

    if(position->y < boid->minY - r) 
        position->y = boid->maxY + r;

    if(position->x > boid->maxX + r)
        position->x = boid->minX - r;

    if(position->y > boid->maxY + r)
        position->y = boid->minY - r;
}