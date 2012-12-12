/**
 * Name: objutil.h
 * Desc: Function definitions for routines for generating 3D structures.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef OBJUTIL_INC_GUARD
#define OBJUTIL_INC_GUARD

#include <math.h>

#include "quadobj.h"
#include "trig.h"

/**
 * Name: objutil_addRectPrismTexNorm(QuadObject * obj, GLfloat x, GLfloat y,
 *          GLfloat z, GLfloat width, GLfloat height, GLfloat depth, int texture,
 *          int reverse)
 * Desc: Create a new rectangular prism with configurable normals.
 * Para: obj, The QuadObjct to create the new prism in.
 *       x, The x position of the prism (relative to object)
 *       y, The y position of the prism (relative to object)
 *       z, The z position of the prism (relative to object)
 *       width, The x size of the rectangular prism.
 *       height, The y size of the rectangular prism.
 *       depth, The z size of the rectangular prism.
 *       texture, The index of the texture to use.
 *       reverse, If true (!=0), normals will face in towards the center of the
 *          the prism.
**/
void objutil_addRectPrismTexNorm(QuadObject * obj, GLfloat x, GLfloat y,
   GLfloat z, GLfloat width, GLfloat height, GLfloat depth, int texture,
   int reverse);

/**
 * Name: objutil_addRectPrismTex(QuadObject * obj, GLfloat x, GLfloat y,
 *          GLfloat z, GLfloat width, GLfloat height, GLfloat depth)
 * Desc: Creates a 3D rectangular prism with a texture.
 * Para: obj, The QuadObjct to create the new prism in.
 *       x, The x position of the prism (relative to object)
 *       y, The y position of the prism (relative to object)
 *       z, The z position of the prism (relative to object)
 *       width, The x size of the rectangular prism.
 *       height, The y size of the rectangular prism.
 *       depth, The z size of the rectangular prism.
 *       texture, The index of the texture to use.
**/
void objutil_addRectPrismTex(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z,
   GLfloat width, GLfloat height, GLfloat depth, int texture);

/**
 * Name: objutil_addRectPrismTex(QuadObject * obj, GLfloat x, GLfloat y,
 *          GLfloat z, GLfloat width, GLfloat height, GLfloat depth)
 * Desc: Creates a 3D rectangular prism.
 * Para: obj, The QuadObjct to create the new prism in.
 *       x, The x position of the prism (relative to object)
 *       y, The y position of the prism (relative to object)
 *       z, The z position of the prism (relative to object)
 *       width, The x size of the rectangular prism.
 *       height, The y size of the rectangular prism.
 *       depth, The z size of the rectangular prism.
**/
void objutil_addRectPrism(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z,
   GLfloat width, GLfloat height, GLfloat depth);

/**
 * Name: objutil_radialVertex(double th, double ph)
 * Desc: Draw vertex in polar coordinates with normal.
 * Note: shamelessly stolen from class
**/
void objutil_radialVertex(double th, double ph);

/**
 * Name: objutil_ball(double x,double y,double z,double r)
 * Desc: Ball generation routine shamelessly stolen from class.
**/
void objutil_ball(double x,double y,double z,double r);

#endif
