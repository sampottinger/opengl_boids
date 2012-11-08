/**
 * Name: physics.c
 * Desc: Implementation of physics.h functions.
 * Auth: Sam Pottinger
**/

#include "physics.h"

void PhysicsVector_Add(PhysicsVector * dest, PhysicsVector * op1, 
    PhysicsVector * op2)
{
    dest->x = op1->x + op2->x;
    dest->y = op1->y + op2->y;
    dest->z = op1->z + op2->z;
}

void PhysicsObject_AddForce(PhysicsObject * physicsObject,
    PhysicsVector * force)
{
    PhysicsVector * sumForce = &(physicsObject->sumForce);
    PhysicsVector_Add(sumForce, sumForce, force);
}