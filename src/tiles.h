#include "SDL2/SDL.h"
#include <vector>

#pragma once

typedef struct tile{
    int tile_id;
    SDL_Rect pos;
    SDL_Surface* sprite_bmp;
    SDL_Texture* sprite_texture;
}Tiles;

extern std::vector<struct tile> meshes;