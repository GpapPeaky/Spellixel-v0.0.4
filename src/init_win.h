#include "def.aux"
#include "sprites.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#ifndef LOAD_SPRITES
#define LOAD_SPRITES 

/* GENERAL USE VARIABLES */

extern float render_factor;
extern int true_x;
extern int true_y;
extern SDL_Window* win;
extern SDL_Renderer* renderer;
extern SDL_Surface* sprite;
extern SDL_Texture *pltexture;
extern SDL_Cursor* CURSOR;

/**
 * @brief Initialises the window and the renderer
 * 
 * @param name Window name
*/
void load_sprite_init(const char* name);

#endif
