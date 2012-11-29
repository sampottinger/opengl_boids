/**
 * Name: bird.h
 * Desc: Header file for 3D bird model that has Boid behavior.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef BIRD_INC_GUARD
#define BIRD_INC_GUARD

#define BEAK_INNER_SIDE_LEN 1.0
#define BEAK_SHIFT 0.5
#define BEAK_OUTER_SIDE_LEN 2.0
#define BIRD_LENGTH 10.0
#define BIRD_HEIGHT 4.0
#define BEAK_LENGTH 4.0
#define NUM_HEAD_RADI 5

#define HEAD_END_RAD 4.0
#define HEAD_END_SHIFT 1
#define HEAD_END_LENGTH 2.0

#define HEAD_INNER_RAD 4.5
#define HEAD_INNER_X_SHIFT 2.1
#define HEAD_INNER_SHIFT 0.25
#define HEAD_INNER_LENGTH 2.0

#define HEAD_START_RAD 3.0
#define HEAD_START_SHIFT 1.25
#define HEAD_START_X_SHIFT 2.20
#define HEAD_START_LENGTH 2.0

#define BODY_FRONT_RAD 3.5
#define BODY_FRONT_SHIFT 0.25
#define BODY_FRONT_X_SHIFT 1.5
#define BODY_FRONT_LENGTH 2.5

#define BODY_MID_RAD 4
#define BODY_MID_LENGTH 4
#define BODY_MID_X_SHIFT 1.75
#define BODY_MID_SHIFT 1

#define BODY_BACK_RAD 4
#define BODY_BACK_LENGTH 15
#define BODY_BACK_X_SHIFT 2
#define BODY_BACK_SHIFT 0

#define BODY_REAR_RAD 1
#define BODY_REAR_LENGTH 2
#define BODY_REAR_X_SHIFT 2.5
#define BODY_REAR_SHIFT 0

#define NOT_FLAPPING 0
#define FLAPPING_DOWN 1
#define FLAPPING_UP 2

#define BEAK_R 0.94902
#define BEAK_G 0.623529
#define BEAK_B 0.121569

#define HEAD_R 1
#define HEAD_G 0.980392
#define HEAD_B 0.941176

#define BACK_HEAD_R 0
#define BACK_HEAD_G 0
#define BACK_HEAD_B 1

#define BODY_R 1
#define BODY_G 1
#define BODY_B 1

#define WING_R 0
#define WING_G 0
#define WING_B 0

#define NUM_WING_GUIDE_POINTS 5

#include <stdio.h>
#include <stdlib.h>

#include "../flocking/boid.h"

#include "constants.h"

#include "quadobj.h"

/**
 * Name: Bird
 * Desc: 3D bird that has boid flocking behavior.
**/
typedef struct
{
    QuadObject quadObject;
    int flapping; // Treated like bool
    float flappingAmount;

    int * frontTopLeftWing;
    int * backTopLeftWing;
    int * frontBottomLeftWing;
    int * backBottomLeftWing;

    int * frontTopRightWing;
    int * backTopRightWing;
    int * frontBottomRightWing;
    int * backBottomRightWing;

    ColoredVertex * origFrontTopLeftWing;
    ColoredVertex * origBackTopLeftWing;
    ColoredVertex * origFrontBottomLeftWing;
    ColoredVertex * origBackBottomLeftWing;

    ColoredVertex * origFrontTopRightWing;
    ColoredVertex * origBackTopRightWing;
    ColoredVertex * origFrontBottomRightWing;
    ColoredVertex * origBackBottomRightWing;

    int startWingQuadIndex;
    int endWingQuadIndex;

    Boid * boid;

} Bird;

/**
 * Name: bird_initBird(Bird * birdPtr, Boid * boidPtr)
 * Desc: Constructor for a new bird.
 * Para: birdPtr, The bird struct to initalize.
 *       boidPtr, Boid defining flocking behavior of this bird.
**/
void bird_initBird(Bird * birdPtr, Boid * boidPtr);

/**
 * Name: bird_initBirdModel(Bird * birdModelPtr)
 * Desc: Create the actual 3D model for a bird.
 * Para: birdModelPtr, The bird whose 3D model should be initialized.
**/
void bird_initBirdModel(Bird * birdModelPtr);

/**
 * Name: bird_draw(Bird * birdPtr)
 * Desc: Draw this bird.
 * Para: birdPtr, The bird to draw.
**/
void bird_draw(Bird * birdPtr);

/**
 * Name: bird_flap(Bird * birdPtr)
 * Desc: Have this bird start flapping.
 * Para: birdPtr, The bird to start the wing flap motion on.
**/
void bird_flap(Bird * birdPtr);

/**
 * Name: bird_animate(Bird * birdPtr)
 * Desc: Animate the bird's flapping if it is currently flapping its wings.
 * Para: birdPtr, The bird to animate.
**/
void bird_animate(Bird * birdPtr);

/**
 * Name: bird_step(Bird * birdPtr, Boid * boids, int totalBirds, float timestep)
 * Desc: Calcuate forces on this bird according to its boid flocking behavior
 *       and update its position.
 * Para: birdPtr, The bird to calculate forces for.
 *       boids, The other boids that exert forces in this bird through its boid
 *          behavior.
 *       totalBoids, The number of boids in the boids array passed in.
 *       timestep, How many "game" seconds to advance the simulation of this
 *          bird's position (how long to pretend it has been since this was
 *          last called).
**/
void bird_step(Bird * birdPtr, Boid * boids, int totalBoids, float timestep);

/**
 * Name: bird_randomizePosition(Bird * birdPtr)
 * Desc: Randomize the position of this bird.
 * Para: birdPtr, The bird whose position should be randomized.
**/
void bird_randomizePosition(Bird * birdPtr);

#endif