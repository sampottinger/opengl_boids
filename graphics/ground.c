#include "ground.h"

void ground_initGround(QuadObject * obj)
{
   QuadObject_init(obj, 8, 6);
   QuadObject_setNextColor(obj, GROUND_R, GROUND_G, GROUND_B);
   //addRectPrismTex(obj, -100, 0, -100, 200, 3, 200, textures[1]);
   objutil_addRectPrism(obj, -200, 0, -200, 400, 3, 400);
}