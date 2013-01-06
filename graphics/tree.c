/**
 * Name: sky.c
 * Desc: Implementation of structures and logic for drawing a skybox.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "tree.h"

#include <math.h>

void tree_initTree(QuadObject * obj, int * texIDs)
{
    quadobject_init(obj, 24, 18);
    quadobject_setNextColor(obj, TREE_R, TREE_G, TREE_B);
    quadobject_setNextTexture(obj, texIDs[0]);
    tree_createSlantedTrapezoid(obj, -5, 0, -5, 10, 50, 10, 4, 4);

    quadobject_setNextTexture(obj, texIDs[1]);
    tree_createSlantedTrapezoid(obj, -15, 35, -15, 30, 20, 30, 0.1, 0.1);
    tree_createSlantedTrapezoid(obj, -20, 15, -20, 40, 20, 40, 20, 20);
}


void tree_createSlantedTrapezoid(QuadObject * obj, float x, float y,
   float z, float startWidth, float height, float startDepth, float endWidth,
   float endDepth)
{
    int bottomForwardLeft;
    int bottomForwardRight;
    int bottomBackwardLeft;
    int bottomBackwardRight;

    int topForwardLeft;
    int topForwardRight;
    int topBackwardLeft;
    int topBackwardRight;

    float widthDiff = (startWidth - endWidth)/2;
    float depthDiff = (startDepth - endDepth)/2;

    endWidth += widthDiff;
    endDepth += depthDiff;

    quadobject_setNextPos(obj, x+widthDiff, y+height, z+endDepth);
    topForwardLeft = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x+endWidth, y+height, z+endDepth);
    topForwardRight = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x+endWidth, y+height, z+depthDiff);
    topBackwardRight = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x+widthDiff, y+height, z+depthDiff);
    topBackwardLeft = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x, y, z+startDepth);
    bottomForwardLeft = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x+startWidth, y, z+startDepth);
    bottomForwardRight = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x+startWidth, y, z);
    bottomBackwardRight = quadobject_addVer(obj);

    quadobject_setNextPos(obj, x, y, z);
    bottomBackwardLeft = quadobject_addVer(obj);

    quadobject_addQuad(obj, topForwardLeft, topForwardRight,
        topBackwardRight, topBackwardLeft);
    quadobject_addQuad(obj, topForwardLeft, topBackwardLeft,
        bottomBackwardLeft, bottomForwardLeft);
    quadobject_addQuad(obj, topBackwardLeft, topBackwardRight,
        bottomBackwardRight, bottomBackwardLeft);
    quadobject_addQuad(obj, topBackwardRight, topForwardRight,
        bottomForwardRight, bottomBackwardRight);
    quadobject_addQuad(obj, topForwardLeft, bottomForwardLeft,
        bottomForwardRight, topForwardRight);
    quadobject_addQuad(obj, bottomForwardLeft, bottomBackwardLeft,
        bottomBackwardRight, bottomForwardRight);

}