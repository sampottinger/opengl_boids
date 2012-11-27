/**
 * Name: data.h
 * Desc: Header files for structures and functions for building and operating on
 *       lighting ready models.
 * Auth: Sam Pottinger
**/

#ifndef QUAD_OBJ_INC_GUARD
#define QUAD_OBJ_INC_GUARD

#include <stdlib.h>
#include <string.h>

#include "openglwrapper.h"
#include "linalg.h"

#define FALSE 0
#define TRUE 1
#define NUM_VERT_PER_QUAD 4

/**
 * Name: ColoredVertex
 * Desc: Vertex with RGB coloring and XYZ position
**/
typedef struct
{
   GLfloat pos[3];
   GLfloat col[3];
} ColoredVertex;

/**
 * Name: Quad
 * Desc: Collection of four verticies and the normal to the front face of those
 *       verticies.
**/
typedef struct
{
   unsigned int ver[4];
   GLfloat norm[3];
   int hasTexture;
   int textureNum;
} Quad;

/**
 * Name: QuadObject
 * Desc: High level "model" like struct.
**/
typedef struct 
{
   // Persistant values
   ColoredVertex * ver;
   int numVer;
   Quad * quad;
   int numQuad;
   short int outOfBounds;
   int numQuadAssigned;
   int numVerAssigned;

   // State machine vals
   GLfloat r;
   GLfloat g;
   GLfloat b;
   GLfloat x;
   GLfloat y;
   GLfloat z;
   int hasTexture;
   int textureNum;

   // Translation, rotation, scale
   GLfloat curX;
   GLfloat curY;
   GLfloat curZ;
   GLfloat curRot;
   GLfloat curRoll;
   GLfloat curPitch;
   GLfloat curYaw;
   GLfloat xScale;
   GLfloat yScale;
   GLfloat zScale;

} QuadObject;

/**
 * Name: light_t
 * Desc: Information about game lighting.
**/
typedef struct
{
   GLfloat pos[4];
   GLfloat diffuse[4];
   GLfloat specular[4];
   GLfloat ambient[4];
}light_t;

/**
 * Name: QuadObject_init(QuadObject * obj, int numVer, int numQuad)
 * Desc: Constructor for a QuadObject.
 * Para: obj, The object to operate on.
 *       numVer, The number of verticies in this object.
 *       numQuad, The number of quadrangles in this object.
**/
void QuadObject_init(QuadObject * obj, int numVer, int numQuad);

/**
 * Name: QuadObject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b)
 * Desc: Set the color of the next vertex to add to this object.
 * Para: obj, The object to operate on.
**/
void QuadObject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b);

/**
 * Name: QuadObject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z)
 * Desc: Set the position of the next vertex to add to this object.
 * Para: obj, The object to operate on.
 *       x, The x position of the next vertex to be added.
 *       y, The y position of the next vertex to be added.
 *       z, The z position of the next vertex to be added.
**/
void QuadObject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z);

void QuadObject_setNextTexture(QuadObject * obj, int texture);
void QuadObject_setNoTexture(QuadObject * obj);

/**
 * Name: QuadObject_setNextR(QuadObject * obj, GLfloat r)
 * Desc: Set the red value of the next vertex's color
 * Para: obj, The object to operate on.
 *       r, The next red value to use.
**/
void QuadObject_setNextR(QuadObject * obj, GLfloat r);

/**
 * Name: QuadObject_setNextG(QuadObject * obj, GLfloat g)
 * Desc: Set the green value of the next vertex's color
 * Para: obj, The object to operate on.
 *       g, The next green value to use.
**/
void QuadObject_setNextG(QuadObject * obj, GLfloat g);

/**
 * Name: QuadObject_setNextB(QuadObject * obj, GLfloat b)
 * Desc: Set the blue value of the next vertex's color
 * Para: obj, The object to operate on.
 *       b, The next blue value to use.
**/
void QuadObject_setNextB(QuadObject * obj, GLfloat b);

/**
 * Name: QuadObject_setNextX(QuadObject * obj, GLfloat x)
 * Desc: Set the x value of the next vertex's position
 * Para: obj, The object to operate on.
 *       x, The next x position to use.
**/
void QuadObject_setNextX(QuadObject * obj, GLfloat x);

/**
 * Name: QuadObject_setNextY(QuadObject * obj, GLfloat y)
 * Desc: Set the y value of the next vertex's position
 * Para: obj, The object to operate on.
 *       y, The next y position to use.
**/
void QuadObject_setNextY(QuadObject * obj, GLfloat y);

/**
 * Name: QuadObject_setNextZ(QuadObject * obj, GLfloat z)
 * Desc: Set the z value of the next vertex's position
 * Para: obj, The object to operate on.
 *       z, The next z position to use.
**/
void QuadObject_setNextZ(QuadObject * obj, GLfloat z);

/**
 * Name: QuadObject_moveNextX(QuadObject * obj, GLfloat dx)
 * Desc: Adjust the x value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dx, The x value (pos or neg) to add to the next X position the next
 *          vertex will get.
**/
void QuadObject_moveNextX(QuadObject * obj, GLfloat dx);

/**
 * Name: QuadObject_moveNextY(QuadObject * obj, GLfloat dy)
 * Desc: Adjust the y value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dy, The y value (pos or neg) to add to the next Y position the next
 *          vertex will get.
**/
void QuadObject_moveNextY(QuadObject * obj, GLfloat dy);

/**
 * Name: QuadObject_moveNextZ(QuadObject * obj, GLfloat dz)
 * Desc: Adjust the z value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dz, The z value (pos or neg) to add to the next Z position the next
 *          vertex will get.
**/
void QuadObject_moveNextZ(QuadObject * obj, GLfloat dz);

/**
 * Name: QuadObject_createQuadFromPrev(QuadObject * obj)
 * Desc: Create a new quadrangle in this object from the last 4 verticies added
 *       to it.
 * Para: obj, The object to operate on.
**/
void QuadObject_createQuadFromPrev(QuadObject * obj);

/**
 * Name: QuadObject_setVer(QuadObject * obj, int verId)
 * Desc: Create a new vertex in this object and give it the given id.
 * Para: obj, The object to operate on.
 *       verId, The id to give the new vertex.
**/
void QuadObject_setVer(QuadObject * obj, int verId);

/**
 * Name: QuadObject_draw(QuadObject * obj)
 * Desc: Draw this object into the current OpenGL context.
**/
void QuadObject_draw(QuadObject * obj);

/**
 * Name: QuadObject_drawSpecific(QuadObject * obj, int numQuads, int startQuad)
 * Desc: Draw this object into the current OpenGL context.
 * Para: numQuads, The number of quadrangles to draw.
 *       startQuad, The quadrangle ID to start drawing with.
**/
void QuadObject_drawSpecific(QuadObject * obj, int numQuads, int startQuad);

/**
 * Name: QuadObject_drawSpecific(QuadObject * obj, int numQuads, int startQuad)
 * Desc: Draw this object into the current OpenGL context with the normals
 *       coming out radially from the given center coordinate.
 * Para: numQuads, The number of quadrangles to draw.
 *       startQuad, The quadrangle ID to start drawing with.
 *       xCenter, The x coordinate of where the normals should start radiating.
 *       yCenter, The y coordinate of where the normals should start radiating.
 *       zCenter, The z coordinate of where the normals should start radiating.
**/
void QuadObject_drawSpecificRadially(QuadObject * obj, int numQuads,
   int startQuad, float xCenter, float yCenter, float zCenter);

/**
 * Name: QuadObject_addVer(QuadObject * obj)
 * Desc: Add a new vertex to this object.
 * Para: obj, The object to operate on.
 * Retr: The id given to the new vertex.
**/
int QuadObject_addVer(QuadObject * obj);

/**
 * Name: QuadObject_getVer(QuadObject * obj, unsigned int vertNum)
 * Desc: Gets information about a vertex.
 * Para: obj, The object to look in.
 *       vertNum, The id of the vertex to get.
 * Retr: Struct with info about the requested vertex.
**/
ColoredVertex * QuadObject_getVer(QuadObject * obj, unsigned int vertNum);

/**
 * Name: QuadObject_addQuad(QuadObject * obj, unsigned int v0Index,
 *                          unsigned int v1Index, unsigned int v2Index,
 *                          unsigned int v3Index)
 * Desc: Add a new quadrangle to this object (going counter-clockwise).
 * Para: obj, The object to operate on.
 *       v0Index, The id of the first vertex in the new quadrangle.
 *       v1Index, The id of the second vertex in the new quadrangle.
 *       v2Index, The id of the third vertex in the new quadrangle.
 *       v2Index, The id of the fourth vertex in the new quadrangle.
**/
int QuadObject_addQuad(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

/**
 * Name: QuadObject_addQuad(QuadObject * obj, unsigned int v0Index,
 *                          unsigned int v1Index, unsigned int v2Index,
 *                          unsigned int v3Index)
 * Desc: Add a new quadrangle to this object (going clockwise).
 * Para: obj, The object to operate on.
 *       v0Index, The id of the first vertex in the new quadrangle.
 *       v1Index, The id of the second vertex in the new quadrangle.
 *       v2Index, The id of the third vertex in the new quadrangle.
 *       v2Index, The id of the fourth vertex in the new quadrangle.
**/
int QuadObject_addQuadBackwards(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

/**
 * Name: QuadObject_del(QuadObject * obj)
 * Desc: Delete the memory used by this object.
 * Para: obj, The object to clean up after.
**/
void QuadObject_del(QuadObject * obj);

void QuadObject_fixQuad(QuadObject * obj, int id);

/**
 * Name: Quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
 *                 ColoredVertex * pointb, ColoredVertex * pointc)
 * Desc: Constructor for a record of a quadrangle in a QuadObject.
 * Para: obj, The object to operate on.
 *       ver, Array of IDs of the verticies this quadrangles contains.
 *       pointa, The first point in this quadrangle to use for finding the
 *               normal.
 *       pointb, The second point in this quadrangle to use for finding the
 *               normal.
 *       pointc, The third point in this quadrangle  to use for finding the
 *               normal.
**/
void Quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

void Quad_fixNormal(Quad * obj, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

#endif
