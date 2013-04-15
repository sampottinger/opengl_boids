/**
 * Desc: Header file for a single boid in a boids birds implementation.
 * Auth: Sam Pottinger
 * Refr: "The Nature of Code" by Daniel Shiffman chapter 6
 * Licn: GNU GPL v2
**/

#ifndef FINAL_BOID_HEADER
#define FINAL_BOID_HEADER

#include "constants.h"
#include "physics.h"

/**
 * Name: Boid
 * Desc: Data structure representing a single boid bird.
**/
typedef struct
{
    PhysicsObject physicsObject;
    PhysicsVector heading;
    float r;
    float maxForce;
    float maxSpeed;
    int minX;
    int minY;
    int minZ;
    int maxX;
    int maxY;
    int maxZ;
    float seperationWeight;
    float alignWeight;
    float cohesionWeight;
} Boid;

/**
 * Name: Boid_init(Boid * boid, float x, float y, float z)
 * Desc: Contructor for a Boid
 * Para: boid, The Boid object to initalize
 *       x, The starting x position of the boid.
 *       y, The starting y position of the boid.
 *       z, The starting z position of the boid.
**/
void Boid_init(Boid * boid, float x, float y, float z);

void Boid_randomForce(Boid * boid);

void Boid_setPos(Boid * boid, float x, float y, float z);

/**
 * Name: Boid_initFull
 * Desc: Full constructor for a Boid with custom position bounds
 * Para: boid, The Boid object to initalize
 *       x, The starting x position of the boid.
 *       y, The starting y position of the boid.
 *       z, The starting z position of the boid.
 *       minX, The minimum allowable x position of a boid.
 *       minY, The minimum allowable y position of a boid.
 *       minZ, The minimum allowable z position of a boid.
 *       maxX, The minimum allowable x position of a boid.
 *       maxY, The minimum allowable y position of a boid.
 *       maxZ, The minimum allowable z position of a boid.
**/
void Boid_initFull(Boid * boid, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ);

/**
 * Name: Boid_step
 * Desc: Update the position of a boid in relation to all other boids.
 * Para: boid, The Boid to update.
 *       boids, The other Boids in the simulation.
 *       numBoids, The number of boids in boids.
 *       timestep, The time to apply the resulting force for.
**/
void Boid_step(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, float timestep,
    char ignoreSight);

/**
 * Name: Boid_respondToFlock
 * Desc: Have other boids affect this boid.
 * Para: boid, The Boid to update
 *       boids, The other Boids in the simulation.
 *       numBoids, The number of boids in boids.
**/
void Boid_respondToFlock(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, char ignoreSight);

/**
 * Name: Boid_calculateSeperation
 * Desc: Calculate forces on this Boid as a result of being too close
 * Para: boid, The Boid to update.
 *       boids, The other Boids in the simulation.
 *       numBoids, The number of boids in boids.
 *       weight, The artifical weight to apply to the seperation force.
**/
void Boid_calculateSeperation(Boid * boid, Boid * boids, int numBoids,
    PhysicsVector * obstacles, int numObstacles, float weight,
    char ignoreSight);

/**
 * Name: Boid_calculateAlign
 * Desc: Calculate forces on this Boid that force it to align with others close
 *       by.
 * Para: boid, The Boid to update.
 *       boids, The 
 *       weight, The artifical weight to apply to the seperation force.
**/
void Boid_calculateAlign(Boid * boid, Boid * boids, int numBoids, float weight,
    char ignoreSight);

/**
 * Name: Boid_calculateCohesion
 * Desc: Calculate forces on this Boid that force it to stay close to other
 *       Boids.
 * Para: boid, The Boid to update.
 *       boids, The other Boids in the simulation.
 *       numBoids, The number of boids in boids.
 *       weight, The artificial weight to apply to the cohesion force.
**/
void Boid_calculateCohesion(Boid * boid, Boid * boids, int numBoids,
    float weight, char ignoreSight);

/**
 * Name: Boid_steerTowardsLocation
 * Desc: Apply force to Boid that directs it towards a location.
 * Para: boid, The Boid to update.
 *       location, The location to go towards.
 *       weight, The artificial weight to apply to the cohesion force.
**/
void Boid_steerTowardsLocation(Boid * boid, PhysicsVector * location,
    float weight);

/**
 * Name: Boid_updatePosition
 * Desc: Update the position of a boid given a timestep and its currently
 *       applied forces.
 * Para: boid, The Boid to update.
 *       timestep, The amount of time to apply current forces for.
**/
void Boid_updatePosition(Boid * boid, float timestep);

/**
 * Name: Boid_wrapOnBorders
 * Desc: If the current boid is outside of its physics bounds, will wrap around.
 * Para: boid, The Boid to wrap.
**/
void Boid_wrapOnBorders(Boid * boid);

/**
 * Name: Boid_getX(Boid * boid)
 * Desc: Get the current global x position of this boid.
 * Para: boid, The boid to get the current x position for.
**/
float Boid_getX(Boid * boid);

/**
 * Name: Boid_getY(Boid * boid)
 * Desc: Get the current global y position of this boid.
 * Para: boid, The boid to get the current y position for.
**/
float Boid_getY(Boid * boid);

/**
 * Name: Boid_getZ(Boid * boid)
 * Desc: Get the current global z position of this boid.
**/
float Boid_getZ(Boid * boid);

/**
 * Name: Boid_setVel(Boid * boid, float x, float y, float z)
 * Desc: Artifically set the current velocity for this boid.
 * Para: boid, The boid to set the velocity.
 *       x, The new x component of this boid's velocity.
 *       y, The new y component of this boid's velocity.
 *       z, The new z component of this boid's velocity.
**/
void Boid_setVel(Boid * boid, float x, float y, float z);

/**
 * Name: Boid_setWeights(Boid * boid, float seperationWeight, float alignWeight,
 *          float cohesionWeight)
 * Desc: Set how much each of the forces on a boid affects it.
 * Para: boid, The boid to set weights for.
 *       seperationWeight, How much the boid will try to distance itself from
 *          other boids.
 *       alignWeight, How much the boid will try to orient itself like the boids
 *          around it.
 *       cohesionWeight, How much a boid will try to stay with other boids close
 *          by.
**/
void Boid_setWeights(Boid * boid, float seperationWeight, float alignWeight,
    float cohesionWeight);

char Boid_inSight(Boid * boid, PhysicsVector * otherPos);

#endif