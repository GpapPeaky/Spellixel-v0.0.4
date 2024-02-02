#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#ifndef SPRITES
#define SPRITES

/**
 * @brief Item Struct
*/
typedef struct item{
    std::string name;
    bool collected;
    SDL_Texture* item_texture;
    SDL_Surface* item_png;
    SDL_FRect item_pos;
}Item;

/**
 * @brief Velocity Struct
*/
typedef struct Velocity{
    float velocity_x;
    float velocity_y;
}Velocity;

/**
 * @brief Bullet struct for each entity
*/
typedef struct bullet{
    SDL_Texture* bullet_texture;
    SDL_Surface* bullet_png;
    SDL_FRect bullet_pos;
    double bullet_angle;
    Velocity bullet_acc;
    int dmg;
}Bullet;

/**
 * @brief Sprite Struct
 * 
 * @note Some fields can remain untouched, (player :: angle) and it wont change
*/
typedef struct sprite{
    SDL_FRect pos;
    Velocity acc;
    SDL_Surface* sprite_bmp;
    SDL_Texture* sprite_texture;
    int HP;
    double angle; 
    struct bullet Bullets;
    std::vector<struct bullet> sprite_bullets;
}Sprite;

extern Sprite pl;  /* Player */
extern Sprite bcg; /* Background */
extern Sprite fence;

#endif
