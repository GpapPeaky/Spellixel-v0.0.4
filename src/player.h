#include <SDL2/SDL.h>
#include <unordered_set>
#include "fx.h"
#include "utils.h"
#include "weapon.h"
#include "macros.h"

#ifndef PLAYER
#define PLAYER

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
void render_player(void);

#endif