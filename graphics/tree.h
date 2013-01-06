/**
 * Name: ground.h
 * Desc: Structures and method definitions for drawing a ground surface.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef TREE_INC_GUARD
#define TREE_INC_GUARD

#include "objutil.h"
#include "quadobj.h"

#include <math.h>

#define TREE_BRANCH_VERTS 8
#define RAD_PER_VERT 0.785398
#define TREE_R 1
#define TREE_G 1
#define TREE_B 1
#define BASE_RAD 20
#define TOP_RAD 20
#define TREE_HEIGHT 20

/**
 * Name: tree_initTree(QuadObject * obj, int texID)
 * Desc: Function that creates a tree.
 * Para: obj, The QuadObject to turn into the ground.
**/
void tree_initTree(QuadObject * obj, int * texIDs);

/**
 * Name: tree_createSlantedTrapezoid(QuadObject * obj, float x, float y,
 *          float z, float width, float height, float depth, float endWidth,
 *          float endDepth)
 * Desc: Create a trapezoid with eight verticies where the top four verticies
 *          may be tighter or further from the center than those below it.
 * Para: obj, The QuadObject to create the prism in.
 *       x, The x position of the object to create the prism at relative to the
 *          overall object.
 *       y, The y position of the object to create the prism at relative to the
 *          overall object.
 *       z, The z position of the object to create the prism at relative to the
 *          overall object.
 *       width, The base width of the face defined by the lower four verticies.
 *       height, The overall height of this prism.
 *       depth, The base depth of the face defined by the lower four verticies.
 *       endWidth, The width of the face defined by the upper four verticies.
 *       endHeight, The height of the face defined by the upper four verticies.
**/
void tree_createSlantedTrapezoid(QuadObject * obj, float x, float y,
   float z, float width, float height, float depth, float endWidth,
   float endDepth);

#endif