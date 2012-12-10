/**
 * Name: ground.c
 * Desc: Implementation of structures and logic for drawing a ground surface.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "ground.h"

void ground_initGround(QuadObject * obj, int texID)
{
   QuadObject_init(obj, 8, 6);
   QuadObject_setNextColor(obj, GROUND_R, GROUND_G, GROUND_B);
   objutil_addRectPrismTex(obj, -320, 0, -320, 640, 3, 640, texID);
   //objutil_addRectPrism(obj, -200, 0, -200, 400, 3, 400);
}