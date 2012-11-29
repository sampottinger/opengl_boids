/**
 * Name: constants.h
 * Desc: Constants for boid flocking behavior.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef BOID_FLOCKING_CONSTANTS
#define BOID_FLOCKING_CONSTANTS

#define MAX_BOID_SPEED 3
#define MAX_BOID_FORCE 0.05
#define START_BOID_ANGLE 3

#define SEPERATION_WEIGHT 1.5
#define ALIGN_WEIGHT 1.0
#define COHESION_WEIGHT 1.0

#define DESIRED_SEPERATION 25

#define MAX_NEIGHBOR_DISTANCE 50

#define BOID_MIN_X -200
#define BOID_MAX_X 200
#define BOID_MIN_Y 0
#define BOID_MAX_Y 200
#define BOID_MIN_Z -200
#define BOID_MAX_Z 200

#endif