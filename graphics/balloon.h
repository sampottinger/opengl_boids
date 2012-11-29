/**
 * Name: balloon.h
 * Desc: Structures and methods for 3D hot air balloon model.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef BALLOON_INC_GUARD
#define BALLOON_INC_GUARD

#include "quadobj.h"
#include "objutil.h"

#define BASKET_R 1
#define BASKET_G 1
#define BASKET_B 1

#define BASKET_RAIL_R 1
#define BASKET_RAIL_G 1
#define BASKET_RAIL_B 1

#define BALLOON_COLOR_1_R 0
#define BALLOON_COLOR_1_G 0
#define BALLOON_COLOR_1_B 1

#define BALLOON_COLOR_2_R 0
#define BALLOON_COLOR_2_G 0.5
#define BALLOON_COLOR_2_B 0.9

#define BASKET_WIDTH 5
#define BASKET_HEIGHT 7
#define BASKET_DEPTH 5
#define BASKET_THICKNESS 0.5

#define NUM_BALLOON_RADI 10
#define BALLOON_HEIGHT 66
#define BALLOON_RADIAL_STEPS 10

#define POLE_HEIGHT 20

#define HEATING_ELEMENT_R 0.75
#define HEATING_ELEMENT_G 0.75
#define HEATING_ELEMENT_B 0.75

#define HEATING_ELEMENT_WIDTH 1
#define HEATING_ELEMENT_HEIGHT 1
#define HEATING_ELEMENT_DEPTH 1

/**
 * Name: balloon_generateRadialPositions(float * xVals, float * yVals,
 *       int numPos, float radius)
 * Desc: Generates a "ring" of positions such that the first and last positions
 *       are eqal and the other points are (mostly) equidistant around a circle.
 * Para: xVals, the array to store the generated x values into.
 *       yVals, the array to store the generated y values into.
 *       numPos, the number of positions to generate
 *       radius, The radius of the circle to find points on.
**/
void balloon_generateRadialPositions(float * xVals, float * yVals, int numPos,
   float radius);

/**
 * Name: generateBalloon(QuadObject * obj, GLfloat * radi, GLfloat * radi_dist)
 * Desc: Generate the balloon part of a hor air balloon.
 * Para: obj, The QuadObject to generate the balloon part of a hot air balloon.
 *       radi, Array describing the shape of the balloon.
 *       radi_dist, Array describing the length of intervals on the balloon.
**/
void balloon_generateBalloon(QuadObject * obj, GLfloat * radi,
   GLfloat * radi_dist);

/**
 * Name: initBalloon(QuadObject * ballPtr)
 * Desc: Create a hot air balloon.
 * Para: ballPtr, Pointer to QuadObject that will be the hot air balloon.
**/
void balloon_initBalloon(QuadObject * ballPtr, int textureID);

#endif
