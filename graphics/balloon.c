/**
 * Name: birds.c
 * Desc: Hot air balloon logic and method implementations.
 * Auth: Sam Pottinger
 * Refr: Help from http://www.swiftless.com/tutorials/opengl/camera2.html,
 *       http://www.gamedev.net/page/resources/_/technical/opengl/
 *       lighting-and-normals-r1682, and http://www.cse.msu.edu/~cse872/
 *       tutorial3.html
 * Licn: GNU GPL v2
**/

#include "balloon.h"

// Textures
int mode=0;

// Radius values to use to construct ballon part of hot air balloons
GLfloat BALLOON_RADI_LIST[NUM_BALLOON_RADI] =
{
    0.001,
    10,
    28,
    30,
    32,
    28,
    20,
    11,
    0.1,
    0.1
};

GLfloat BALLOON_RADI_DIST[NUM_BALLOON_RADI] =
{
    2,
    10,
    10,
    10,
    10,
    10,
    10,
    2,
    1
};

void balloon_generateRadialPositions(float * xVals, float * yVals, int numPos,
   float radius)
{
    int i = 0;
    double step = 2 * PI / (numPos - 1);
    double curRad = 0;

    for(i=0; i<numPos; i++)
    {
        xVals[i] = radius * sin(curRad);
        yVals[i] = radius * cos(curRad);
        curRad += step;
    }

    xVals[numPos-1] = xVals[0];
    yVals[numPos-1] = yVals[0];
}

void balloon_generateBalloon(QuadObject * obj, GLfloat * radi,
   GLfloat * radi_dist)
{
    int i;
    int j;
    int upperRightID;
    int lowerRightID;
    int upperLeftID;
    int lowerLeftID;
    int newVert;
    int color;
    int startNumVertAssigned = obj->numVerAssigned;
    float xRadialPositions [BALLOON_RADIAL_STEPS];
    float zRadialPositions [BALLOON_RADIAL_STEPS];

    quadobject_setNextPos(obj, 0, POLE_HEIGHT + BALLOON_HEIGHT, 0);

    color = 0;
    for(i=0; i<NUM_BALLOON_RADI; i++)
    {
        balloon_generateRadialPositions(xRadialPositions, zRadialPositions,
            BALLOON_RADIAL_STEPS, BALLOON_RADI_LIST[i]);

        for(j=0; j<BALLOON_RADIAL_STEPS; j++)
        {
            if(color == 1)
            {
                color = 0;
                quadobject_setNextColor(
                    obj,
                    BALLOON_COLOR_1_R,
                    BALLOON_COLOR_1_G,
                    BALLOON_COLOR_1_B
                );
            }
            else
            {
                color = 1;
                quadobject_setNextColor(
                    obj,
                    BALLOON_COLOR_2_R,
                    BALLOON_COLOR_2_G,
                    BALLOON_COLOR_2_B
                );
            }

            quadobject_setNextX(obj, xRadialPositions[j]);
            quadobject_setNextZ(obj, zRadialPositions[j]);
            newVert = quadobject_addVer(obj);

            // Create face if appropriate
            if(newVert - startNumVertAssigned >= BALLOON_RADIAL_STEPS)
            {
                lowerRightID = newVert;
                lowerLeftID = lowerRightID - 1;
                upperRightID = lowerRightID - BALLOON_RADIAL_STEPS;
                upperLeftID = upperRightID - 1;
                quadobject_addQuad(
                    obj,
                    upperRightID,
                    upperLeftID,
                    lowerLeftID,
                    lowerRightID
                );
            }
        }

        quadobject_moveNextY(obj, -BALLOON_RADI_DIST[i]);
      
    }
}

void balloon_initBalloon(QuadObject * ballPtr, int textureID)
{
    int bottomForwardLeft;
    int bottomForwardRight;
    int bottomBackwardLeft;
    int bottomBackwardRight;

    int topForwardLeft;
    int topForwardRight;
    int topBackwardLeft;
    int topBackwardRight;

    int outerTopForwardLeft;
    int outerTopForwardRight;
    int outerTopBackwardLeft;
    int outerTopBackwardRight;

    int innerTopForwardLeft;
    int innerTopForwardRight;
    int innerTopBackwardLeft;
    int innerTopBackwardRight;

    quadobject_init(ballPtr, 216, 172);

    // Set location
    ballPtr->xScale = 0.35;
    ballPtr->yScale = 0.35;
    ballPtr->zScale = 0.35;
    ballPtr->curPitch = 1;

    // Basket outline
    quadobject_setNextTexture(ballPtr, textureID);
    quadobject_setNextColor(
        ballPtr,
        BASKET_RAIL_R,
        BASKET_RAIL_G,
        BASKET_RAIL_B
    );
    quadobject_setNextPos(ballPtr, -BASKET_WIDTH, BASKET_HEIGHT, BASKET_DEPTH);
    topForwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, BASKET_WIDTH, BASKET_HEIGHT, BASKET_DEPTH);
    topForwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, BASKET_WIDTH, BASKET_HEIGHT, -BASKET_DEPTH);
    topBackwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, -BASKET_WIDTH, BASKET_HEIGHT, -BASKET_DEPTH);
    topBackwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, -BASKET_WIDTH, 0, BASKET_DEPTH);
    bottomForwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, BASKET_WIDTH, 0, BASKET_DEPTH);
    bottomForwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, BASKET_WIDTH, 0, -BASKET_DEPTH);
    bottomBackwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(ballPtr, -BASKET_WIDTH, 0, -BASKET_DEPTH);
    bottomBackwardLeft = quadobject_addVer(ballPtr);

    quadobject_addQuad(ballPtr, topForwardLeft, topBackwardLeft,
        bottomBackwardLeft, bottomForwardLeft);
    quadobject_addQuad(ballPtr, topBackwardLeft, topBackwardRight,
        bottomBackwardRight, bottomBackwardLeft);
    quadobject_addQuad(ballPtr, topBackwardRight, topForwardRight,
        bottomForwardRight, bottomBackwardRight);
    quadobject_addQuad(ballPtr, topForwardLeft, bottomForwardLeft,
        bottomForwardRight, topForwardRight);
    quadobject_addQuad(ballPtr, bottomForwardLeft, bottomBackwardLeft,
        bottomBackwardRight, bottomForwardRight);

    outerTopForwardLeft = topForwardLeft;
    outerTopForwardRight = topForwardRight;
    outerTopBackwardLeft = topBackwardLeft;
    outerTopBackwardRight = topBackwardRight;

    // Basket innards
    quadobject_setNextColor(ballPtr, BASKET_R, BASKET_G, BASKET_B);
    quadobject_setNextPos(
        ballPtr,
        -BASKET_WIDTH + BASKET_THICKNESS,
        BASKET_HEIGHT - BASKET_THICKNESS,
        BASKET_DEPTH - BASKET_THICKNESS
    );
    topForwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr,
        BASKET_WIDTH - BASKET_THICKNESS,
        BASKET_HEIGHT - BASKET_THICKNESS,
        BASKET_DEPTH - BASKET_THICKNESS
    );
    topForwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr,
        BASKET_WIDTH - BASKET_THICKNESS,
        BASKET_HEIGHT - BASKET_THICKNESS,
        -BASKET_DEPTH + BASKET_THICKNESS
    );
    topBackwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr,
        -BASKET_WIDTH + BASKET_THICKNESS,
        BASKET_HEIGHT - BASKET_THICKNESS,
        -BASKET_DEPTH + BASKET_THICKNESS
    );
    topBackwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr,
        -BASKET_WIDTH + BASKET_THICKNESS,
        0,
        BASKET_DEPTH - BASKET_THICKNESS
    );
    bottomForwardLeft = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr,
        BASKET_WIDTH - BASKET_THICKNESS,
        0,
        BASKET_DEPTH - BASKET_THICKNESS
    );
    bottomForwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr, 
        BASKET_WIDTH - BASKET_THICKNESS, 
        0, 
        -BASKET_DEPTH + BASKET_THICKNESS
    );
    bottomBackwardRight = quadobject_addVer(ballPtr);

    quadobject_setNextPos(
        ballPtr, 
        -BASKET_WIDTH + BASKET_THICKNESS, 
        0, 
        -BASKET_DEPTH + BASKET_THICKNESS
    );
    bottomBackwardLeft = quadobject_addVer(ballPtr);

    quadobject_addQuadBackwards(ballPtr, topForwardLeft, topBackwardLeft,
        bottomBackwardLeft, bottomForwardLeft);
    quadobject_addQuadBackwards(ballPtr, topBackwardLeft, topBackwardRight,
        bottomBackwardRight, bottomBackwardLeft);
    quadobject_addQuadBackwards(ballPtr, topBackwardRight, topForwardRight,
        bottomForwardRight, bottomBackwardRight);
    quadobject_addQuadBackwards(ballPtr, topForwardLeft, bottomForwardLeft,
        bottomForwardRight, topForwardRight);
    quadobject_addQuadBackwards(ballPtr, bottomForwardLeft, bottomBackwardLeft,
        bottomBackwardRight, bottomForwardRight);

    innerTopForwardLeft = topForwardLeft;
    innerTopForwardRight = topForwardRight;
    innerTopBackwardLeft = topBackwardLeft;
    innerTopBackwardRight = topBackwardRight;

    // Basket railing
    quadobject_setNextColor(ballPtr, BASKET_RAIL_R, BASKET_RAIL_G,
        BASKET_RAIL_B);

    quadobject_addQuad(
        ballPtr, 
        outerTopForwardRight, 
        innerTopForwardRight, 
        innerTopForwardLeft, 
        outerTopForwardLeft
    );
    quadobject_addQuad(
        ballPtr, 
        outerTopBackwardLeft, 
        innerTopBackwardLeft, 
        innerTopBackwardRight, 
        outerTopBackwardRight
    );
    quadobject_addQuad(
        ballPtr, 
        outerTopBackwardRight, 
        innerTopBackwardRight, 
        innerTopForwardRight, 
        outerTopForwardRight
    );
    quadobject_addQuad(
        ballPtr,
        outerTopForwardLeft,
        innerTopForwardLeft,
        innerTopBackwardLeft,
        outerTopBackwardLeft
    );

    // Poles
    quadobject_setNextColor(
        ballPtr,
        BASKET_RAIL_R,
        BASKET_RAIL_G,
        BASKET_RAIL_B
    );
    objutil_addRectPrism(ballPtr, 
        -BASKET_WIDTH, 
        0, 
        -BASKET_DEPTH, 
        0.5, 
        POLE_HEIGHT, 
        0.5
    );
    objutil_addRectPrism(
        ballPtr, 
        -BASKET_WIDTH, 
        0, 
        BASKET_DEPTH - BASKET_THICKNESS, 
        0.5, 
        POLE_HEIGHT, 
        0.5
    );
    objutil_addRectPrism(
        ballPtr, 
        BASKET_WIDTH - BASKET_THICKNESS, 
        0, 
        -BASKET_DEPTH, 0.5, 
        POLE_HEIGHT, 
        0.5
    );
    objutil_addRectPrism(
        ballPtr, 
        BASKET_WIDTH - BASKET_THICKNESS, 
        0, 
        BASKET_DEPTH - BASKET_THICKNESS, 
        0.5, 
        20, 
        0.5
    );

    // Top enclosure
    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH,
        POLE_HEIGHT,
        -BASKET_DEPTH,
        BASKET_WIDTH*2,
        0.5,
        0.5
    );
    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH,
        POLE_HEIGHT,
        BASKET_DEPTH - BASKET_THICKNESS,
        BASKET_WIDTH*2,
        0.5,
        0.5
    );
    objutil_addRectPrism(
        ballPtr,
        BASKET_WIDTH - BASKET_THICKNESS,
        POLE_HEIGHT,
        -BASKET_DEPTH,
        0.5,
        0.5,
        BASKET_DEPTH*2
    );
    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH,
        POLE_HEIGHT,
        -BASKET_DEPTH,
        0.5,
        0.5,
        BASKET_DEPTH*2
    );

    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH,
        POLE_HEIGHT,
        -BASKET_DEPTH/2,
        BASKET_WIDTH*2,
        0.5,
        0.5
    );
    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH,
        POLE_HEIGHT,
        BASKET_DEPTH/2,
        BASKET_WIDTH*2,
        0.5,
        0.5
    );
    objutil_addRectPrism(
        ballPtr,
        BASKET_WIDTH/2,
        POLE_HEIGHT,
        -BASKET_DEPTH,
        0.5,
        0.5,
        BASKET_DEPTH*2
    );
    objutil_addRectPrism(
        ballPtr,
        -BASKET_WIDTH/2,
        POLE_HEIGHT,
        -BASKET_DEPTH,
        0.5,
        0.5,
        BASKET_DEPTH*2
    );

    quadobject_setNoTexture(ballPtr);

    // Heating element
    quadobject_setNextColor(ballPtr, HEATING_ELEMENT_R, HEATING_ELEMENT_G,
        HEATING_ELEMENT_B);
    objutil_addRectPrism(ballPtr, -HEATING_ELEMENT_WIDTH, POLE_HEIGHT, 
        -HEATING_ELEMENT_DEPTH, HEATING_ELEMENT_WIDTH*2, HEATING_ELEMENT_HEIGHT*2,
        HEATING_ELEMENT_DEPTH*2);

    balloon_generateBalloon(ballPtr, BALLOON_RADI_LIST, BALLOON_RADI_DIST);
}

void balloon_draw(QuadObject * ballPtr)
{
    quadobject_drawSpecific(ballPtr, BALLOON_START_VERTEX, 0);
    quadobject_drawSpecificRadially(
        ballPtr,
        ballPtr->numQuad,
        BALLOON_START_VERTEX,
        0,
        BALLOON_RADIATION_CENTER,
        0
    );
}
