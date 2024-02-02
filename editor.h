#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <dirent.h>
#include <regex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "macros.h"

#ifndef EDITOR
#define EDITOR

extern const int LOCAL_TILE_SIZE;
extern const int scrn_w;
extern const int scrn_h;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int currentTile;

/**
 * @brief Initialises the editor window
*/
void init();

/**
 * @brief Shows the next tile on click
 * 
 * @param e Click event
*/
void tile_on_click(SDL_Event& event);

/**
 * @brief Renders the tile map
*/
void render();

#endif /* EDITOR */
