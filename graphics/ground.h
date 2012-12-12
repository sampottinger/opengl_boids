/**
 * Name: ground.h
 * Desc: Structures and method definitions for drawing a ground surface.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef GROUND_INC_GUARD
#define GROUND_INC_GUARD

#include "objutil.h"
#include "quadobj.h"

#define GROUND_R 1
#define GROUND_G 1
#define GROUND_B 1
#define SCENE_WIDTH 640
#define SCENE_DEPTH 640
#define SCENE_START_X -320
#define SCENE_START_Z -320

/**
 * Name: ground_initGround(QuadObject * obj, int texID)
 * Desc: Function that creates the (poorly textured) ground.
 * Para: obj, The QuadObject to turn into the ground.
**/
void ground_initGround(QuadObject * obj, int texID);

#endif