#ifndef GROUND_INC_GUARD
#define GROUND_INC_GUARD

#include "objutil.h"
#include "quadobj.h"

#define GROUND_R 1
#define GROUND_G 1
#define GROUND_B 1

/**
 * Name: ground_initGround(QuadObject * obj)
 * Desc: Function that creates the (poorly textured) ground.
 * Para: obj, The QuadObject to turn into the ground.
**/
void ground_initGround(QuadObject * obj);

#endif