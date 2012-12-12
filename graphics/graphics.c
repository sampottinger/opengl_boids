/**
 * Name: graphics.c
 * Desc: Driver for visualization of boids flocking behavior.
 * Auth: Sam Pottinger
 * Note: Help from http://www.swiftless.com/tutorials/opengl/camera2.html,
 *       http://www.gamedev.net/page/resources/_/technical/opengl/'
 *       lighting-and-normals-r1682, and http://www.cse.msu.edu/~cse872/
 *       tutorial3.html
 * Licn: GNU GPL v2.
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "../CSCIx229.h"
#include "../flocking/physics.h"

#include "flock.h"

#include "openglwrapper.h"
#include "balloon.h"
#include "bird.h"
#include "ground.h"
#include "sky.h"
#include "tree.h"

// Camera positions
float xpos = 0, ypos = 50, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float lightPosition0[3]={SCENE_START_X / 2, 100.0, SCENE_START_Z / 2};
float lightAccumulator0 = 0;

float moveBy = 1;

int moveLight;

float ambient_0[4]={0.9,0.9,0.9,1.0};
float specular_0[4]={0.9,0.9,0.9,1.0};
float diffuse_0[4]={0.9,0.9,0.9,1.0};

// Boids params
float seperation_weight = 1.5;
float align_weight = 1.0;
float cohesion_weight = 1.0;

// Mouse positions
float lastx = -1;
float lasty = -1;

// Camera mode
int cameraMode = FIRST_PERSON;
int lastWidth;
int lastHeight;

int balloon1Multiplier;
int balloon2Multiplier;
int balloon3Multiplier;
int balloon4Multiplier;

int textures[NUM_TEXTURES];

// Balloons and ground
QuadObject balloon1;
QuadObject balloon2;
QuadObject balloon3;
QuadObject balloon4;
QuadObject ground;
QuadObject skybox;
QuadObject trees[NUM_TREES];

Flock flock;

// Projection values
GLdouble dim=500;

// Azimuth and elevation of view angle
int th=0;
int ph=0;

/**
 * Name: Print(const char * format, ...)
 * Desc: Text rendering function shamelessly taken from class.
 * Args: Conforms to printf
**/
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
    char buf[LEN];
    char* ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,format);
    vsnprintf(buf,LEN,format,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*ch++);
}

/**
 * Name: applyCamera()
 * Desc: Apply rotation and translation due to camera.
**/
void applyCamera()
{
    if(cameraMode == FIRST_PERSON)
    {
        // rotate our camera on the x-axis (left and right)
        glRotatef(xrot,1.0,0.0,0.0);

        // rotate our camera on the y-axis (up and down)
        glRotatef(yrot,0.0,1.0,0.0);

        // translate the screen to the position of our camera
        glTranslated(-xpos,-ypos,-zpos);
    }
    else if(cameraMode == THIRD_PERSON)
    {
        glTranslated(0,
            THIRD_PERSON_CAMERA_Y_OFFEST,
            THIRD_PERSON_CAMERA_Z_OFFEST
        );
        glRotatef(xrot,1.0,0.0,0.0);
        quadobject_drawSpecific(&balloon1, 92, 0);
        
        float yRadiationCenter = BALLOON_HEIGHT / 2;
        quadobject_drawSpecificRadially(
            &balloon1,
            balloon1.numQuad,
            92,
            0,
            yRadiationCenter,
            0
        );
        glRotatef(yrot,0.0,1.0,0.0);
        glTranslated(-xpos,-ypos,-zpos);
    }
}

/**
 * Name: display()
 * Desc: The function that draws all simulation objects and applies camera
 *       transforms.
**/
void display()
{
    int i;

    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Reset view
    glLoadIdentity();

    //  Perspective - set eye position
    if (cameraMode == PERSPECTIVE)
    {
        double Ex = -2 * dim * trig_rad_sin(th) * trig_rad_cos(ph);
        double Ey = 4 * dim * trig_rad_sin(ph);
        double Ez = 2 * dim * trig_rad_cos(th) * trig_rad_cos(ph);
        gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, trig_rad_cos(ph), 0);
    }
    else if(cameraMode == FIRST_PERSON || cameraMode == THIRD_PERSON)
    {
        applyCamera();
    }
    //  Orthogonal - set world orientation
    else
    {
        glRotatef(ph,1,0,0);
        glRotatef(th,0,1,0);
    }

    glScalef(1.8,1.8,1.8);
    glTranslatef(0,-100,10);

    // Draw skybox
    sky_draw(&skybox);

    // Draw sun
    objutil_ball(lightPosition0[0], lightPosition0[1], lightPosition0[2], 1);

    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_0);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular_0);

    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition0);
   
    // Set materials
    float emission_material[4]={0,0,0,1};
    float specular_material[4]={0.2,0.2,0.2,1.0};
    float ambient_material[4]={0.1,0.1,0.1,1.0};
    float shiny_material[1]={0};
   
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient_material);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_material);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny_material);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission_material);

    balloon_draw(&balloon2);
    balloon_draw(&balloon3);
    balloon_draw(&balloon4);

    quadobject_draw(&ground);

    // Draw birds
    flock_draw(&flock);

    // Draw plants
    for(i=0; i<NUM_TREES; i++)
        quadobject_draw(trees+i);

    // Display current weights
    glColor3f(1,1,1);

    // Display mode specific message
    if(cameraMode == PERSPECTIVE)
    {
        glWindowPos2i(10,35);
        Print(
            "distance: %f, align: %f, cohesion: %f. Use d / D, a / A, and c / C to adjust. The v key changes modes. w will increase height of sun and s will decrease it.",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
        glWindowPos2i(10,50);
        Print(
            "> overview mode   _ free flight mode   _ balloon flying mode",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
    }
    else if(cameraMode == FIRST_PERSON)
    {
        glWindowPos2i(10,35);
        Print(
            "Use w, s, a, and d to move. The v key will change view modes.",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
        glWindowPos2i(10,50);
        Print(
            "_ overview mode   > free flight mode   _ balloon flying mode",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
    }
    else if(cameraMode == THIRD_PERSON)
    {
        glWindowPos2i(10,35);
        Print(
            "Use w, s, a, and d to move. The v key will change view modes.",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
        glWindowPos2i(10,50);
        Print(
            "_ overview mode   _ free flight mode   > balloon flying mode",
            seperation_weight,
            align_weight,
            cohesion_weight
        );
    }

    // Render scene and flip buffers
    glFlush();
    glutSwapBuffers();
}

/**
 * Name: copyQuadObjPosToVector(QuadObject * quadObj, PhysicsVector * vector)
 * Desc: Copy the current location of a quad object to a PhysicsVector for use
 *       in boid simulation.
 * Para: quadObj, The object to copy the position from.
 *       vector, The vector to copy the position into.
**/
void copyQuadObjPosToVector(QuadObject * quadObj, PhysicsVector * vector)
{
    PhysicsVector_init(vector, quadObj->x, quadObj->y, quadObj->z);
}

/**
 * Name: animate()
 * Desc: Function that changes the height and rotation of the balloons.
**/
void animate()
{
    PhysicsVector balloonObstacles[4];
    copyQuadObjPosToVector(&balloon2, balloonObstacles+0);
    copyQuadObjPosToVector(&balloon3, balloonObstacles+1);
    copyQuadObjPosToVector(&balloon4, balloonObstacles+2);

    if(cameraMode == PERSPECTIVE)
    {
        flock_step(&flock, balloonObstacles, 3);
    }
    else if(cameraMode == FIRST_PERSON || cameraMode == THIRD_PERSON)
    {
        PhysicsVector_init(balloonObstacles+3, xpos, ypos, zpos);
        flock_step(&flock, balloonObstacles, 4);
    }

    // Rotate balloons
    balloon2.curRot += moveBy * BALLOON_2_ROT_RATE;
    balloon3.curRot += moveBy * BALLOON_3_ROT_RATE;
    balloon4.curRot += moveBy * BALLOON_4_ROT_RATE;

    // Move balloon 2 (balloon controlled by user)
    if(balloon2.curY > MAX_BALLOON_HEIGHT || balloon2.curY < MIN_BALLOON_HEIGHT)
        balloon2Multiplier *= -1;
    balloon2.curY += moveBy * BALLOON_2_Y_MOVE_RATE * balloon2Multiplier;

    // Move balloon 3
    if(balloon3.curY > MAX_BALLOON_HEIGHT || balloon3.curY < MIN_BALLOON_HEIGHT)
        balloon3Multiplier *= -1;
    balloon3.curY += moveBy * BALLOON_3_Y_MOVE_RATE * balloon3Multiplier;

    // Move balloon 4
    if(balloon4.curY > MAX_BALLOON_HEIGHT || balloon4.curY < MIN_BALLOON_HEIGHT)
        balloon4Multiplier *= -1;
    balloon4.curY += moveBy * BALLOON_4_Y_MOVE_RATE * balloon4Multiplier;

    // Move the sun object
    if(moveLight)
    {
        lightAccumulator0 += LIGHT_ROT_RATE;
    }
    lightPosition0[2] = cos(lightAccumulator0) * LIGHT_ROT_RADIUS;
    lightPosition0[0] = sin(lightAccumulator0) * LIGHT_ROT_RADIUS;

    // Schedule call to this animate function again.
    glutPostRedisplay();
    glutTimerFunc(UPDATE_FREQUENCY, animate, 0);
}

/**
 * Name: setUpPerspective()
 * Desc: Sets up perspective for the application.
**/
void setUpPerspective()
{
   glEnable(GL_DEPTH_CLAMP);

   //set the viewport to the current window specifications
   glViewport (0, 0, (GLsizei)lastWidth, (GLsizei)lastHeight);

   //set the matrix to projection
   glMatrixMode (GL_PROJECTION);

   glLoadIdentity ();
   //set the perspective (angle of sight, width, height, , depth)
   double w2h = (lastHeight>0) ? (double)lastWidth/lastHeight : 1;
   gluPerspective (60, w2h, dim/16, 16*dim);

   //set the matrix back to model
   glMatrixMode (GL_MODELVIEW);
}

/**
 * Name: keyboardFPS(unsigned char key, int x, int y)
 * Desc: Respond to keyboard events while in first person perspective mode.
 * Para: key, The key pressed that needs to be responded to.
 *       x, The x position of the mouse cursor when the key was pressed.
 *       y, The y position of the mouse cursor when the key was pressed.
**/
void keyboardFPS(unsigned char key, int x, int y)
{
    float xrotrad, yrotrad;

    // Quit
    if (key=='q')
    {
        xrot += 1;
        if (xrot >360)
            xrot -= 360;
    }

    // Rotate left
    if (key=='z')
    {
        xrot -= 1;
        if (xrot < -360)
            xrot += 360;
    }

    // Move forward
    if (key=='w')
    {
        yrotrad = (yrot / 180 * PI);
        xrotrad = (xrot / 180 * PI);
        xpos += (float)(sin(yrotrad)) * FPS_FORWARD_AMOUNT;
        zpos -= (float)(cos(yrotrad)) * FPS_FORWARD_AMOUNT;
        ypos -= (float)(sin(xrotrad)) * FPS_FORWARD_AMOUNT;
    }

    // Move backwards
    if (key=='s')
    {
        yrotrad = (yrot / 180 * PI);
        xrotrad = (xrot / 180 * PI); 
        xpos -= (float)(sin(yrotrad));
        zpos += (float)(cos(yrotrad));
        ypos += (float)(sin(xrotrad));
    }

    // Side step right
    if (key=='d')
    {
        yrotrad = (yrot / 180 * PI);
        xpos += (float)(cos(yrotrad)) * 0.2;
        zpos += (float)(sin(yrotrad)) * 0.2;
    }

    // Side step left
    if (key=='a')
    {
        yrotrad = (yrot / 180 * PI);
        xpos -= (float)(cos(yrotrad)) * 0.2;
        zpos -= (float)(sin(yrotrad)) * 0.2;
    }

    // Chnage view
    if(key=='v')
    {
        if(cameraMode == FIRST_PERSON)
        {
            cameraMode = THIRD_PERSON;
        }
        else if(cameraMode == THIRD_PERSON)
        {
            cameraMode = PERSPECTIVE;
            setUpPerspective();
        }
    }

    // Ensure positions in range
    if(xpos < MIN_X)
      xpos = MIN_X;
    else if(xpos > MAX_X)
      xpos = MAX_X;

    if(ypos < MIN_Y)
      ypos = MIN_Y;
    else if(ypos > MAX_Y)
      ypos = MAX_Y;

    if(zpos < MIN_Z)
      zpos = MIN_Z;
    else if(zpos > MAX_Z)
      zpos = MAX_Z;

    // Quit
    if (key==27)
    {
        exit(0);
    }
}


/**
 * Name: keyboardOverview(unsigned char key, int x, int y)
 * Desc: Respond to keyboard events while in overview perspective.
 * Para: key, The key pressed.
 *       x, The x position of the mouse cursor when the key was pressed.
 *       y, The y position of the mouse cursor when the key was pressed.
**/
void keyboardOverview(unsigned char key, int x, int y)
{
    // Pause movement of light
    if(key=='p')
    {
        if(moveLight)
            moveLight = FALSE;
        else
            moveLight = TRUE;
    }

    // Increase altitude of light
    else if(key=='w')
    {
        lightPosition0[1] += 1;
    }

    // Decrease altitude of light
    else if(key=='s')
    {
        lightPosition0[1] -= 1;
    }

    // Increase amount of seperation in boid simulation
    else if(key=='D')
    {
        seperation_weight += 0.1;
    }

    // Decrease amount of seperation in boid simulation
    else if(key=='d')
    {
        seperation_weight -= 0.1;
    }

    // Increase amount of orientation alignment in boid simulation
    else if(key=='A')
    {
        align_weight += 0.1;
    }

    // Decrease amount of orientation alignment in boid simulation
    else if(key=='a')
    {
        align_weight -= 0.1;
    }

    // Increase amount of cohesion in boid simulation
    else if(key=='C')
    {
        cohesion_weight += 0.1;
    }

    // Decrease amount of cohesion in boid simulation
    else if(key=='c')
    {
        cohesion_weight -= 0.1;
    }

    // Change view mode
    else if(key=='v')
    {
        cameraMode = FIRST_PERSON;
    }

    // Quict
    else if (key==27)
    {
        exit(0);
    }

    // Update boid simulation behavior
    flock_setWeights(&flock, seperation_weight, align_weight, cohesion_weight);
}

/**
 * Name: keyboard(unsigned char key, int x, int y)
 * Desc: Allows FPS-style movement of the "camera" via keyboard keys.
 * Para: key, The key pressed.
 *       x, The x position of the mouse cursor when the key was pressed.
 *       y, The y position of the mouse cursor when the key was pressed.
 * Note: Got some help from http://www.swiftless.com/tutorials/opengl/
 *       camera2.html
**/
void keyboard(unsigned char key, int x, int y)
{
  if(cameraMode == PERSPECTIVE)
    keyboardOverview(key, x, y);
  else if(cameraMode == FIRST_PERSON || cameraMode == THIRD_PERSON)
    keyboardFPS(key, x, y);
}

/**
 * Name: mouseMovementFPS(int x, int y)
 * Desc: Function preodically called to adjust "camera" in response to mouse
 *       movements when in first person or third person mode.
 * Para: x, The x position of the mouse.
 *       y, The y position of the mouse.
 * Note: To figure out how to attach this to the "camera," I got help from a
 *       tutorial at http://www.swiftless.com/tutorials/opengl/camera2.html
**/
void mouseMovementFPS(int x, int y)
{
   int diffx=x-lastx; //check the difference between the  current x and the last x position
   int diffy=y-lasty; //check the difference between the  current y and the last y position
   lastx=x; //set lastx to the current x position
   lasty=y; //set lasty to the current y position
   xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
   yrot += (float) diffx; //set the xrot to yrot with the addition of the difference in the x position
}

/**
 * Name: mouseMovementOverview(int x, int y)
 * Desc: Function preodically called to adjust "camera" in response to mouse
 *       movements while in overview mode.
 * Para: x, The x position of the mouse.
 *       y, The y position of the mouse.
**/
void mouseMovementOverview(int x, int y)
{
    if(lastx == -1 || lasty == -1)
    {
        lastx = x;
        lasty = y;
        return;
    }

    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    ph += (float) diffy * 2; //set the xrot to xrot with the addition of the difference in the y position
    th += (float) diffx; //set the xrot to yrot with the addition of the difference in the x position
}

/**
 * Name: mouseMovement(int x, int y)
 * Desc: Function preodically called to adjust "camera" in response to mouse
 *       movements.
 * Para: x, The x position of the mouse.
 *       y, The y position of the mouse.
**/
void mouseMovement(int x, int y)
{
    if(cameraMode == PERSPECTIVE)
        mouseMovementOverview(x, y);
    else
        mouseMovementFPS(x, y);
}

/**
 * Name: handleReshape(int width, int height)
 * Desc: Callback for when the window is resized.
 * Args: width, The new width of the window.
 *       height, The new height of the window.
 * Note: I was messing around with glutEnterGameMode and I changed this slightly
 *       from what was provided in class with help from
 *       http://www.swiftless.com/tutorials/opengl/fullscreen.html
**/
void handleReshape(int width,int height)
{
   lastWidth = width;
   lastHeight = height;
   setUpPerspective();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
    Bird * curBird;
    int i;

    // Initialize GLUT and process user parameters
    glutInit(&argc,argv);

    // Request double buffered, true color window with Z buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   
    // Request window
    glutInitWindowSize(WIDTH, HEIGHT);
    lastWidth = WIDTH;
    lastHeight = HEIGHT;
   
    // Create the window
    glutCreateWindow(TITLE);

    // Enable face culling
    glEnable(GL_CULL_FACE);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Load textures
    textures[CRATE_TEXTURE_INDEX] = LoadTexBMP("crate.bmp");
    textures[GROUND_TEXTURE_INDEX] = LoadTexBMP("groundsoil.bmp");
    textures[SKY_TOP_TEXTURE_INDEX] = LoadTexBMP("sky_top.bmp");
    textures[SKY_LEFT_TEXTURE_INDEX] = LoadTexBMP("sky_left.bmp");
    textures[SKY_BACK_TEXTURE_INDEX] = LoadTexBMP("sky_back.bmp");
    textures[SKY_RIGHT_TEXTURE_INDEX] = LoadTexBMP("sky_right.bmp");
    textures[SKY_FRONT_TEXTURE_INDEX] = LoadTexBMP("sky_front.bmp");
    textures[SKY_BOTTOM_TEXTURE_INDEX] = LoadTexBMP("sky_bottom.bmp");
    textures[TREE_BARK_INDEX] = LoadTexBMP("tree_bark.bmp");
    textures[TREE_LEAVES_INDEX] = LoadTexBMP("tree_leaves.bmp");

    // Create first balloon
    balloon_initBalloon(&balloon1, textures[CRATE_TEXTURE_INDEX]);
    
    // Create second balloon
    balloon_initBalloon(&balloon2, textures[CRATE_TEXTURE_INDEX]);
    balloon2.curX = 50;
    balloon2.curZ = 50;
    balloon2.curY = 60;

    // Create third balloon
    balloon_initBalloon(&balloon3, textures[CRATE_TEXTURE_INDEX]);
    balloon3.curX = -50;
    balloon3.curZ = -50;
    balloon3.curY = 60;

    // Create fourth balloon
    balloon_initBalloon(&balloon4, textures[CRATE_TEXTURE_INDEX]);
    balloon4.curX = 0;
    balloon4.curZ = 50;
    balloon4.curY = 60;

    // Create the ground
    ground_initGround(&ground, textures[GROUND_TEXTURE_INDEX]);
    ground.curY = -5;

    sky_initSky(&skybox, textures + SKY_TEXTURES_START_INDEX);
    skybox.curY = -5.1;

    // Create plants
    for(i=0; i<NUM_TREES; i++)
    {
        tree_initTree(trees+i, textures + TREE_TEXTURES_START_INDEX);
        trees[i].curX = rand() % SCENE_WIDTH + SCENE_START_X;
        trees[i].curY = -3;
        trees[i].curZ = rand() % SCENE_DEPTH + SCENE_START_Z;
        trees[i].xScale = 0.4;
        trees[i].yScale = 0.7;
        trees[i].zScale = 0.4;
    }

    // Create many birds
    flock_init(&flock, NUM_BIRDS);
    for(i=0; i<NUM_BIRDS; i++)
    {
        curBird = flock_getBird(&flock, i);
        bird_randomizePosition(curBird);
        curBird->quadObject.xScale = 0.3;
        curBird->quadObject.yScale = 0.3;
        curBird->quadObject.zScale = 0.3;
    }

    // Set up lighting
    glShadeModel(GL_SMOOTH); // Smooth shading
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

    glEnable(GL_CULL_FACE);

    glEnable(GL_NORMALIZE);

    // Start by going up
    balloon1Multiplier = 1;
    balloon2Multiplier = 1;
    balloon3Multiplier = 1;
    balloon4Multiplier = 1;

    moveLight = TRUE;

    // Set up perspective
    setUpPerspective();

    // Tell GLUT to call "display" when the scene should be drawn
    glutDisplayFunc(display);

    // Register callback for resizing window
    glutReshapeFunc(handleReshape);

    // Register callback for animation
    glutTimerFunc(25,animate,0);

    // Register callback for keyboard taps
    glutKeyboardFunc(keyboard);

    // Check for mouse movement
    glutPassiveMotionFunc(mouseMovement);

    // Go full screen to capture mouse
    glutFullScreen();

    // Pass control to GLUT so it can interact with the user
    glutMainLoop();
    return 0;
}