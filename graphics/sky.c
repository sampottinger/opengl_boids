/**
 * Name: sky.c
 * Desc: Implementation of structures and logic for drawing a skybox.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "sky.h"

void sky_initSky(QuadObject * obj, int * texIDs)
{
    int bottomForwardLeft;
    int bottomForwardRight;
    int bottomBackwardLeft;
    int bottomBackwardRight; 

    int topForwardLeft;
    int topForwardRight;
    int topBackwardLeft;
    int topBackwardRight;

    int x = -320;
    int y = 0;
    int z = -320;
    int width = 640;
    int height = 640;
    int depth = 640;

    quadobject_init(obj, 8, 6);
    quadobject_setNextColor(obj, SKY_R, SKY_G, SKY_B); 

    quadobject_setNextPos(obj, x, y+height, z+depth);
    topForwardLeft = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x+width, y+height, z+depth);
    topForwardRight = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x+width, y+height, z);
    topBackwardRight = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x, y+height, z);
    topBackwardLeft = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x, y, z+depth);
    bottomForwardLeft = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x+width, y, z+depth);
    bottomForwardRight = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x+width, y, z);
    bottomBackwardRight = quadobject_addVer(obj); 

    quadobject_setNextPos(obj, x, y, z);
    bottomBackwardLeft = quadobject_addVer(obj); 

    quadobject_setNextTexture(obj, texIDs[0]); // Top 
    quadobject_addQuadBackwards(obj, topForwardLeft, topForwardRight,
      topBackwardRight, topBackwardLeft);
    quadobject_setNextTexture(obj, texIDs[1]); // Left
    quadobject_addQuadBackwards(obj, topForwardLeft, topBackwardLeft,
      bottomBackwardLeft, bottomForwardLeft);
    quadobject_setNextTexture(obj, texIDs[2]); // Back
    quadobject_addQuadBackwards(obj, topBackwardLeft, topBackwardRight,
      bottomBackwardRight, bottomBackwardLeft);
    quadobject_setNextTexture(obj, texIDs[3]); // Right
    quadobject_addQuadBackwards(obj, topBackwardRight, topForwardRight,
      bottomForwardRight, bottomBackwardRight);
    quadobject_setNextTexture(obj, texIDs[4]); // Forward
    quadobject_addQuadBackwards(obj, topForwardRight, topForwardLeft,
      bottomForwardLeft, bottomForwardRight);
    quadobject_setNextTexture(obj, texIDs[5]); // Bottom
    quadobject_addQuadBackwards(obj, bottomForwardLeft, bottomBackwardLeft,
      bottomBackwardRight, bottomForwardRight);
}