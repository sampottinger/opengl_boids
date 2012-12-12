/**
 * Name: objutil.c
 * Desc: Implementation of logic for generating simple 3D structures.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "objutil.h"

void objutil_addRectPrismTexNorm(QuadObject * obj, GLfloat x, GLfloat y,
    GLfloat z, GLfloat width, GLfloat height, GLfloat depth, int texture,
    int reverseNormals)
{
    int bottomForwardLeft;
    int bottomForwardRight;
    int bottomBackwardLeft;
    int bottomBackwardRight;

    int topForwardLeft;
    int topForwardRight;
    int topBackwardLeft;
    int topBackwardRight;

    if(texture != -1)
        quadobject_setNextTexture(obj, texture);

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

    if(reverseNormals == TRUE)
    {
        quadobject_addQuadBackwards(obj, topForwardLeft, topForwardRight,
            topBackwardRight, topBackwardLeft);
        quadobject_addQuadBackwards(obj, topForwardLeft, topBackwardLeft,
            bottomBackwardLeft, bottomForwardLeft);
        quadobject_addQuadBackwards(obj, topBackwardLeft, topBackwardRight,
            bottomBackwardRight, bottomBackwardLeft);
        quadobject_addQuadBackwards(obj, topBackwardRight, topForwardRight,
            bottomForwardRight, bottomBackwardRight);
        quadobject_addQuadBackwards(obj, topForwardLeft, bottomForwardLeft,
            bottomForwardRight, topForwardRight);
        quadobject_addQuadBackwards(obj, bottomForwardLeft, bottomBackwardLeft,
            bottomBackwardRight, bottomForwardRight);
    }
    else
    {
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
}

void objutil_addRectPrismTex(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z,
    GLfloat width, GLfloat height, GLfloat depth, int texture)
{
    objutil_addRectPrismTexNorm(obj, x, y, z, width, height, depth, texture, 0);
}

void objutil_addRectPrism(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z,
    GLfloat width, GLfloat height, GLfloat depth)
{
    objutil_addRectPrismTex(obj, x, y, z, width, height, depth, -1);
}

void objutil_radialVertex(double th,double ph)
{
    double x = trig_rad_sin(th) * trig_rad_cos(ph);
    double y = trig_rad_cos(th) * trig_rad_cos(ph);
    double z = trig_rad_sin(ph);
    //  For a sphere at the origin, the position
    //  and normal vectors are the same
    glNormal3d(x,y,z);
    glVertex3d(x,y,z);
}

void objutil_ball(double x,double y,double z,double r)
{
    int th,ph;
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01,1.0};
    float shinyvec[] = {1};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glScaled(r,r,r);
    //  White ball
    glColor3f(1,1,1);
    glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    //  Bands of latitude
    for (ph=-90;ph<90;ph+=10)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*10)
        {
            objutil_radialVertex(th,ph);
            objutil_radialVertex(th,ph+10);
        }
        glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}
