/**
 * Name: constants.h
 * Desc: Structures and logic for executing the boids flocking simulation on a
 *       collection of birds / boids.
 * Refr: "The Nature of Code" by Daniel Shiffman chapter 6
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef flock_HEADER
#define flock_HEADER

#include "bird.h"

/**
 * Name: Flock
 * Desc: Collection of birds with boid flocking behavior who exert boid flocking
 *       forces on each other.
**/
typedef struct
{
    Bird * birds;
    Boid * boids;
    int numBirds;
} Flock;

/**
 * Name: flock_init(Flock * flock, int numBirds)
 * Desc: Create a new flock of given size.
 * Para: flock, The flock to initalize.
 *       numBirds, The number of birds that this flock needs to hold.
**/
void flock_init(Flock * flock, int numBirds);

/**
 * Name: flock_draw(Flock * flock)
 * Desc: Draw the birds in this flock.
 * Para: flock, The flock whose birds need to be drawn.
**/
void flock_draw(Flock * flock);

/**
 * Name: flock_getBird(Flock * flock, int index)
 * Desc: Get a bird from this flock by index / numerical ID.
 * Para: flock, The flock to get the bird from.
 *       index, The index of the bird to get.
**/
Bird * flock_getBird(Flock * flock, int index);

/**
 * Name: flock_step(Flock * flock)
 * Desc: Update all of the birds in this flock via boids flocking behavior.
 * Para: flock, The flock to run flocking behavior for.
**/
void flock_step(Flock * flock, PhysicsVector * obstacles, int numObstacles);

/**
 * Name: flock_setWeights(Flock * flock, float seperationWeight,
 *       float alignWeight, float cohesionWeight)
 * Desc: Set the weights of each of the forces in flocking behavior for all of
 *       the birds in this flock.
 * Para: flock, The flock to set weights for.
 *       seperationWeight, How much the birds in this flock will try to seperate
 *          from each other.
 *       alignWeight, How much the birds in this flock should try to align their
 *          orientation / direction of travel.
 *       cohesionWeight, How much the birds in this flock will try to stay
 *          together.
**/
void flock_setWeights(Flock * flock, float seperationWeight, float alignWeight,
    float cohesionWeight);

#endif