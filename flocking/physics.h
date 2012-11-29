/**
 * Name: physics.h
 * Desc: Header file for basic physics constructs like position and forces.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef FINAL_PHYSICS_HEADER
#define FINAL_PHYSICS_HEADER

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>

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
 * Desc: An object that has a position, acceleration, and veclocity which can
 *       have forces applied to it.
 * Auth: Sam Pottinger
**/
typedef struct
{
    float mass;
    PhysicsVector position;
    PhysicsVector acceleration;
    PhysicsVector velocity;
} PhysicsObject;

/**
 * Name: PhysicsVector_init
 * Desc: Constructor for PhysicsVector
 * Para: vector, The vector to initalize
 *       x, The x component of the new vector
 *       y, The y component of the new vector
 *       z, The z component of the new vector
**/
void PhysicsVector_init(PhysicsVector * vector, GLfloat x, GLfloat y, GLfloat z);

/**
 * Name: PhysicsVector_add
 * Desc: Adds two PhysicsVectors to each other and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be added to op2.
 *       op2, The vector that will be added to op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_add(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2);

/**
 * Name: PhysicsVector_sub
 * Desc: Subtracts op2 vector from op1 vector and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the subtraction.
 *       op1, The vector that be subtracted from.
 *       op2, The vector that will be subtracted from op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_sub(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2);

/**
 * Name: PhysicsVector_eq
 * Desc: Determines if two vectors are equal to each other within tollerance.
 * Para: op1, The first vector to compare.
 *       op2, The second vector to compare.
 *       tollerance, The amount of difference allowed between the two to still
 *           be considered equal.
 * Retr: 1 if equal 0 otherwise.
**/
int PhysicsVector_eq(PhysicsVector * op1, PhysicsVector * op2,
    float tollerance);

/**
 * Name: PhysicsVector_mult
 * Desc: Multiplies two PhysicsVectors to each other and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be multiplied with op2.
 *       op2, The vector that will be multiplied with op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_mult(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2);

/**
 * Name: PhysicsVector_multScalar
 * Desc: Multiplies a PhysicsVector by a scalar and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be multiplied with op2.
 *       op2, The scalar that will be multiplied with op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_multScalar(PhysicsVector * dest, PhysicsVector * op1,
    float op2);

/**
 * Name: PhysicsVector_div
 * Desc: Divides a PhysicsVectors from another and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be divided by op2.
 *       op2, The vector that will be divide op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_div(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2);

/**
 * Name: PhysicsVector_divScalar
 * Desc: Divides a PhysicsVector by a scalar and saves the result to another
 *       result vector.
 * Para: dest, The vector which will hold the result of the addition.
 *       op1, The vector that will be multiplied with op2.
 *       op2, The scalar that will be multiplied with op1.
 * Note: This allows any subset of op1 == op2 == dest by memory address.
**/
void PhysicsVector_divScalar(PhysicsVector * dest, PhysicsVector * op1,
    float op2);

/**
 * Name: PhysicsVector_length
 * Desc: Find the magnitude of the given vector.
 * Para: target, The vector to find the magnitude of.
 * Retr: Magnitude of the given vector;
**/
float PhysicsVector_length(PhysicsVector * target);

/**
 * Name: PhysicsVector_distVector
 * Desc: Find the straight line between op1 and op2
 * Para: dest, Where to put the dimensions of the resulting straight line.
 *       op1, Where to start calculating the distance.
 *       op2, Where to end the straight line.
**/
void PhysicsVector_distVector(PhysicsVector * dest, PhysicsVector * op1,
    PhysicsVector * op2);

/**
 * Name: PhysicsVector_dist
 * Desc: Find the straight line distance between op1 and op2
 * Para: op1, Where to start calculating the distance.
 *       op2, Where to end the straight line.
 * Retr: Length of straight line between op1 and op2
**/
float PhysicsVector_dist(PhysicsVector * op1, PhysicsVector * op2);

/**
 * Name: PhysicsVector_normalize
 * Desc: Normalizes the given vector.
 * Para: target, Where to save the normalized vector.
 *       op, The vector to normalize.
 * Note: target can == op by address.
**/
void PhysicsVector_normalize(PhysicsVector * target, PhysicsVector * op);

/**
 * Name: PhysicsVector_limit
 * Desc: Limits the given vector's magnitude and scales it necessary;
 * Para: target, Where to save the limited vector.
 *       op, The vector to limit.
 *       limit, The max magnitude.
 * Note: target can == op by address.
**/
void PhysicsVector_limit(PhysicsVector * target, PhysicsVector * op,
    float limit);

/**
 * Name: PhysicsObject_init
 * Desc: Constructor for PhysicsObject that gives it a sum of forces = 0 in all
 *       components.
 * Para: object, The PhysicsObject to initalize
 *       mass, The mass of the new object
 *       x, The starting x position.
 *       y, The starting y position.
 *       z, The starting z position.
**/
void PhysicsObject_init(PhysicsObject * obj, float mass, GLfloat x, GLfloat y,
    GLfloat z);

/**
 * Name: PhysicsObject_addForce
 * Desc: Adds a force to a PhysicsObject
 * Para: physicsObject, The object to add the force to.
 *       force, The force to add.
**/
void PhysicsObject_addForce(PhysicsObject * physicsObject, 
    PhysicsVector * force);

/**
 * Name: PhysicsObject_updateVelocity
 * Desc: Update the velocity of the given object with its current sum
 *       acceleration.
 * Para: physicsObject, The object whose velocity should be updated.
 *       time, The time in steps that the velocity should be accelerated over.
 * Note: Although calculated on time steps, the acceleration is updated
 *       instantaneously.
**/
void PhysicsObject_updateVelocity(PhysicsObject * physicsObject, float time);

/**
 * Name: PhysicsObject_updatePosition
 * Desc: Updates the location of the given object with its current sum velocity
 *       but does not update the velocity (see PhysicsObject_updateVelocity).
 * Para: physicsObject, The object whose position should be updated.
 *       time, The time in steps the velocity should be applied over.
 * Note: Will apply the velocity over the given time duration but position will
 *       be updated instantaneously.
**/
void PhysicsObject_updatePosition(PhysicsObject * physicsObject, float time);

#endif