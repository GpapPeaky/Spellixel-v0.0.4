#include "auxf/def.aux"
#include "SDL2/SDL.h"
#include "enemy.h"
#include "item.h"
#include "fx.h"
#include "utils.h"
#include "weapon.h"
#include <unordered_set>

#pragma once

/**
 * @brief Handles player input (Movement)
 * @param e Event related to movement
 * 
 * @bug No diagonal movement
*/
void handle_input(SDL_Event& e);

/**
 * @brief Updates the player position
 * 
 * @param deltaTime Basis of each update
*/
void update_player(float deltaTime);

/**
 * @brief Renders the player model
*/
void render_player_and_enemies(void);
