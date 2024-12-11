#include "init_win.h"
#include "utils.h"

#pragma once

extern std::vector<Item> items; /* Saves all item textures to load here */
extern Item current_item;
extern Item podium;

/**
 * @brief Initialises the podium
*/
void init_podium(void);

/**
 * @brief Spawns an item, initialiser
 * 
 * @param x X axis
 * @param y Y axis
 * @param item_name The name of the item to spawn
*/
void spawn_item(int x, int y, std::string item_name);

/**
 * @brief Checks for collisions between the player and the item rectangle
*/
void item_player_collision(void);

/**
 * @brief Renders the item on the player
*/
void render_item_on_player(void);

/**
 * @brief Renders the item on the map
*/
void render_item(void);
