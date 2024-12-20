#include "init_win.h"
#include "utils.h"
#include "enemy.h"
#include "tiles.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#pragma once

extern int current_map_idx;
extern int total_rooms_count;

/* x -> 24, y -> 14 */
/* We need the tile size as well */

/**
 * @brief Loads a character map either for background or collisions
 * 
 * @param filename Name of file
 * 
 * @returns A 2D vector of integers each corresponding to a texture
*/
std::vector<std::vector<int>> load_map(const std::string& filename);

/**
 * @brief Renders the background tiles (no collisions)
 * 
 * @param map Map which it renders
 * 
 * @note WHENEVER A NEW TEXTURE IS ADDED, THE AMOUNT OF TEXTURES ALLOCATED IN THE TEXTURES ARRAY HAS TO BE INCREMENTED
*/
Render_t render_background_tiles(std::vector<std::vector<int>>& map);

/**
 * @brief Renders the background tiles (collisions)
 * 
 * @param map Map which it renders
 * 
 * @note WHENEVER A NEW TEXTURE IS ADDED, THE AMOUNT OF TILES ALLOCATED IN THE TILES ARRAY HAS TO BE INCREMENTED
*/
Render_t render_mesh_tiles(std::vector<std::vector<int>>& map);

/**
 * @brief Updates the loaded map
*/
Update_t update_loaded_map(void);
