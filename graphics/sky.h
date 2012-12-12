/**
 * Name: ground.h
 * Desc: Structures and method definitions for drawing a ground surface.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef SKY_INC_GUARD
#define SKY_INC_GUARD

#include "objutil.h"
#include "quadobj.h"

#define SKY_R 1
#define SKY_G 1
#define SKY_B 1

/**
 * Name: ground_initGround(QuadObject * obj, int texID)
 * Desc: Function that creates the (poorly textured) ground.
 * Para: obj, The QuadObject to turn into the ground.
 *       texID, integer array of size 2. First element should have bark texture
 *          index / ID and the second should have a leaves texture.
**/
void sky_initSky(QuadObject * obj, int * texID);

#endif