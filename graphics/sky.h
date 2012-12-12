/**
 * Name: ground.h
 * Desc: Structures and method definitions for drawing a skybox.s
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef SKY_INC_GUARD
#define SKY_INC_GUARD

#include "objutil.h"
#include "quadobj.h"

 #include "openglwrapper.h"

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

/**
 * Name: sky_draw(QuadObject * obj)
 * Desc: Draws an object as a skybox.
 * Para: obj, The object to draw as a skybox.
**/
void sky_draw(QuadObject * obj);

#endif