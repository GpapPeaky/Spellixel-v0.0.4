#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <dirent.h>
#include <regex> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "def.aux"
#include "utils.h"

/* TODO: Replace regex */

#ifndef EDITOR
#define EDITOR

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int current_tile;

/**
 * @brief Initialises the editor window
*/
void init(void);

/**
 * @brief Shows the next tile on click
 * 
 * @param e Click event
*/
void tile_on_click(SDL_Event& event); /* Update type */

/**
 * @brief Renders the tile map
*/
void render(void);

#endif /* EDITOR */
