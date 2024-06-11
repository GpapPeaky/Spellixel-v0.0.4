#include "init_win.h"
#include "def.aux"
#include "mesh.h"
#include "utils.h"
#include "fx.h"
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <string>

#ifndef ENEMY
#define ENEMY

extern SDL_Color e_text_colour;
extern SDL_Color e_text_colour_bg;
extern SDL_Surface* e_text;
extern SDL_Texture* e_txt;
extern SDL_Texture* e_b_txt;
extern TTF_Font* e_font;
extern SDL_FRect e_rect;
extern SDL_FRect e_b_rect;
extern SDL_FRect e_c_rect;

typedef enum enemy_t{
    agressive, /* They attack */
    passive, /* They are standing */
    healing /* They heal you */
}enemy_t;

typedef struct max{
    int x;
    int y;
}max;

typedef struct min{
    int x;
    int y;
}min;

typedef struct wander{
    max max;
    min min;
}wander;

typedef struct Enemy{
    Sprite sprite;
    wander wander;
    float speed;
    std::string name;
    enemy_t type;
    bool damaged;
    int damage_taken;
}Enemy;

extern std::vector<Enemy> enemies;

/**
 * @brief Init enemy font
*/
Init_t init_enemy_font(void);
/**
 * @brief Renders The damage taken by an enemy
 * 
 * @param dmg_taken Damage taken
 * @param position Position of text
*/
Render_t render_damaged_enemies(int dmg_taken, SDL_FRect* position);

/**
 * @brief Creates a chicken enemy
 * 
 * @note May have to be passed onto a vector
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @warning Shoots eggs, but they deal no damage (They heal you by one)
 * 
 * @returns An enemy type
*/
Enemy chicken(int x, int y);

/**
 * @brief TEMP adds random movement
 * 
 * @note Will be changed later
*/
void update_enemy_movement();

/**
 * @brief Renders the enemies
*/
void render_enemies();

/**
 * @brief Creates a sheep enemy
 * 
 * @note May have to be passed onto a vector
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @returns An enemy type
*/
Enemy sheep(int x, int y);

/**
 * @brief John
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @warning Shouldn't be confused with an enemy. he wont attack
 * 
 * @returns An enemy type
*/
Enemy john(int x , int y);

/**
 * @brief H I L B E R T
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @warning Shouldn't be confused with an enemy. he wont attack
 * 
 * @returns An enemy type
*/
Enemy hilbert(int x , int y);

/**
 * @brief Goblin peasant
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @warning He will attack
 * 
 * @returns An enemy type
*/
Enemy goblin(int x, int y);

/**
 * @brief villager peasant
 * 
 * @param x axis position
 * @param y axis position
 * 
 * @warning He will attack
 * 
 * @returns An enemy type
*/
Enemy villager(int x, int y);

/**
 * @brief Function that depending on what enemy is shooting, it shoots something different at different rates
 * 
 * @param reload_speed After how many frames , every enemy reloads
*/
void shoot(float reload_speed);
/* TODO: ADD RELOAD TIMERS AS A FIELD TO EACH ENEMY */

/**
 * @brief Checks if a bullet has hit a mesh
 * 
 * @param bullet Bullet object
 * 
 * @returns TRUE if it hits
 *                     FALSE if it does not
*/
bool bullet_hits_mesh(const Bullet& bullet);

/**
 * @brief Checks if a bullet has hit the player
 * 
 * @param bullet Bullet object
 * 
 * @returns TRUE if it hits
 *                     FALSE if it does not
*/
bool bullet_hits_player(const Bullet& bullet);

/**
 * @brief Checks if a bullet runs offscreen
 * 
 * @param bullet Bullet object
 * 
 * @return TRUE if offscreen
 *                  FALSE if on-screen
*/
bool bullet_offscreen(const Bullet& bullet);

/**
 * @brief Updates all enemy bullets
 * 
 * @param dt Time elapsed since the last update
*/
void update_enemy_bullets(float dt);

/**
 * @brief Renders the bullets of each enemy
 * 
 * @param enemies The vector containing all enemies
*/
void render_enemy_bullets(void);

/**
 * @brief Updates the enemies state (dead/alive)
*/
void update_enemy(void);

/* TODO: MAKE THE ENEMY BULLET ARRAY NOT CLEAR AFTER THE ENEMIES DEATH */

/*
    TODO: Make a village guard
                Make wolves
                Make bandits
                Make mouse hover font
                Make HP bars, and Sprite field
                Make AD stat as a field in the Sprite struct
                Make all stats as fields in the Sprite struct
*/

/**
 * @brief Handles all enemy updates
 * 
 * @param dt Timer
*/
void enemy_updates(float dt);

/**
 * @brief Prints All Registered Enemies
 */
void print_enemies();

/**
 * @brief Scans for the agressive enemies in the enemies vector
 * 
 * @returns Number of agressive enemies
 */
uint scan_for_aggr_enemies();

#endif /* ENEMY */
