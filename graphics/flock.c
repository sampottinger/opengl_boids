/**
 * Name: flock.c
 * Desc: Implementation of structures and logic for a collection of flocking
 *       birds as defined in flock.h
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "flock.h"

void Flock_init(Flock * flock, int numBirds)
{
    int i;

    flock->birds = malloc(sizeof(Bird) * numBirds);
    flock->boids = malloc(sizeof(Boid) * numBirds);
    flock->numBirds = numBirds;

    for(i=0; i<numBirds; i++)
    {
        Boid_init(flock->boids+i, 0, 0, 0);
        bird_initBird(flock->birds+i, flock->boids+i);
        bird_randomizePosition(flock->birds+i);
    }
}

Bird * Flock_getBird(Flock * flock, int index)
{
    return flock->birds+index;
}

void Flock_draw(Flock * flock)
{
    int i;
    int totalBirds = flock->numBirds;
    for(i=0; i<totalBirds; i++)
        bird_draw(flock->birds+i);
}

void Flock_step(Flock * flock)
{
    Bird * curBird;
    Boid * flockBoids;
    int i;
    int totalBirds;

    totalBirds = flock->numBirds;
    flockBoids = flock->boids;
    for(i=0; i<totalBirds; i++)
    {
        curBird = Flock_getBird(flock, i);
        bird_step(curBird, flockBoids, totalBirds, 1);
        bird_animate(curBird);
    }
}

void Flock_setWeights(Flock * flock, float seperationWeight, float alignWeight, float cohesionWeight)
{
    int i;
    int totalBirds = flock->numBirds;
    for(i=0; i<totalBirds; i++)
    {
        Bird * bird = flock->birds+i;
        Boid_setWeights(bird->boid, seperationWeight, alignWeight, cohesionWeight);
    }
}
