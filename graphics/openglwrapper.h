/**
 * Name: openglwrapper.h
 * Desc: Simplified header file for including OpenGL cross-platform.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef OPEN_GL_LOADED
#define OPEN_GL_LOADED

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#endif