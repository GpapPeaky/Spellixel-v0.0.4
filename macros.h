/**
 * @brief Basic definitions and macros that may require to be created for the main to function
*/

#ifndef MACROS
#define MACROS

extern int screen_x;
extern int screen_y;

#endif

#pragma region SCREEN

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MID_X SCREEN_WIDTH/2
#define MID_Y SCREEN_HEIGHT/2

#pragma endregion SCREEN

#pragma region  MAP_LOADER

#define TEXTURES 31 /* +1 The actual amount of textures excluding tile (0) ( or the last texture idx ) */

#define X_S 30
#define Y_S 16

#define ROOMS 4 /* AMOUNT OF ROOMS */

#pragma endregion MAP_LOADER

#pragma region PLAYER

#define __BULLET_SPEED__  700.0f
#define __SPEED_UP__ 70.0f
#define __SLOW_DOWN__ 0.8f
#define PLAYER_SIZE_X 60
#define PLAYER_SIZE_Y 60
#define SHOOTING_RATE 201 /* IDEA: Add as a field to the player sprite struct */

#pragma endregion PLAYER

#define RUNNING 0
#define NOT_RUNNING 1

/* Meshes */

#define MESH_SIZE 64 /* Has to be binary */

/**
 * @note ALL SPRITES LOADED WILL BE 4 * THEIR ACTUAL PIXEL SIZE IN ORDER TO MAINTAIN RELATIVE SIZES
 *              BETWEEN SPRITES, MAKES THE GAME MORE UNIFROM.
*/

/* Enemies */

/* IDEA: Add as a field to each enemy */

#define CHICKEN_SPEED 0.5f
#define SHEEP_SPEED 0.420f
#define JOHN_SPEED 0.469f

/* Sound */

#pragma region SOUND

#define VOLUME 20

#pragma endregion SOUND
/* Put here all general definitions like meshes arrays and bullet arrays, player Sprite types background Sprite type etc */
