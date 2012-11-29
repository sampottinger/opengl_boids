/**
 * Name: linalg.h
 * Desc: Header file for linear algebra utility functions.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2.
**/

#ifndef LINALG_INC_GUARD
#define LINALG_INC_GUARD

#include <math.h>
#define PI 3.14159265

/**
 * Name: float *norm,float pointa[3],float pointb[3],float pointc[3]
 * Desc: Finds the normal vector to the plane described by the given points.
 * Para: norm, The array to store the normal vector into.
 *       pointa, The first point's coordinates.
 *       pointb, The first point's coordinates.
 *       pointc, The first point's coordinates.
 * Note: Thanks http://www.gamedev.net/page/resources/_/technical/opengl/
 *       lighting-and-normals-r1682 for helping out with this + lighting.
**/
void linalg_getFaceNormal(float *norm, float pointa[3], float pointb[3],
    float pointc[3]);

/**
 * Name: normalize(float * vect)
 * Desc: Normalizes the given array (treating it like a vector).
 * Para: vect, The vector to normalize.
 * Note: Thanks http://www.gamedev.net/page/resources/_/technical/opengl/
 *       lighting-and-normals-r1682 for helping out with this + lighting.
**/
void linalg_normalize(float * vect);

/**
 * Name: crossProduct(float *c,float a[3], float b[3])
 * Desc: Finds the cross product of the two given vectors.
 * Para: c, The array to store the cross product into.
 *       a, The first vector. Will find cross product with b.
 *       b, The second vector Will find cross product with a.
 * Note: Thanks http://www.gamedev.net/page/resources/_/technical/opengl/
 *       lighting-and-normals-r1682 for helping out with this + lighting.
**/
void linalg_crossProduct(float *c, float a[3], float b[3]);

#endif