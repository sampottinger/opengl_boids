/**
 * Name: physics.c
 * Desc: Implementation of physics.h functions.
 * Auth: Sam Pottinger
**/

#include "physics.h"

void PhysicsVector_init(PhysicsVector * vector, GLfloat x, GLfloat y, GLfloat z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void PhysicsObject_init(PhysicsObject * obj, float mass, GLfloat x, GLfloat y,
    GLfloat z)
{
    obj->mass = mass;
    PhysicsVector_init(&(obj->position), x, y, z);
    PhysicsVector_init(&(obj->acceleration), 0, 0, 0);
    PhysicsVector_init(&(obj->velocity), 0, 0, 0);
}

void PhysicsVector_add(PhysicsVector * dest, PhysicsVector * op1, 
    PhysicsVector * op2)
{
    dest->x = op1->x + op2->x;
    dest->y = op1->y + op2->y;
    dest->z = op1->z + op2->z;
}

void PhysicsVector_sub(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2)
{
    dest->x = op1->x - op2->x;
    dest->y = op1->y - op2->y;
    dest->z = op1->z - op2->z;
}

int PhysicsVector_eq(PhysicsVector * op1, PhysicsVector * op2,
    float tollerance)
{
    if(fabs(op1->x - op2->x) > tollerance)
        return 0;
    if(fabs(op1->y - op2->y) > tollerance)
        return 0;
    if(fabs(op1->z - op2->z) > tollerance)
        return 0;

    return 1;
}

void PhysicsVector_mult(PhysicsVector * dest, PhysicsVector * op1, 
    PhysicsVector * op2)
{
    dest->x = op1->x * op2->x;
    dest->y = op1->y * op2->y;
    dest->z = op1->z * op2->z;
}

void PhysicsVector_multScalar(PhysicsVector * dest, PhysicsVector * op1,
    float op2)
{
    PhysicsVector scalarVector;
    PhysicsVector * scalarVectorPtr = &scalarVector;

    PhysicsVector_init(scalarVectorPtr, op2, op2, op2);
    PhysicsVector_mult(dest, op1, scalarVectorPtr);
}

void PhysicsVector_div(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2)
{
    dest->x = op1->x / op2->x;
    dest->y = op1->y / op2->y;
    dest->z = op1->z / op2->z;
}

void PhysicsVector_divScalar(PhysicsVector * dest, PhysicsVector * op1,
    float op2)
{
    PhysicsVector scalarVector;
    PhysicsVector * scalarVectorPtr = &scalarVector;

    PhysicsVector_init(scalarVectorPtr, op2, op2, op2);
    PhysicsVector_div(dest, op1, scalarVectorPtr);
}

float PhysicsVector_length(PhysicsVector * target)
{
    double total = 0;

    total += pow(target->x, 2);
    total += pow(target->y, 2);
    total += pow(target->z, 2);

    return (float)sqrt(total);
}

void PhysicsVector_distVector(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2)
{
    dest->x = op1->x - op2->x;
    dest->y = op1->y - op2->y;
    dest->z = op1->z - op2->z;
}

float PhysicsVector_dist(PhysicsVector * op1, PhysicsVector * op2)
{
    PhysicsVector distanceVector;
    PhysicsVector * distanceVectorPtr = &distanceVector;

    PhysicsVector_distVector(distanceVectorPtr, op1, op2);

    return PhysicsVector_length(distanceVectorPtr);
}

void PhysicsVector_normalize(PhysicsVector * target, PhysicsVector * op)
{
    float magnitude = PhysicsVector_length(op);
    PhysicsVector_divScalar(target, op, magnitude);
}

void PhysicsVector_limit(PhysicsVector * target, PhysicsVector * op,
    float limit)
{
    float curMagnitude = PhysicsVector_length(op);

    if(curMagnitude <= limit)
        return;

    PhysicsVector_normalize(target, op);
    PhysicsVector_multScalar(target, target, limit);
}

void PhysicsObject_addForce(PhysicsObject * physicsObject,
    PhysicsVector * force)
{
    PhysicsVector deltaAcceleration;
    PhysicsVector * deltaAccelerationPtr = &deltaAcceleration;

    PhysicsVector_multScalar(deltaAccelerationPtr, force, physicsObject->mass);

    PhysicsVector * sumAccelerationPtr = &(physicsObject->acceleration);
    PhysicsVector_add(sumAccelerationPtr, sumAccelerationPtr,
        deltaAccelerationPtr);
}

void PhysicsObject_updateVelocity(PhysicsObject * physicsObject, float timeDur)
{
    PhysicsVector * accelerationPtr;
    PhysicsVector deltaVelocity;
    PhysicsVector * deltaVelocityPtr = &deltaVelocity;

    PhysicsVector * velocityPtr = &(physicsObject->velocity);

    // Calculate change in velocity
    accelerationPtr = &(physicsObject->acceleration);
    PhysicsVector_multScalar(deltaVelocityPtr, accelerationPtr, timeDur);

    // Add change in velocity
    PhysicsVector_add(velocityPtr, velocityPtr, deltaVelocityPtr);
}

void PhysicsObject_updatePosition(PhysicsObject * physicsObject, float timeDur)
{
    PhysicsVector * accelerationPtr;
    PhysicsVector deltaVelocity;
    PhysicsVector * deltaVelocityPtr = &deltaVelocity;

    PhysicsVector * velocityPtr = &(physicsObject->velocity);
    PhysicsVector * positionPtr = &(physicsObject->position);

    // Calculate change in velocity
    accelerationPtr = &(physicsObject->acceleration);
    PhysicsVector_multScalar(deltaVelocityPtr, accelerationPtr, timeDur);

    // Add change in velocity
    PhysicsVector_add(positionPtr, velocityPtr, deltaVelocityPtr);
}
