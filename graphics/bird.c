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
            QuadObject_getVer(quadObject, frontTopLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackTopLeftWing+i,
            QuadObject_getVer(quadObject, backTopLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontBottomLeftWing+i,
            QuadObject_getVer(quadObject, frontBottomLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackBottomLeftWing+i,
            QuadObject_getVer(quadObject, backBottomLeftWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontTopRightWing+i,
            QuadObject_getVer(quadObject, frontTopRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackTopRightWing+i,
            QuadObject_getVer(quadObject, backTopRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origFrontBottomRightWing+i,
            QuadObject_getVer(quadObject, frontBottomRightWing[i]),
            sizeof(ColoredVertex)
        );
        memcpy(
            origBackBottomRightWing+i,
            QuadObject_getVer(quadObject, backBottomRightWing[i]),
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
        if(birdPtr->flappingAmount >= 1)
            birdPtr->flapping = NOT_FLAPPING;
        else if(birdPtr->flappingAmount <= -0.5)
            birdPtr->flapping = FLAPPING_UP;

        if(birdPtr->flapping == FLAPPING_DOWN)
            birdPtr->flappingAmount -= 0.1;
        else if(birdPtr->flapping == FLAPPING_UP)
            birdPtr->flappingAmount += 0.1;

        for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
        {
            frontTopLeftWing = QuadObject_getVer(quadObject, birdPtr->frontTopLeftWing[i]);
            backTopLeftWing = QuadObject_getVer(quadObject, birdPtr->backTopLeftWing[i]);
            frontBottomLeftWing = QuadObject_getVer(quadObject, birdPtr->frontBottomLeftWing[i]);
            backBottomLeftWing = QuadObject_getVer(quadObject, birdPtr->backBottomLeftWing[i]);
            frontTopRightWing = QuadObject_getVer(quadObject, birdPtr->frontTopRightWing[i]);
            backTopRightWing = QuadObject_getVer(quadObject, birdPtr->backTopRightWing[i]);
            frontBottomRightWing = QuadObject_getVer(quadObject, birdPtr->frontBottomRightWing[i]);
            backBottomRightWing = QuadObject_getVer(quadObject, birdPtr->backBottomRightWing[i]);

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
            QuadObject_fixQuad(birdPtr, i);
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

    QuadObject_init(birdPtr, 76, 75);

    /* BEAK */

    QuadObject_setNextColor(birdPtr, BEAK_R, BEAK_G, BEAK_B);

    // End - 4 vert, 1 face
    /*QuadObject_setNextPos(
        birdPtr,
        0,
        BIRD_HEIGHT / 2,
        BIRD_LENGTH / 2
    );*/
    beakEndBackTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BEAK_INNER_SIDE_LEN);
    beakEndBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, -BEAK_INNER_SIDE_LEN);
    beakEndForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BEAK_INNER_SIDE_LEN);
    beakEndForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Start - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, BEAK_LENGTH);
    QuadObject_moveNextX(birdPtr, BEAK_SHIFT);
    QuadObject_moveNextY(birdPtr, BEAK_SHIFT);
    QuadObject_moveNextX(birdPtr, -BEAK_OUTER_SIDE_LEN / 2);
    beakStartForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BEAK_OUTER_SIDE_LEN);
    beakStartForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, BEAK_OUTER_SIDE_LEN);
    beakStartBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BEAK_OUTER_SIDE_LEN);
    beakStartBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Fill in - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        beakEndBackTop,
        beakEndForwardTop,
        beakStartForwardTop,
        beakStartBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        beakStartBackBottom,
        beakEndBackBottom,
        beakEndBackTop,
        beakStartBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        beakStartForwardTop,
        beakEndForwardTop,
        beakEndForwardBottom,
        beakStartForwardBottom
    );
    QuadObject_addQuad(
        birdPtr,
        beakStartBackBottom,
        beakStartForwardBottom,
        beakEndForwardBottom,
        beakEndBackBottom
    );

    /* HEAD */

    QuadObject_setNextColor(birdPtr, HEAD_R, HEAD_G, HEAD_B);

    // Front head part - 4 vert, 1 head
    QuadObject_moveNextZ(birdPtr, HEAD_END_LENGTH);
    QuadObject_moveNextX(birdPtr, -HEAD_END_SHIFT);
    QuadObject_moveNextY(birdPtr, HEAD_END_SHIFT);
    QuadObject_moveNextX(birdPtr, -HEAD_END_RAD / 2);
    headEndForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -HEAD_END_RAD);
    headEndForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, HEAD_END_RAD);
    headEndBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, HEAD_END_RAD);
    headEndBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect head to beak - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        beakStartBackTop,
        beakStartForwardTop,
        headEndForwardTop,
        headEndBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        beakStartBackTop,
        headEndBackTop,
        headEndBackBottom,
        beakStartBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        beakStartForwardBottom,
        headEndForwardBottom,
        headEndForwardTop,
        beakStartForwardTop
    );
    QuadObject_addQuadBackwards(
        birdPtr,
        beakStartBackBottom,
        beakStartForwardBottom,
        headEndForwardBottom,
        headEndBackBottom
    );

    // Mid head part - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, HEAD_INNER_LENGTH);
    QuadObject_moveNextX(birdPtr, -HEAD_INNER_X_SHIFT);
    QuadObject_moveNextY(birdPtr, HEAD_INNER_SHIFT);
    QuadObject_moveNextX(birdPtr, -HEAD_INNER_RAD / 2);
    headMidForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -HEAD_INNER_RAD);
    headMidForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, HEAD_INNER_RAD);
    headMidBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, HEAD_INNER_RAD);
    headMidBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to head end - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        headEndBackTop,
        headEndForwardTop,
        headMidForwardTop,
        headMidBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        headEndBackTop,
        headMidBackTop,
        headMidBackBottom,
        headEndBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        headEndForwardBottom,
        headMidForwardBottom,
        headMidForwardTop,
        headEndForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        headMidBackBottom,
        headMidForwardBottom,
        headEndForwardBottom,
        headEndBackBottom
    );

    // Start head part - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, HEAD_START_LENGTH);
    QuadObject_moveNextX(birdPtr, -HEAD_START_X_SHIFT);
    QuadObject_moveNextY(birdPtr, -HEAD_START_SHIFT);
    QuadObject_moveNextX(birdPtr, -HEAD_START_RAD / 2);
    headStartForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -HEAD_START_RAD);
    headStartForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, HEAD_START_RAD);
    headStartBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, HEAD_START_RAD);
    headStartBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to head mid - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        headMidBackTop,
        headMidForwardTop,
        headStartForwardTop,
        headStartBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        headMidBackTop,
        headStartBackTop,
        headStartBackBottom,
        headMidBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        headMidForwardBottom,
        headStartForwardBottom,
        headStartForwardTop,
        headMidForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        headStartBackBottom,
        headStartForwardBottom,
        headMidForwardBottom,
        headMidBackBottom
    );

    QuadObject_setNextColor(birdPtr, BACK_HEAD_R, BACK_HEAD_G, BACK_HEAD_B);

    // Front body part - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, BODY_FRONT_LENGTH);
    QuadObject_moveNextX(birdPtr, -BODY_FRONT_X_SHIFT);
    QuadObject_moveNextY(birdPtr, -BODY_FRONT_SHIFT);
    QuadObject_moveNextX(birdPtr, -BODY_FRONT_RAD / 2);
    bodyFrontForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BODY_FRONT_RAD);
    bodyFrontForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, BODY_FRONT_RAD);
    bodyFrontBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BODY_FRONT_RAD);
    bodyFrontBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to head mid - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        headStartBackTop,
        headStartForwardTop,
        bodyFrontForwardTop,
        bodyFrontBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        headStartBackTop,
        bodyFrontBackTop,
        bodyFrontBackBottom,
        headStartBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        headStartForwardBottom,
        bodyFrontForwardBottom,
        bodyFrontForwardTop,
        headStartForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyFrontBackBottom,
        bodyFrontForwardBottom,
        headStartForwardBottom,
        headStartBackBottom
    );

    // Mid body part - 4 vert, 1 face

    QuadObject_setNextColor(birdPtr, BODY_R, BODY_G, BODY_B);

    QuadObject_moveNextZ(birdPtr, BODY_MID_LENGTH);
    QuadObject_moveNextX(birdPtr, -BODY_MID_X_SHIFT);
    QuadObject_moveNextY(birdPtr, -BODY_MID_SHIFT);
    QuadObject_moveNextX(birdPtr, -BODY_MID_RAD / 2);
    bodyMidForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BODY_MID_RAD);
    bodyMidForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, BODY_MID_RAD);
    bodyMidBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BODY_MID_RAD);
    bodyMidBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        bodyFrontBackTop,
        bodyFrontForwardTop,
        bodyMidForwardTop,
        bodyMidBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyFrontBackTop,
        bodyMidBackTop,
        bodyMidBackBottom,
        bodyFrontBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        bodyFrontForwardBottom,
        bodyMidForwardBottom,
        bodyMidForwardTop,
        bodyFrontForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyMidBackBottom,
        bodyMidForwardBottom,
        bodyFrontForwardBottom,
        bodyFrontBackBottom
    );

    // Back body part - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, BODY_BACK_LENGTH);
    QuadObject_moveNextX(birdPtr, -BODY_BACK_X_SHIFT);
    QuadObject_moveNextY(birdPtr, -BODY_BACK_SHIFT);
    QuadObject_moveNextX(birdPtr, -BODY_BACK_RAD / 2);
    bodyBackForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BODY_BACK_RAD);
    bodyBackForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, BODY_BACK_RAD);
    bodyBackBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BODY_BACK_RAD);
    bodyBackBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        bodyMidBackTop,
        bodyMidForwardTop,
        bodyBackForwardTop,
        bodyBackBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyMidBackTop,
        bodyBackBackTop,
        bodyBackBackBottom,
        bodyMidBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        bodyMidForwardBottom,
        bodyBackForwardBottom,
        bodyBackForwardTop,
        bodyMidForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyBackBackBottom,
        bodyBackForwardBottom,
        bodyMidForwardBottom,
        bodyMidBackBottom
    );

    // Back body part - 4 vert, 1 face
    QuadObject_moveNextZ(birdPtr, BODY_REAR_LENGTH);
    QuadObject_moveNextX(birdPtr, -BODY_REAR_X_SHIFT);
    QuadObject_moveNextY(birdPtr, -BODY_REAR_SHIFT);
    QuadObject_moveNextX(birdPtr, -BODY_REAR_RAD / 2);
    bodyRearForwardTop = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, -BODY_REAR_RAD);
    bodyRearForwardBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextX(birdPtr, BODY_REAR_RAD);
    bodyRearBackBottom = QuadObject_addVer(birdPtr);
    QuadObject_moveNextY(birdPtr, BODY_REAR_RAD);
    bodyRearBackTop = QuadObject_addVer(birdPtr);
    QuadObject_createQuadFromPrev(birdPtr);

    // Connect to body front - 0 vert, 4 face
    QuadObject_addQuad(
        birdPtr,
        bodyBackBackTop,
        bodyBackForwardTop,
        bodyRearForwardTop,
        bodyRearBackTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyBackBackTop,
        bodyRearBackTop,
        bodyRearBackBottom,
        bodyBackBackBottom
    );
    QuadObject_addQuad(
        birdPtr,
        bodyBackForwardBottom,
        bodyRearForwardBottom,
        bodyRearForwardTop,
        bodyBackForwardTop
    );
    QuadObject_addQuad(
        birdPtr,
        bodyRearBackBottom,
        bodyRearForwardBottom,
        bodyBackForwardBottom,
        bodyBackBackBottom
    );

    /* LEFT WING */

    QuadObject_setNextColor(birdPtr, WING_R, WING_G, WING_B);

    // Create model curve - 5 vert, 0 face
    QuadObject_moveNextZ(birdPtr, -BODY_REAR_LENGTH);
    QuadObject_moveNextZ(birdPtr, -BODY_BACK_LENGTH);
    QuadObject_moveNextX(birdPtr, -2);
    QuadObject_moveNextY(birdPtr, -2);
    i = 0;
    frontTopLeftWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, -1);
    QuadObject_moveNextX(birdPtr, -1);
    QuadObject_moveNextY(birdPtr, 1);
    frontTopLeftWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, -1);
    QuadObject_moveNextX(birdPtr, -1);
    QuadObject_moveNextY(birdPtr, 0.5);
    frontTopLeftWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextX(birdPtr, -10);
    frontTopLeftWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, 4);
    QuadObject_moveNextX(birdPtr, -2);
    QuadObject_moveNextY(birdPtr, -1.3);
    frontTopLeftWing[i] = QuadObject_addVer(birdPtr);
    i++;

    // Mirror points behind - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = QuadObject_getVer(birdPtr, frontTopLeftWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backTopLeftWing[i] = QuadObject_addVer(birdPtr);
    }

    // Create faces on top - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        quadIndex = QuadObject_addQuadBackwards(
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
        curVer = QuadObject_getVer(birdPtr, frontTopLeftWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1] - 1,
            curVer->pos[2]
        );
        frontBottomLeftWing[i] = QuadObject_addVer(birdPtr);
    }

    // Mirror points below back - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = QuadObject_getVer(birdPtr, frontBottomLeftWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backBottomLeftWing[i] = QuadObject_addVer(birdPtr);
    }

    // Create faces on bottom - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        QuadObject_addQuad(
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
        QuadObject_addQuad(
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
        QuadObject_addQuadBackwards(
            birdPtr,
            backTopLeftWing[i],
            backTopLeftWing[i-1],
            backBottomLeftWing[i-1],
            backBottomLeftWing[i]
        );
    }

    // Seal off wing - 0 vert, 1 face
    QuadObject_addQuadBackwards(
        birdPtr,
        frontTopLeftWing[NUM_WING_GUIDE_POINTS-1],
        backTopLeftWing[NUM_WING_GUIDE_POINTS-1],
        backBottomLeftWing[NUM_WING_GUIDE_POINTS-1],
        frontBottomLeftWing[NUM_WING_GUIDE_POINTS-1]
    );

    /* RIGHT WING */

    // Create model curve - 5 vert, 0 face
    curVer = QuadObject_getVer(birdPtr, frontTopLeftWing[0]);
    QuadObject_setNextPos(
        birdPtr,
        curVer->pos[0] + 3,
        curVer->pos[1],
        curVer->pos[2]
    );
    i = 0;
    frontTopRightWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, -1);
    QuadObject_moveNextX(birdPtr, 1);
    QuadObject_moveNextY(birdPtr, 1);
    frontTopRightWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, -1);
    QuadObject_moveNextX(birdPtr, 1);
    QuadObject_moveNextY(birdPtr, 0.5);
    frontTopRightWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextX(birdPtr, 10);
    frontTopRightWing[i] = QuadObject_addVer(birdPtr);
    i++;

    QuadObject_moveNextZ(birdPtr, 4);
    QuadObject_moveNextX(birdPtr, 2);
    QuadObject_moveNextY(birdPtr, -1.3);
    frontTopRightWing[i] = QuadObject_addVer(birdPtr);
    i++;

    // Mirror points behind - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = QuadObject_getVer(birdPtr, frontTopRightWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backTopRightWing[i] = QuadObject_addVer(birdPtr);
    }

    // Create faces on top - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        QuadObject_addQuad(
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
        curVer = QuadObject_getVer(birdPtr, frontTopRightWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1] - 1,
            curVer->pos[2]
        );
        frontBottomRightWing[i] = QuadObject_addVer(birdPtr);
    }

    // Mirror points below back - 5 verts, 0 face
    for(i=0; i<NUM_WING_GUIDE_POINTS; i++)
    {
        curVer = QuadObject_getVer(birdPtr, frontBottomRightWing[i]);
        QuadObject_setNextPos(
            birdPtr,
            curVer->pos[0],
            curVer->pos[1],
            curVer->pos[2] + MID_WING_Z_LENGTHS[i]
        );
        backBottomRightWing[i] = QuadObject_addVer(birdPtr);
    }

    // Create faces on bottom - 0 verts, 4 faces
    for(i=1; i<NUM_WING_GUIDE_POINTS; i++)
    {
        QuadObject_addQuadBackwards(
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
        QuadObject_addQuadBackwards(
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
        QuadObject_addQuad(
            birdPtr,
            backTopRightWing[i],
            backTopRightWing[i-1],
            backBottomRightWing[i-1],
            backBottomRightWing[i]
        );
    }

    // Seal off wing - 0 vert, 1 face
    decoratedBirdPtr->endWingQuadIndex = QuadObject_addQuad(
        birdPtr,
        frontTopRightWing[NUM_WING_GUIDE_POINTS-1],
        backTopRightWing[NUM_WING_GUIDE_POINTS-1],
        backBottomRightWing[NUM_WING_GUIDE_POINTS-1],
        frontBottomRightWing[NUM_WING_GUIDE_POINTS-1]
    );
}

void bird_draw(Bird * birdPtr)
{
    QuadObject_draw(&(birdPtr->quadObject));
}

void bird_step(Bird * birdPtr, Boid * boids, int totalBirds, float timestep)
{
    Boid_step(birdPtr->boid, boids, totalBirds, timestep);
    birdPtr->quadObject.curX = Boid_getX(birdPtr->boid);
    birdPtr->quadObject.curY = Boid_getY(birdPtr->boid);
    birdPtr->quadObject.curZ = Boid_getZ(birdPtr->boid);
}
