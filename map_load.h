#include "init_win.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#ifndef MAP_LOAD
#define MAP_LOAD

typedef struct tile{
    int tile_id;
    SDL_Rect pos;
    SDL_Surface* sprite_bmp;
    SDL_Texture* sprite_texture;
}Tiles;

extern std::vector<struct tile> meshes;
extern int current_map_idx;

#endif

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
void render_background_tiles(std::vector<std::vector<int>>& map );

/**
 * @brief Renders the background tiles (collisions)
 * 
 * @param map Map which it renders
 * 
 * @note WHENEVER A NEW TEXTURE IS ADDED, THE AMOUNT OF TILES ALLOCATED IN THE TILES ARRAY HAS TO BE INCREMENTED
*/
void render_mesh_tiles(std::vector<std::vector<int>>& map );
