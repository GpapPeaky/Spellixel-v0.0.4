#include "macros.h"
#include <iostream>
#include "sprites.h"
#include <time.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#ifndef LOAD_SPRITES
#define LOAD_SPRITES 

/* GENERAL USE VARIABLES */

extern SDL_Window* win;
extern SDL_Renderer* renderer;
extern SDL_Surface* sprite;
extern SDL_Texture *pltexture;
extern SDL_Cursor* CURSOR;

extern SDL_Texture* background_tile_texture1;
extern SDL_Texture* background_tile_texture2;
extern SDL_Texture* background_tile_texture3;
extern SDL_Texture* background_tile_texture4;

extern int true_x;
extern int true_y;

/**
 * @brief Initialises the window and the renderer
 * 
 * @param name Window name
*/
void load_sprite_init(const char* name);

// /**
//  * @brief Renders the generated background
// */
// void render_background(void);

// /**
//  * @brief Generates once the background to be used
// */
// void init_background(void);

#endif
