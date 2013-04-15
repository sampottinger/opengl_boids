/**
 * Name: bird.c
 * Desc: Logic and method implementations for 3D flocking bird model.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "bird.h"

void bird_initBird(Bird * birdPtr, Boid * boidPtr)
{
    int i;
    QuadObject * quadObject;

    int * frontTopLeftWing;
    int * backTopLeftWing;
    int * frontBottomLeftWing;
    int * backBottomLeftWing;
    int * frontTopRightWing;
    int * backTopRightWing;
    int * frontBottomRightWing;
    int * backBottomRightWing;

    ColoredVertex * origFrontTopLeftWing;
    ColoredVertex * origBackTopLeftWing;
    ColoredVertex * origFrontBottomLeftWing;
    ColoredVertex * origBackBottomLeftWing;
    ColoredVertex * origFrontTopRightWing;
    ColoredVertex * origBackTopRightWing;
    ColoredVertex * origFrontBottomRightWing;
    ColoredVertex * origBackBottomRightWing;

    // Allocate space for wings
    birdPtr->frontTopLeftWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->backTopLeftWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->frontBottomLeftWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->backBottomLeftWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);

    birdPtr->frontTopRightWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->backTopRightWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->frontBottomRightWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);
    birdPtr->backBottomRightWing = malloc(sizeof(int) * NUM_WING_GUIDE_POINTS);

    // Build the model
    bird_initBirdModel(birdPtr);
    birdPtr->flapping=NOT_FLAPPING;
    birdPtr->flappingAmount=1;

    // Create space for copies of initial wing state
    birdPtr->origFrontTopLeftWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origBackTopLeftWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origFrontBottomLeftWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origBackBottomLeftWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);

    birdPtr->origFrontTopRightWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origBackTopRightWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origFrontBottomRightWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);
    birdPtr->origBackBottomRightWing = 
        malloc(sizeof(ColoredVertex) * NUM_WING_GUIDE_POINTS);

    // Create aliases for shorter lines
    frontTopLeftWing = birdPtr->frontTopLeftWing;
    backTopLeftWing = birdPtr->backTopLeftWing;
    frontBottomLeftWing = birdPtr->frontBottomLeftWing;
    backBottomLeftWing = birdPtr->backBottomLeftWing;
    frontTopRightWing = birdPtr->frontTopRightWing;
    backTopRightWing = birdPtr->backTopRightWing;
    frontBottomRightWing = birdPtr->frontBottomRightWing;
    backBottomRightWing = birdPtr->backBottomRightWing;
    origFrontTopLeftWing = birdPtr->origFrontTopLeftWing;
    origBackTopLeftWing = birdPtr->origBackTopLeftWing;
    origFrontBottomLeftWing = birdPtr->origFrontBottomLeftWing;
    origBackBottomLeftWing = birdPtr->origBackBottomLeftWing;
    origFrontTopRightWing = birdPtr->origFrontTopRightWing;
    origBackTopRightWing = birdPtr->origBackTopRightWing;
    origFrontBottomRightWing = birdPtr->origFrontBottomRightWing;
    origBackBottomRightWing = birdPtr->origBackBottomRightWing;

    // Copy initial wing state
    quadObject = &(birdPtr->quadObject);
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        memcpy(
            origFrontTopLeftWing+i,
            quadobject_getVer(quadObject, frontTopLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackTopLeftWing+i,
            quadobject_getVer(quadObject, backTopLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontBottomLeftWing+i,
            quadobject_getVer(quadObject, frontBottomLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackBottomLeftWing+i,
            quadobject_getVer(quadObject, backBottomLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontTopRightWing+i,
            quadobject_getVer(quadObject, frontTopRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackTopRightWing+i,
            quadobject_getVer(quadObject, backTopRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontBottomRightWing+i,
            quadobject_getVer(quadObject, frontBottomRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackBottomRightWing+i,
            quadobject_getVer(quadObject, backBottomRightWing[i]),
            sizeof(ColoredVertex)
        );
    }

    birdPtr->boid = boidPtr;
}

void bird_animate(Bird * birdPtr)
{
    int i;
    ColoredVertex * frontTopLeftWing;
    ColoredVertex * backTopLeftWing;
    ColoredVertex * frontBottomLeftWing;
    ColoredVertex * backBottomLeftWing;
    ColoredVertex * frontTopRightWing;
    ColoredVertex * backTopRightWing;
    ColoredVertex * frontBottomRightWing;
    ColoredVertex * backBottomRightWing;
    QuadObject * quadObject = &(birdPtr->quadObject);

    if(birdPtr->flapping == NOT_FLAPPING)
    {
        return;
    }
    else
    {
        if(birdPtr->flappingAmount >= 2)
            birdPtr->flapping = RETURNING;
        else if(birdPtr->flappingAmount <= -0.5)
            birdPtr->flapping = FLAPPING_UP;
        else if(birdPtr->flappingAmount == 0 && birdPtr->flapping == RETURNING)
            birdPtr->flapping = NOT_FLAPPING;

        if(birdPtr->flapping == FLAPPING_DOWN || birdPtr->flapping == RETURNING)
            birdPtr->flappingAmount -= 0.1;
        else if(birdPtr->flapping == FLAPPING_UP)
            birdPtr->flappingAmount += 0.1;

        for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
        {
            frontTopLeftWing = quadobject_getVer(quadObject, birdPtr->frontTopLeftWing[i]);
            backTopLeftWing = quadobject_getVer(quadObject, birdPtr->backTopLeftWing[i]);
            frontBottomLeftWing = quadobject_getVer(quadObject, birdPtr->frontBottomLeftWing[i]);
            backBottomLeftWing = quadobject_getVer(quadObject, birdPtr->backBottomLeftWing[i]);
            frontTopRightWing = quadobject_getVer(quadObject, birdPtr->frontTopRightWing[i]);
            backTopRightWing = quadobject_getVer(quadObject, birdPtr->backTopRightWing[i]);
            frontBottomRightWing = quadobject_getVer(quadObject, birdPtr->frontBottomRightWing[i]);
            backBottomRightWing = quadobject_getVer(quadObject, birdPtr->backBottomRightWing[i]);

            frontTopLeftWing->pos[1] = birdPtr->origFrontTopLeftWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            backTopLeftWing->pos[1] = birdPtr->origBackTopLeftWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            frontBottomLeftWing->pos[1] = birdPtr->origFrontBottomLeftWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            backBottomLeftWing->pos[1] = birdPtr->origBackBottomLeftWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            frontTopRightWing->pos[1] = birdPtr->origFrontTopRightWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            backTopRightWing->pos[1] = birdPtr->origBackTopRightWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            frontBottomRightWing->pos[1] = birdPtr->origFrontBottomRightWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
            backBottomRightWing->pos[1] = birdPtr->origBackBottomRightWing[i].pos[1] * birdPtr->flappingAmount - 2 + birdPtr->flappingAmount;
        }

        for(i=birdPtr->startWingQuadIndex; i<=birdPtr->endWingQuadIndex; i++)
        {
            quadobject_fixQuad(&(birdPtr->quadObject), i);
        }
    }
}

void bird_randomizePosition(Bird * birdPtr)
{
    float x = (rand() % (MAX_X - MIN_X)) + MIN_X;
    float y = (rand() % (MAX_Y - MIN_Y)) + MIN_Y;
    float z = (rand() % (MAX_Z - MIN_Z)) + MIN_Z;
    birdPtr->quadObject.curX = x;
    birdPtr->quadObject.curY = y;
    birdPtr->quadObject.curZ = z;
    Boid_setPos(birdPtr->boid, x, y, z);
    Boid_setVel(birdPtr->boid, rand() % 2, rand() % 2, rand() % 2);
}

void bird_flap(Bird * birdPtr)
{
    birdPtr->flapping = FLAPPING_DOWN;
    birdPtr->flappingAmount = 0.9;
    bird_animate(birdPtr);
}

void bird_initBirdModel(Bird * decoratedBirdPtr)
{
    QuadObject * birdPtr = &(decoratedBirdPtr->quadObject);

    ColoredVertex * curVer;

    int quadIndex;

    int beakEndForwardTop;
    int beakEndBackTop;
    int beakEndBackBottom;
    int beakEndForwardBottom;
    int beakStartForwardTop;
    int beakStartBackTop;
    int beakStartBackBottom;
    int beakStartForwardBottom;

    int headEndForwardTop;
    int headEndBackTop;
    int headEndBackBottom;
    int headEndForwardBottom;
    int headMidForwardTop;
    int headMidBackTop;
    int headMidBackBottom;
    int headMidForwardBottom;
    int headStartForwardTop;
    int headStartBackTop;
    int headStartBackBottom;
    int headStartForwardBottom;

    int bodyFrontForwardTop;
    int bodyFrontBackTop;
    int bodyFrontBackBottom;
    int bodyFrontForwardBottom;
    int bodyMidForwardTop;
    int bodyMidBackTop;
    int bodyMidBackBottom;
    int bodyMidForwardBottom;
    int bodyBackForwardTop;
    int bodyBackBackTop;
    int bodyBackBackBottom;
    int bodyBackForwardBottom;
    int bodyRearForwardTop;
    int bodyRearBackTop;
    int bodyRearBackBottom;
    int bodyRearForwardBottom;

    int * frontTopLeftWing = decoratedBirdPtr->frontTopLeftWing;
    int * backTopLeftWing = decoratedBirdPtr->backTopLeftWing;
    int * frontBottomLeftWing = decoratedBirdPtr->frontBottomLeftWing;
    int * backBottomLeftWing = decoratedBirdPtr->backBottomLeftWing;

    int * frontTopRightWing = decoratedBirdPtr->frontTopRightWing;
    int * backTopRightWing = decoratedBirdPtr->backTopRightWing;
    int * frontBottomRightWing = decoratedBirdPtr->frontBottomRightWing;
    int * backBottomRightWing = decoratedBirdPtr->backBottomRightWing;

    int i;

    float MID_WING_Z_LENGTHS[NUM_WING_GUIDE_POINTS] = {
        11,
        12,
        12,
        10,
        4
    };

    quadobject_init(birdPtr, 76, 75);

    /* BEAK */

    quadobject_setNextColor(birdPtr, BEAK_R, BEAK_G, BEAK_B);

    // End - 4 vert, 1 face
    beakEndBackTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BEAK_INNER_SIDE_LEN);
    beakEndBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, -BEAK_INNER_SIDE_LEN);
    beakEndForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BEAK_INNER_SIDE_LEN);
    beakEndForwardTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Start - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, BEAK_LENGTH);
    quadobject_moveNextX(birdPtr, BEAK_SHIFT);
    quadobject_moveNextY(birdPtr, BEAK_SHIFT);
    quadobject_moveNextX(birdPtr, -BEAK_OUTER_SIDE_LEN / 2);
    beakStartForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BEAK_OUTER_SIDE_LEN);
    beakStartForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, BEAK_OUTER_SIDE_LEN);
    beakStartBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BEAK_OUTER_SIDE_LEN);
    beakStartBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Fill in - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        beakEndBackTop,
        beakEndForwardTop,
        beakStartForwardTop,
        beakStartBackTop
    );
    quadobject_addQuad(
        birdPtr,
        beakStartBackBottom,
        beakEndBackBottom,
        beakEndBackTop,
        beakStartBackTop
    );
    quadobject_addQuad(
        birdPtr,
        beakStartForwardTop,
        beakEndForwardTop,
        beakEndForwardBottom,
        beakStartForwardBottom
    );
    quadobject_addQuad(
        birdPtr,
        beakStartBackBottom,
        beakStartForwardBottom,
        beakEndForwardBottom,
        beakEndBackBottom
    );

    /* HEAD */

    quadobject_setNextColor(birdPtr, HEAD_R, HEAD_G, HEAD_B);

    // Front head part - 4 vert, 1 head
    quadobject_moveNextZ(birdPtr, HEAD_END_LENGTH);
    quadobject_moveNextX(birdPtr, -HEAD_END_SHIFT);
    quadobject_moveNextY(birdPtr, HEAD_END_SHIFT);
    quadobject_moveNextX(birdPtr, -HEAD_END_RAD / 2);
    headEndForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -HEAD_END_RAD);
    headEndForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, HEAD_END_RAD);
    headEndBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, HEAD_END_RAD);
    headEndBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect head to beak - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        beakStartBackTop,
        beakStartForwardTop,
        headEndForwardTop,
        headEndBackTop
    );
    quadobject_addQuad(
        birdPtr,
        beakStartBackTop,
        headEndBackTop,
        headEndBackBottom,
        beakStartBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        beakStartForwardBottom,
        headEndForwardBottom,
        headEndForwardTop,
        beakStartForwardTop
    );
    quadobject_addQuadBackwards(
        birdPtr,
        beakStartBackBottom,
        beakStartForwardBottom,
        headEndForwardBottom,
        headEndBackBottom
    );

    // Mid head part - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, HEAD_INNER_LENGTH);
    quadobject_moveNextX(birdPtr, -HEAD_INNER_X_SHIFT);
    quadobject_moveNextY(birdPtr, HEAD_INNER_SHIFT);
    quadobject_moveNextX(birdPtr, -HEAD_INNER_RAD / 2);
    headMidForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -HEAD_INNER_RAD);
    headMidForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, HEAD_INNER_RAD);
    headMidBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, HEAD_INNER_RAD);
    headMidBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to head end - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        headEndBackTop,
        headEndForwardTop,
        headMidForwardTop,
        headMidBackTop
    );
    quadobject_addQuad(
        birdPtr,
        headEndBackTop,
        headMidBackTop,
        headMidBackBottom,
        headEndBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        headEndForwardBottom,
        headMidForwardBottom,
        headMidForwardTop,
        headEndForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        headMidBackBottom,
        headMidForwardBottom,
        headEndForwardBottom,
        headEndBackBottom
    );

    // Start head part - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, HEAD_START_LENGTH);
    quadobject_moveNextX(birdPtr, -HEAD_START_X_SHIFT);
    quadobject_moveNextY(birdPtr, -HEAD_START_SHIFT);
    quadobject_moveNextX(birdPtr, -HEAD_START_RAD / 2);
    headStartForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -HEAD_START_RAD);
    headStartForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, HEAD_START_RAD);
    headStartBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, HEAD_START_RAD);
    headStartBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to head mid - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        headMidBackTop,
        headMidForwardTop,
        headStartForwardTop,
        headStartBackTop
    );
    quadobject_addQuad(
        birdPtr,
        headMidBackTop,
        headStartBackTop,
        headStartBackBottom,
        headMidBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        headMidForwardBottom,
        headStartForwardBottom,
        headStartForwardTop,
        headMidForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        headStartBackBottom,
        headStartForwardBottom,
        headMidForwardBottom,
        headMidBackBottom
    );

    quadobject_setNextColor(birdPtr, BACK_HEAD_R, BACK_HEAD_G, BACK_HEAD_B);

    // Front body part - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, BODY_FRONT_LENGTH);
    quadobject_moveNextX(birdPtr, -BODY_FRONT_X_SHIFT);
    quadobject_moveNextY(birdPtr, -BODY_FRONT_SHIFT);
    quadobject_moveNextX(birdPtr, -BODY_FRONT_RAD / 2);
    bodyFrontForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BODY_FRONT_RAD);
    bodyFrontForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, BODY_FRONT_RAD);
    bodyFrontBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BODY_FRONT_RAD);
    bodyFrontBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to head mid - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        headStartBackTop,
        headStartForwardTop,
        bodyFrontForwardTop,
        bodyFrontBackTop
    );
    quadobject_addQuad(
        birdPtr,
        headStartBackTop,
        bodyFrontBackTop,
        bodyFrontBackBottom,
        headStartBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        headStartForwardBottom,
        bodyFrontForwardBottom,
        bodyFrontForwardTop,
        headStartForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyFrontBackBottom,
        bodyFrontForwardBottom,
        headStartForwardBottom,
        headStartBackBottom
    );

    // Mid body part - 4 vert, 1 face

    quadobject_setNextColor(birdPtr, BODY_R, BODY_G, BODY_B);

    quadobject_moveNextZ(birdPtr, BODY_MID_LENGTH);
    quadobject_moveNextX(birdPtr, -BODY_MID_X_SHIFT);
    quadobject_moveNextY(birdPtr, -BODY_MID_SHIFT);
    quadobject_moveNextX(birdPtr, -BODY_MID_RAD / 2);
    bodyMidForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BODY_MID_RAD);
    bodyMidForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, BODY_MID_RAD);
    bodyMidBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BODY_MID_RAD);
    bodyMidBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        bodyFrontBackTop,
        bodyFrontForwardTop,
        bodyMidForwardTop,
        bodyMidBackTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyFrontBackTop,
        bodyMidBackTop,
        bodyMidBackBottom,
        bodyFrontBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        bodyFrontForwardBottom,
        bodyMidForwardBottom,
        bodyMidForwardTop,
        bodyFrontForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyMidBackBottom,
        bodyMidForwardBottom,
        bodyFrontForwardBottom,
        bodyFrontBackBottom
    );

    // Back body part - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, BODY_BACK_LENGTH);
    quadobject_moveNextX(birdPtr, -BODY_BACK_X_SHIFT);
    quadobject_moveNextY(birdPtr, -BODY_BACK_SHIFT);
    quadobject_moveNextX(birdPtr, -BODY_BACK_RAD / 2);
    bodyBackForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BODY_BACK_RAD);
    bodyBackForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, BODY_BACK_RAD);
    bodyBackBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BODY_BACK_RAD);
    bodyBackBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        bodyMidBackTop,
        bodyMidForwardTop,
        bodyBackForwardTop,
        bodyBackBackTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyMidBackTop,
        bodyBackBackTop,
        bodyBackBackBottom,
        bodyMidBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        bodyMidForwardBottom,
        bodyBackForwardBottom,
        bodyBackForwardTop,
        bodyMidForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyBackBackBottom,
        bodyBackForwardBottom,
        bodyMidForwardBottom,
        bodyMidBackBottom
    );

    // Back body part - 4 vert, 1 face
    quadobject_moveNextZ(birdPtr, BODY_REAR_LENGTH);
    quadobject_moveNextX(birdPtr, -BODY_REAR_X_SHIFT);
    quadobject_moveNextY(birdPtr, -BODY_REAR_SHIFT);
    quadobject_moveNextX(birdPtr, -BODY_REAR_RAD / 2);
    bodyRearForwardTop = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, -BODY_REAR_RAD);
    bodyRearForwardBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextX(birdPtr, BODY_REAR_RAD);
    bodyRearBackBottom = quadobject_addVer(birdPtr);
    quadobject_moveNextY(birdPtr, BODY_REAR_RAD);
    bodyRearBackTop = quadobject_addVer(birdPtr);
    quadobject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    quadobject_addQuad(
        birdPtr,
        bodyBackBackTop,
        bodyBackForwardTop,
        bodyRearForwardTop,
        bodyRearBackTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyBackBackTop,
        bodyRearBackTop,
        bodyRearBackBottom,
        bodyBackBackBottom
    );
    quadobject_addQuad(
        birdPtr,
        bodyBackForwardBottom,
        bodyRearForwardBottom,
        bodyRearForwardTop,
        bodyBackForwardTop
    );
    quadobject_addQuad(
        birdPtr,
        bodyRearBackBottom,
        bodyRearForwardBottom,
        bodyBackForwardBottom,
        bodyBackBackBottom
    );

    /* LEFT WING */

    quadobject_setNextColor(birdPtr, WING_R, WING_G, WING_B);

    // Create model curve - 5 vert, 0 face
    quadobject_moveNextZ(birdPtr, -BODY_REAR_LENGTH);
    quadobject_moveNextZ(birdPtr, -BODY_BACK_LENGTH);
    quadobject_moveNextX(birdPtr, -2);
    quadobject_moveNextY(birdPtr, -2);
    i = 0;
    frontTopLeftWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, -1);
    quadobject_moveNextX(birdPtr, -1);
    quadobject_moveNextY(birdPtr, 1);
    frontTopLeftWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, -1);
    quadobject_moveNextX(birdPtr, -1);
    quadobject_moveNextY(birdPtr, 0.5);
    frontTopLeftWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextX(birdPtr, -10);
    frontTopLeftWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, 4);
    quadobject_moveNextX(birdPtr, -2);
    quadobject_moveNextY(birdPtr, -1.3);
    frontTopLeftWing[i] = quadobject_addVer(birdPtr);
    i++;

    // Mirror points behind - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontTopLeftWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backTopLeftWing[i] = quadobject_addVer(birdPtr);
    }

    // Create faces on top - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadIndex = quadobject_addQuadBackwards(
            birdPtr,
            frontTopLeftWing[i],
            frontTopLeftWing[i-1],
            backTopLeftWing[i-1],
            backTopLeftWing[i]
        );
    }
    decoratedBirdPtr->startWingQuadIndex = quadIndex - (NUM_WING_GUIDE_POINTS - 1);

    // Mirror points below front - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontTopLeftWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1] - 1,
            curVer->pos[2]
        );
        frontBottomLeftWing[i] = quadobject_addVer(birdPtr);
    }

    // Mirror points below back - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontBottomLeftWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backBottomLeftWing[i] = quadobject_addVer(birdPtr);
    }

    // Create faces on bottom - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuad(
            birdPtr,
            frontBottomLeftWing[i],
            frontBottomLeftWing[i-1],
            backBottomLeftWing[i-1],
            backBottomLeftWing[i]
        );
    }

    // Create faces on edges - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuad(
            birdPtr,
            frontTopLeftWing[i],
            frontTopLeftWing[i-1],
            frontBottomLeftWing[i-1],
            frontBottomLeftWing[i]
        );
    }

    // Create faces on edges - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuadBackwards(
            birdPtr,
            backTopLeftWing[i],
            backTopLeftWing[i-1],
            backBottomLeftWing[i-1],
            backBottomLeftWing[i]
        );
    }

    // Seal off wing - 0 vert, 1 face
    quadobject_addQuadBackwards(
        birdPtr,
        frontTopLeftWing[NUM_WING_GUIDE_POINTS-1],
        backTopLeftWing[NUM_WING_GUIDE_POINTS-1],
        backBottomLeftWing[NUM_WING_GUIDE_POINTS-1],
        frontBottomLeftWing[NUM_WING_GUIDE_POINTS-1]
    );

    /* RIGHT WING */

    // Create model curve - 5 vert, 0 face
    curVer = quadobject_getVer(birdPtr, frontTopLeftWing[0]);
    quadobject_setNextPos(
        birdPtr,
        curVer->pos[0] + 3,
        curVer->pos[1],
        curVer->pos[2]
    );
    i = 0;
    frontTopRightWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, -1);
    quadobject_moveNextX(birdPtr, 1);
    quadobject_moveNextY(birdPtr, 1);
    frontTopRightWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, -1);
    quadobject_moveNextX(birdPtr, 1);
    quadobject_moveNextY(birdPtr, 0.5);
    frontTopRightWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextX(birdPtr, 10);
    frontTopRightWing[i] = quadobject_addVer(birdPtr);
    i++;

    quadobject_moveNextZ(birdPtr, 4);
    quadobject_moveNextX(birdPtr, 2);
    quadobject_moveNextY(birdPtr, -1.3);
    frontTopRightWing[i] = quadobject_addVer(birdPtr);
    i++;

    // Mirror points behind - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontTopRightWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backTopRightWing[i] = quadobject_addVer(birdPtr);
    }

    // Create faces on top - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuad(
            birdPtr,
            frontTopRightWing[i],
            frontTopRightWing[i-1],
            backTopRightWing[i-1],
            backTopRightWing[i]
        );
    }

    // Mirror points below front - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontTopRightWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1] - 1,
            curVer->pos[2]
        );
        frontBottomRightWing[i] = quadobject_addVer(birdPtr);
    }

    // Mirror points below back - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = quadobject_getVer(birdPtr, frontBottomRightWing[i]);
        quadobject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backBottomRightWing[i] = quadobject_addVer(birdPtr);
    }

    // Create faces on bottom - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuadBackwards(
            birdPtr,
            frontBottomRightWing[i],
            frontBottomRightWing[i-1],
            backBottomRightWing[i-1],
            backBottomRightWing[i]
        );
    }

    // Create faces on edges - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuadBackwards(
            birdPtr,
            frontTopRightWing[i],
            frontTopRightWing[i-1],
            frontBottomRightWing[i-1],
            frontBottomRightWing[i]
        );
    }

    // Create faces on edges - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadobject_addQuad(
            birdPtr,
            backTopRightWing[i],
            backTopRightWing[i-1],
            backBottomRightWing[i-1],
            backBottomRightWing[i]
        );
    }

    // Seal off wing - 0 vert, 1 face
    decoratedBirdPtr->endWingQuadIndex = quadobject_addQuad(
        birdPtr,
        frontTopRightWing[NUM_WING_GUIDE_POINTS-1],
        backTopRightWing[NUM_WING_GUIDE_POINTS-1],
        backBottomRightWing[NUM_WING_GUIDE_POINTS-1],
        frontBottomRightWing[NUM_WING_GUIDE_POINTS-1]
    );
}

void bird_draw(Bird * birdPtr)
{
    quadobject_draw(&(birdPtr->quadObject));
}

void bird_step(Bird * birdPtr, Boid * boids, int totalBirds, 
    PhysicsVector * obstacles, int numObstacles, float timestep)
{
    PhysicsVector from;

    PhysicsVector_init(&from, 0, 0, 0);

    Boid_step(birdPtr->boid, boids, totalBirds, obstacles, numObstacles,
        timestep, FALSE);
    birdPtr->quadObject.curX = Boid_getX(birdPtr->boid);
    birdPtr->quadObject.curY = Boid_getY(birdPtr->boid);
    birdPtr->quadObject.curZ = Boid_getZ(birdPtr->boid);
    birdPtr->quadObject.curPitch = linalg_calcPitchDeg(&from,
        &(birdPtr->boid->heading));

    if(rand() % 500 <= 1 && birdPtr->flapping == NOT_FLAPPING)
    {
        bird_flap(birdPtr);
    }
}
