/**
 * Name: birds.c
 * Desc: Hot air balloon display.
 * Auth: Sam Pottinger
 * Note: Help from http://www.swiftless.com/tutorials/opengl/camera2.html,
 *       http://www.gamedev.net/page/resources/_/technical/opengl/'
 *       lighting-and-normals-r1682, and http://www.cse.msu.edu/~cse872/
 *       tutorial3.html
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "../CSCIx229.h"

#include "flock.h"

#include "openglwrapper.h"
#include "balloon.h"
#include "bird.h"
#include "ground.h"

#define TITLE "title"

#define WIDTH 600
#define HEIGHT 500

#define PERSPECTIVE 1
#define ORTHOGRAPHIC 2

#define TRUE 1
#define FALSE 0

#define MAX_BALLOON_HEIGHT 300
#define MIN_BALLOON_HEIGHT 0

#define NUM_BIRDS 100

float lightPosition0[3]={20.0,50.0,20.0};
float lightAccumulator0 = 0;

float moveBy = 1;

int moveLight;

float ambient_0[4]={0.9,0.9,0.9,1.0};
float specular_0[4]={0.9,0.9,0.9,1.0};
float diffuse_0[4]={0.9,0.9,0.9,1.0};

// Mouse positions
float lastx = -1;
float lasty = -1;

// Camera mode
int cameraMode = PERSPECTIVE;
int lastWidth;
int lastHeight;

int balloon1Multiplier;
int balloon2Multiplier;
int balloon3Multiplier;
int balloon4Multiplier;

int textures[2];

// Balloons and ground
QuadObject balloon1;
QuadObject balloon2;
QuadObject balloon3;
QuadObject balloon4;
QuadObject ground;

Flock flock;

// Projection values
GLdouble dim=500;

// Azimuth and elevation of view angle
int th=0;
int ph=0;

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   // Reset view
   glLoadIdentity();

   //  Perspective - set eye position
   if (cameraMode == PERSPECTIVE)
   {
      double Ex = -2 * dim * trig_rad_sin(th) * trig_rad_cos(ph);
      double Ey = 2 * dim * trig_rad_sin(ph);
      double Ez = 2 * dim * trig_rad_cos(th) * trig_rad_cos(ph);
      gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, trig_rad_cos(ph), 0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   glScalef(1.8,1.8,1.8);
   glTranslatef(0,-100,10);

   objutil_ball(lightPosition0[0], lightPosition0[1], lightPosition0[2], 1);

   glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_0);
   glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_0);
   glLightfv(GL_LIGHT0,GL_SPECULAR,specular_0);

   glLightfv(GL_LIGHT0,GL_POSITION,lightPosition0);
   
   float emission_material[4]={0,0,0,1};
   float specular_material[4]={0.2,0.2,0.2,1.0};
   float ambient_material[4]={0.1,0.1,0.1,1.0};
   float shiny_material[1]={0};
   
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient_material);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_material);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny_material);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission_material);

   QuadObject_drawSpecific(&balloon1, 92, 0);
   QuadObject_drawSpecific(&balloon2, 92, 0);
   QuadObject_drawSpecific(&balloon3, 92, 0);
   QuadObject_drawSpecific(&balloon4, 92, 0);

   float yRadiationCenter = BALLOON_HEIGHT / 2;
   QuadObject_drawSpecificRadially(
      &balloon1,
      balloon1.numQuad,
      92,
      0,
      yRadiationCenter,
      0
   );
   QuadObject_drawSpecificRadially(
      &balloon2,
      balloon2.numQuad,
      92,
      0,
      yRadiationCenter,
      0
   );
   QuadObject_drawSpecificRadially(
      &balloon3,
      balloon3.numQuad,
      92,
      0,
      yRadiationCenter,
      0
   );
   QuadObject_drawSpecificRadially(
      &balloon4,
      balloon4.numQuad,
      92,
      0,
      yRadiationCenter,
      0
   );

   QuadObject_draw(&ground);

   // Draw birds
   Flock_draw(&flock);

   // Render scene and flip buffers
   glFlush();
   glutSwapBuffers();
}

/**
 * Name: animate()
 * Desc: Function that changes the height and rotation of the balloons.
**/
void animate()
{
   Flock_step(&flock);

   balloon1.curRot += moveBy;
   balloon2.curRot += moveBy * 1.25;
   balloon3.curRot += moveBy * 1.50;
   balloon4.curRot += moveBy * 1.75;

   if(balloon1.curY > MAX_BALLOON_HEIGHT || balloon1.curY < MIN_BALLOON_HEIGHT)
      balloon1Multiplier *= -1;
   balloon1.curY += moveBy * 0.1 * balloon1Multiplier;

   if(balloon2.curY > MAX_BALLOON_HEIGHT || balloon2.curY < MIN_BALLOON_HEIGHT)
      balloon2Multiplier *= -1;
   balloon2.curY += moveBy * 0.2 * balloon2Multiplier;

   if(balloon3.curY > MAX_BALLOON_HEIGHT || balloon3.curY < MIN_BALLOON_HEIGHT)
      balloon3Multiplier *= -1;
   balloon3.curY += moveBy * 0.3 * balloon3Multiplier;

   if(balloon4.curY > MAX_BALLOON_HEIGHT || balloon4.curY < MIN_BALLOON_HEIGHT)
      balloon4Multiplier *= -1;
   balloon4.curY += moveBy * 0.4 * balloon4Multiplier;

   if(moveLight)
   {
      lightAccumulator0 += 0.03;
   }
   lightPosition0[2] = cos(lightAccumulator0) * 100;
   lightPosition0[0] = sin(lightAccumulator0) * 100;

   glutPostRedisplay();
   glutTimerFunc(25,animate,0);
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
   gluPerspective (60, w2h, dim/4, 4*dim);

   //set the matrix back to model
   glMatrixMode (GL_MODELVIEW);
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
   if(key=='p')
   {
      if(moveLight)
         moveLight = FALSE;
      else
         moveLight = TRUE;
   }
   else if(key=='w')
   {
      lightPosition0[1] += 1;
   }
   else if(key=='s')
   {
      lightPosition0[1] -= 1;
   }

   else if (key==27)
   {
      exit(0);
   }
}

/**
 * Name: mouseMovement(int x, int y)
 * Desc: Function preodically called to adjust "camera" in response to mouse
 *       movements.
 * Para: x, The x position of the mouse.
 *       y, The y position of the mouse.
 * Note: To figure out how to attach this to the "camera," I got help from a
 *       tutorial at http://www.swiftless.com/tutorials/opengl/camera2.html
**/
void mouseMovement(int x, int y)
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
   th += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
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
   
   // Request 500 x 500 pixel window
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
   textures[0] = LoadTexBMP("crate.bmp");
   textures[1] = LoadTexBMP("groundsoil.bmp");

   // Create first balloon
   balloon_initBalloon(&balloon1, textures[0]);
   balloon1.curY = 30;

   // Create second balloon
   balloon_initBalloon(&balloon2, textures[0]);
   balloon2.curX = 50;
   balloon2.curZ = 50;
   balloon2.curY = 20;

   // Create third balloon
   balloon_initBalloon(&balloon3, textures[0]);
   balloon3.curX = -50;
   balloon3.curZ = -50;
   balloon3.curY = 30;

   // Create fourth balloon
   balloon_initBalloon(&balloon4, textures[0]);
   balloon4.curX = 0;
   balloon4.curZ = 50;
   balloon4.curY = 30;

   // Create the ground
   ground_initGround(&ground, textures[1]);
   ground.curY = -5;

   // Create many birds
   Flock_init(&flock, NUM_BIRDS);
   for(i=0; i<NUM_BIRDS; i++)
   {
      curBird = Flock_getBird(&flock, i);
      bird_randomizePosition(curBird);
      curBird->quadObject.xScale = 0.1;
      curBird->quadObject.yScale = 0.1;
      curBird->quadObject.zScale = 0.1;
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

   //  Tell GLUT to call "display" when the scene should be drawn
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

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}