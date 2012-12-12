/**
 * Name: constants.h
 * Desc: 3D presentation constants for boids visualization.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#ifndef GRAPHICS_CONSTANTS
#define GRAPHICS_CONSTANTS

#define MAX_X 300
#define MAX_Y 500
#define MAX_Z 300
#define MIN_X -300
#define MIN_Y 0
#define MIN_Z -300

#define TITLE "Boids Simulation"

#define WIDTH 600
#define HEIGHT 500

#define PERSPECTIVE 1
#define ORTHOGRAPHIC 2
#define FIRST_PERSON 3
#define THIRD_PERSON 4

#define TRUE 1
#define FALSE 0

#define MAX_BALLOON_HEIGHT 300
#define MIN_BALLOON_HEIGHT 50

#define NUM_BIRDS 100

#define NUM_TREES 150

#define FPS_FORWARD_AMOUNT 5

#define UPDATE_FREQUENCY 25

#define THIRD_PERSON_CAMERA_Y_OFFEST -20
#define THIRD_PERSON_CAMERA_Z_OFFEST -50

#define BALLOON_2_ROT_RATE 1.25
#define BALLOON_3_ROT_RATE 1.5
#define BALLOON_4_ROT_RATE 1.75

#define BALLOON_2_Y_MOVE_RATE 0.2
#define BALLOON_3_Y_MOVE_RATE 0.3
#define BALLOON_4_Y_MOVE_RATE 0.4

#define LIGHT_ROT_RATE 0.03
#define LIGHT_ROT_RADIUS 320

#define SKY_TEXTURES_START_INDEX 2
#define TREE_TEXTURES_START_INDEX 8

#define CRATE_TEXTURE_INDEX 0
#define GROUND_TEXTURE_INDEX 1
#define SKY_TOP_TEXTURE_INDEX 2
#define SKY_LEFT_TEXTURE_INDEX 3
#define SKY_BACK_TEXTURE_INDEX 4
#define SKY_RIGHT_TEXTURE_INDEX 5
#define SKY_FRONT_TEXTURE_INDEX 6
#define SKY_BOTTOM_TEXTURE_INDEX 7
#define TREE_BARK_INDEX 8
#define TREE_LEAVES_INDEX 9

#define NUM_TEXTURES 10

#endif