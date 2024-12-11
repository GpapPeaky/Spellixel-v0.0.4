#include "utils.h"
#include "init_win.h"
#include "font.h"
#include "map_load.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#pragma once

extern SDL_Rect ui_rect;
extern SDL_Texture* ui_texture;

/* UI starts at y = 1024, and we have left 56 pixels to fills with data */

/**
 * @brief Initialises the ui assets
*/
Init_t init_ui(void);

/**
 * @brief Renders the ui's background
*/
Render_t render_ui_background(void);

/**
 * @brief Renders the player stats
*/
Render_t render_player_stats(void);

/**
 * @brief Complete method for rendering the UI
*/
Render_t render_UI(void);
