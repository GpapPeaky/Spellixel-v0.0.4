#include "auxf/def.aux"
#include "utils.h"
#include "sprites.h"
#include "init_win.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#pragma once

extern SDL_FRect shadow;

/**
 * @brief Draws a shadow for an entity
 * 
 * @param entity Entity to draw shadow for
 * @param w_fix_offset Width offset fix
*/
Render_t draw_sprite_shadow(Sprite entity, int w_fix_offset);

/**
 * @brief Draws a shadow for a bullet
 * 
 * @param bul bullet to draw shadow for
*/
Render_t draw_bullet_shadow(Bullet bul);
