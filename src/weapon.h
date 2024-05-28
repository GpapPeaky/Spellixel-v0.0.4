#include "sound.h"
#include "init_win.h"
#include "fx.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>

extern std::vector<Sprite> bullets; /* Vector with all bullets shot */

#ifndef WEAPON
#define WEAPON

/**
 * @brief Handles Shooting
 * 
 * @param e Event for shooting
*/
void handle_shooting(SDL_Event& e);

/**
 * @brief Updates The Bullets Position
 * 
 * @param deltaTime Basis of each update
*/
void update_bullets(float deltaTime);

/**
 * @brief Renders the bullets shot by the player
*/
void render_player_bullets(void);

#endif 
