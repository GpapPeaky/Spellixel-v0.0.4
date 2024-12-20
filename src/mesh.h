#include "init_win.h"
#include "map_load.h"
#include "sprites.h"
#include "auxf/def.aux"
#include <vector>
#include <algorithm>

#pragma once

/**
 * @brief Check collisions between the BULLETS and the meshes
 * 
 * @note This only covers bullets
*/
void mesh_bullet_collision(std::vector<Bullet>& bullet_vector);

/**
 * @brief Check collisions between the PLAYER and the meshes
 * 
 * @note This only checks the player ( pl )
*/
void mesh_player_collision(void);

/**
 * @brief Renders the meshes generated
*/
void render_meshes(void);

/**
 * @brief All meshes functions are included here
 * 
 * @param bullet_array Array of bullets to check for collisions
*/
void mesh_collisions(std::vector <Bullet> &bullet_array);

/**
 * @brief Updates meshes' position 
*/
void update_mesh_positions();
