/**
 * Name: physics.h
 * Desc: Header file for basic physics constructs like position and forces.
 * Auth: Sam Pottinger
**/

#ifndef FINAL_PHYSICS_HEADER
#define FINAL_PHYSICS_HEADER

#include <vector>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/**
 * Name: PhysicsVector
 * Desc: A simple 3 component vector with components named x, y, and z.
**/
typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} PhysicsVector;

/**
 * Name: PhysicsObject
 * Desc: An object that has a position and veclocity which can have forces
 *       applied to it.
 * Auth: Sam Pottinger
**/
typedef struct
{
    PhysicsVector location;
    PhysicsVector velocity;
    PhysicsVector sumForce;
} PhysicsObject;

/**
 * Name: PhysicsVector_Add
 * Desc: Adds two PhysicsVectors to each other and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be added to op2.
 *       op2, The vector taht will be added to op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_Add(
    PhysicsVector * dest,
    PhysicsVector * op1,
    PhysicsVector * op2
);

/**
 * Name: PhysicsObject_AddForce
 * Desc: Adds a force to a PhysicsObject
 * Para: physicsObject, The object to add the force to.
 *       force, The force to add.
**/
void PhysicsObject_AddForce(
    PhysicsObject * physicsObject,
    PhysicsVector * force
);

#endif