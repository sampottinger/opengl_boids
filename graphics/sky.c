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

    QuadObject_init(obj, 8, 6);
    QuadObject_setNextColor(obj, SKY_R, SKY_G, SKY_B); 

    QuadObject_setNextPos(obj, x, y+height, z+depth);
    topForwardLeft = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x+width, y+height, z+depth);
    topForwardRight = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x+width, y+height, z);
    topBackwardRight = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x, y+height, z);
    topBackwardLeft = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x, y, z+depth);
    bottomForwardLeft = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x+width, y, z+depth);
    bottomForwardRight = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x+width, y, z);
    bottomBackwardRight = QuadObject_addVer(obj); 

    QuadObject_setNextPos(obj, x, y, z);
    bottomBackwardLeft = QuadObject_addVer(obj); 

    QuadObject_setNextTexture(obj, texIDs[0]); // Top 
    QuadObject_addQuadBackwards(obj, topForwardLeft, topForwardRight,
      topBackwardRight, topBackwardLeft);
    QuadObject_setNextTexture(obj, texIDs[1]); // Left
    QuadObject_addQuadBackwards(obj, topForwardLeft, topBackwardLeft,
      bottomBackwardLeft, bottomForwardLeft);
    QuadObject_setNextTexture(obj, texIDs[2]); // Back
    QuadObject_addQuadBackwards(obj, topBackwardLeft, topBackwardRight,
      bottomBackwardRight, bottomBackwardLeft);
    QuadObject_setNextTexture(obj, texIDs[3]); // Right
    QuadObject_addQuadBackwards(obj, topBackwardRight, topForwardRight,
      bottomForwardRight, bottomBackwardRight);
    QuadObject_setNextTexture(obj, texIDs[4]); // Forward
    QuadObject_addQuadBackwards(obj, topForwardRight, topForwardLeft,
      bottomForwardLeft, bottomForwardRight);
    QuadObject_setNextTexture(obj, texIDs[5]); // Bottom
    QuadObject_addQuadBackwards(obj, bottomForwardLeft, bottomBackwardLeft,
      bottomBackwardRight, bottomForwardRight);
}