#include "enemy.h"

std::vector<Enemy> enemies;

SDL_Color e_text_colour;
SDL_Color e_text_colour_bg;
SDL_Surface* e_text;
SDL_Texture* e_txt;
SDL_Texture* e_b_txt;
TTF_Font* e_font;
SDL_FRect e_rect;
SDL_FRect e_b_rect;
SDL_FRect e_c_rect;
Uint32 dmg_strt_tm = 0;

/* FIXED: THE EGG GENERATED BY THE CHICKEN FOR SOME TIME IN TESTING WAS NOT MOVING */

Init_t init_enemy_font(void){
    e_font = TTF_OpenFont("src/font/FFFFORWA.TTF", FONT_SIZE); /* Relative to the .exe */
    if(!e_font){
        std:printf("FONT: %s\n ", SDL_GetError());
    }
    e_text_colour = { 255, 255, 255}; /* White font */
    e_text_colour_bg = { 0, 0, 0}; /* White font */
}

Render_t render_damaged_enemies(int dmg_taken, SDL_FRect* position){

    srand(time(NULL));
    
    e_text = TTF_RenderUTF8_Solid(e_font, std::to_string(-dmg_taken).c_str(), e_text_colour);
    if(!e_text){
        std::printf("ERROR: %s\n ", SDL_GetError());
    }
    e_txt = SDL_CreateTextureFromSurface(renderer, e_text);

    // SDL_FreeSurface(e_text);

    e_text = TTF_RenderUTF8_Solid(e_font, std::to_string(-dmg_taken).c_str(), e_text_colour_bg);
    if(!e_text){
        std::printf("ERROR: %s\n ", SDL_GetError());
    }
    e_b_txt = SDL_CreateTextureFromSurface(renderer, e_text);

    SDL_FreeSurface(e_text);

    e_rect.x = position->x;
    e_rect.y = position->y - 20;
    e_rect.h = e_text->h;
    e_rect.w = e_text->w;

    e_b_rect.x = e_rect.x + 2;
    e_b_rect.y = e_rect.y + 2;
    e_b_rect.h = e_text->h + 2;
    e_b_rect.w = e_text->w + 2;

    e_c_rect.x = e_rect.x - 2;
    e_c_rect.y = e_rect.y - 2;
    e_c_rect.h = e_text->h;
    e_c_rect.w = e_text->w;


    SDL_RenderCopyF(renderer, e_b_txt, NULL, &e_c_rect);
    SDL_RenderCopyF(renderer, e_b_txt, NULL, &e_b_rect);
    SDL_RenderCopyF(renderer, e_txt, NULL, &e_rect);

    SDL_DestroyTexture(e_b_txt);
    SDL_DestroyTexture(e_txt);
}

void shoot(float reload_speed){
    static auto last_shot_time = std::chrono::high_resolution_clock::now();

    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_shot_time).count();

    if(elapsed_time >= reload_speed){
        for (auto &agressor : enemies) {
            if (agressor.type == agressive || agressor.type == healing){
                float playerX = pl.pos.x;
                float playerY = pl.pos.y;

                /* ADD TIMER */
                
                /* Hilbert is shooting the eggs, and they are constantly loaded inside him... FIXME */
                agressor.sprite.Bullets.bullet_pos.x = agressor.sprite.pos.x + agressor.sprite.pos.w / 2;
                agressor.sprite.Bullets.bullet_pos.y = agressor.sprite.pos.y + agressor.sprite.pos.h / 2;

                agressor.sprite.Bullets.bullet_angle = std::atan2(playerY - agressor.sprite.pos.y, playerX - agressor.sprite.pos.x);

                /* FIX THE ANGLE */
                /* IT GOES ON A WRONG ANGLE */

                agressor.sprite.sprite_bullets.push_back(agressor.sprite.Bullets);
            }

            // std::printf("bullet vector size <%d> \n ", agressor.sprite.sprite_bullets.size());
            // std::printf("bullet velocity <%.2f,%.2f> \n ", agressor.sprite.Bullets.bullet_acc.velocity_x,agressor.sprite.Bullets.bullet_acc.velocity_y);

            /* FIXED: The egg is rendered directly on the player and it is not deleted afterwards */
        }
        last_shot_time = current_time;
    }
}

bool bullet_hits_mesh(const Bullet &bullet){
    SDL_FRect bullet_rectangle = {bullet.bullet_pos.x, bullet.bullet_pos.y, bullet.bullet_pos.w, bullet.bullet_pos.h};

    for (const auto &mesh : meshes){
        SDL_FRect mesh_rectangle = {(float) mesh.pos.x, (float) mesh.pos.y, (float)mesh.pos.w, (float) mesh.pos.h};

        if (SDL_HasIntersectionF(&bullet_rectangle, &mesh_rectangle)){
            return true;
        }
    }

    return false;
}

bool bullet_hits_player(const Bullet &bullet){
    if(SDL_HasIntersectionF(&bullet.bullet_pos, &pl.pos)){
        pl.HP -= bullet.dmg;
    }
    return SDL_HasIntersectionF(&bullet.bullet_pos, &pl.pos);
}

bool bullet_offscreen(const Bullet &bullet){
    return (bullet.bullet_pos.x > screen_x || bullet.bullet_pos.x < 0 ||
            bullet.bullet_pos.y > screen_y || bullet.bullet_pos.y < 0);
}

void update_enemy_bullets(float deltaTime){
    for (auto &enemy : enemies){
        for (auto &bullet : enemy.sprite.sprite_bullets){
            bullet.bullet_pos.x += std::cos(bullet.bullet_angle) * bullet.bullet_acc.velocity_x * (deltaTime);
            bullet.bullet_pos.y += std::sin(bullet.bullet_angle) * bullet.bullet_acc.velocity_y * (deltaTime);
        }

        enemy.sprite.sprite_bullets.erase(std::remove_if(enemy.sprite.sprite_bullets.begin(), enemy.sprite.sprite_bullets.end(),
                                                        [&](const Bullet &bullet)
                                                        {
                                                            return bullet_hits_player(bullet) || bullet_offscreen(bullet) || bullet_hits_mesh(bullet);
                                                        }), enemy.sprite.sprite_bullets.end());
    }
}

/* FIXME: WHENEVER AN ENEMY DIES IT IS REMOVED FROM THE ENEMY VECTOR, THAT MEANS THAT THE FUNCTION DOES NOT HAVE ACCESS TO THE REMAINING BULLETS LAODED */

Render_t render_enemy_bullets(void){
    for (auto &enemy : enemies){
        for (auto &enemy_bullet : enemy.sprite.sprite_bullets){
            draw_bullet_shadow(enemy_bullet);
            SDL_RenderCopyExF(renderer, enemy_bullet.bullet_texture, NULL, &enemy_bullet.bullet_pos, enemy_bullet.bullet_angle * (180.0 / M_PI), NULL, SDL_FLIP_NONE);
        }
    }
}

Update_t update_enemy_movement(void){

    srand(time(NULL));

    for(auto &enemy : enemies){

        int rand_x_offset = rand() % 10 - 4; /* wandering around offset with each update */
        int rand_y_offset = rand() % 10 - 4;

        int new_x = enemy.sprite.pos.x + rand_x_offset * enemy.speed;
        int new_y = enemy.sprite.pos.y + rand_y_offset * enemy.speed;

        if(new_x < enemy.wander.min.x){
            new_x = enemy.wander.min.x;
        }
        else if(new_x > enemy.wander.max.x){
            new_x = enemy.wander.max.x;
        }

        if(new_y < enemy.wander.min.y){
            new_y = enemy.wander.min.y;
        }
        else if(new_y > enemy.wander.max.y){
            new_y = enemy.wander.max.y;
        }

        enemy.sprite.pos.x = new_x;
        enemy.sprite.pos.y = new_y;
    }
}

Update_t update_enemy(void){
    for(auto it = enemies.begin(); it != enemies.end();){
        auto& enemy = *it;

        for(auto bullet_it = pl.sprite_bullets.begin(); bullet_it != pl.sprite_bullets.end();){
            auto& player_bullet = *bullet_it;

            if(SDL_HasIntersectionF(&player_bullet.bullet_pos, &enemy.sprite.pos) && enemy.type == agressive){
                enemy.sprite.HP -= player_bullet.dmg;
                enemy.damage_taken = player_bullet.dmg;
                enemy.damaged = true;

                dmg_strt_tm = SDL_GetTicks();

                bullet_it = pl.sprite_bullets.erase(bullet_it);
            }else{
                ++bullet_it;\
            }
        }

        if(enemy.sprite.HP <= 0){
            SDL_DestroyTexture(enemy.sprite.sprite_texture);
            it = enemies.erase(it);
        }else{
            ++it;
        }
    }
}

Render_t render_enemies(void){
    
    Uint32 currentTime = SDL_GetTicks(); // Get the current time
    
    for (auto &enemy : enemies) {
        draw_sprite_shadow(enemy.sprite, 6);
        SDL_RenderCopyF(renderer, enemy.sprite.sprite_texture, NULL, &enemy.sprite.pos);

        if (enemy.damaged) {
            if (currentTime - dmg_strt_tm <= DAMAGE_DISPLAY_DURATION) {
                render_damaged_enemies(enemy.damage_taken, &enemy.sprite.pos);
            }else{
                enemy.damaged = false;
            }
        }
    }
}


Enemy chicken(int x, int y){
    Enemy chicken;
    chicken.type = healing;
    chicken.name =  "chicken";

    chicken.sprite.HP = 10;
    chicken.sprite.Bullets.dmg = -1;

    chicken.sprite.Bullets.bullet_png = IMG_Load("src/sprites/bullets/egg.png");
    chicken.sprite.Bullets.bullet_texture = SDL_CreateTextureFromSurface(renderer, chicken.sprite.Bullets.bullet_png);

    SDL_FreeSurface(chicken.sprite.Bullets.bullet_png);

    chicken.sprite.sprite_bmp = IMG_Load("src/sprites/chicken.png");
    chicken.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, chicken.sprite.sprite_bmp);

    SDL_FreeSurface(chicken.sprite.sprite_bmp);

    chicken.sprite.Bullets.bullet_pos.h = 15;
    chicken.sprite.Bullets.bullet_pos.w = 18;

    chicken.sprite.Bullets.bullet_acc.velocity_x = 70.0f;
    chicken.sprite.Bullets.bullet_acc.velocity_y = 70.0f;

    chicken.wander.max.x = x + 50;
    chicken.wander.max.y = y + 50;
    chicken.wander.min.x = x - 20;
    chicken.wander.min.y = y - 30;

    chicken.sprite.pos.h = 40; /* 4 times the sprite size */
    chicken.sprite.pos.w = 40;
    chicken.sprite.pos.x = x;
    chicken.sprite.pos.y = y;

    chicken.speed = CHICKEN_SPEED;

    enemies.push_back(chicken);

    SDL_RenderCopyF(renderer, chicken.sprite.sprite_texture, NULL, &chicken.sprite.pos);

    return chicken;
}

Enemy sheep(int x, int y){
    Enemy sheep;
    sheep.type = passive;
    sheep.name = "sheep";

    sheep.sprite.HP = 30;

    sheep.sprite.sprite_bmp = IMG_Load("src/sprites/sheep.png");
    sheep.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, sheep.sprite.sprite_bmp);

    SDL_FreeSurface(sheep.sprite.sprite_bmp);

    sheep.wander.max.x = x + 50;
    sheep.wander.max.y = y + 50;
    sheep.wander.min.x = x - 20;
    sheep.wander.min.y = y - 30;

    sheep.sprite.pos.h = 60; /* 4 times the sprite size */
    sheep.sprite.pos.w = 68;
    sheep.sprite.pos.x = x;
    sheep.sprite.pos.y = y;

    sheep.speed = SHEEP_SPEED;

    enemies.push_back(sheep);

    SDL_RenderCopyF(renderer, sheep.sprite.sprite_texture, NULL, &sheep.sprite.pos);

    return sheep;
}

Enemy john(int x, int y){
    Enemy john;
    john.type = passive;
    john.name = "john the knight";

    john.sprite.sprite_bmp = IMG_Load("src/sprites/john.png");
    john.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, john.sprite.sprite_bmp);
    SDL_FreeSurface(john.sprite.sprite_bmp);

    /* John will not wander.. */
    /* John shall not die */
    /* Long live John */
    /* John is  dead */
    /* John is John */
    /* John... */

    john.wander.max.x = x;
    john.wander.max.y = y;
    john.wander.min.x = x;
    john.wander.min.y = y;

    john.sprite.pos.h = 60; /* 4 times the sprite size */
    john.sprite.pos.w = 60;
    john.sprite.pos.x = x;
    john.sprite.pos.y = y;

    john.speed = JOHN_SPEED;

    enemies.push_back(john); /* LET ME PUSH BACK JOHN MATE */

    SDL_RenderCopyF(renderer, john.sprite.sprite_texture, NULL, &john.sprite.pos);

    return john;
}

Enemy hilbert(int x, int y){
    Enemy hilbert;
    hilbert.type = passive;
    hilbert.name = "hilbert the commander";

    hilbert.sprite.HP = 150;

    hilbert.sprite.sprite_bmp = IMG_Load("src/sprites/hilbert.png");
    hilbert.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, hilbert.sprite.sprite_bmp);
    SDL_FreeSurface(hilbert.sprite.sprite_bmp);

    /* hilbert is a senior Knight */

    hilbert.wander.max.x = x;
    hilbert.wander.max.y = y;
    hilbert.wander.min.x = x;
    hilbert.wander.min.y = y;

    hilbert.sprite.pos.h = 60; /* 4 times the sprite size */
    hilbert.sprite.pos.w = 60;
    hilbert.sprite.pos.x = x;
    hilbert.sprite.pos.y = y;

    hilbert.speed = JOHN_SPEED;

    enemies.push_back(hilbert); /* LET ME PUSH BACK hilbert MATE */

    SDL_RenderCopyF(renderer, hilbert.sprite.sprite_texture, NULL, &hilbert.sprite.pos);

    return hilbert;
}

Enemy goblin(int x, int y){
    Enemy goblin;
    goblin.type = agressive;
    goblin.name = "goblin";

    goblin.sprite.HP = 50;
    goblin.sprite.Bullets.dmg = 5;

    goblin.sprite.sprite_bmp = IMG_Load("src/sprites/goblin.png");
    goblin.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, goblin.sprite.sprite_bmp);
    SDL_FreeSurface(goblin.sprite.sprite_bmp);

    goblin.sprite.Bullets.bullet_png = IMG_Load("src/sprites/bullets/goblin_punch.png");
    goblin.sprite.Bullets.bullet_texture = SDL_CreateTextureFromSurface(renderer,goblin.sprite.Bullets.bullet_png);
    SDL_FreeSurface(goblin.sprite.Bullets.bullet_png);

    goblin.sprite.Bullets.bullet_pos.w = 27 ;
    goblin.sprite.Bullets.bullet_pos.h = 18;

    goblin.sprite.Bullets.bullet_acc.velocity_x = 50.0f;
    goblin.sprite.Bullets.bullet_acc.velocity_y = 50.0f;

    goblin.wander.max.x = x  - 15;
    goblin.wander.max.y = y - 5;
    goblin.wander.min.x = x - 50;
    goblin.wander.min.y = y - 150;

    goblin.sprite.pos.h = 60; /* 4 times the sprite size */
    goblin.sprite.pos.w = 60;
    goblin.sprite.pos.x = x;
    goblin.sprite.pos.y = y;

    goblin.speed = 0.77f;

    enemies.push_back(goblin); /* LET ME PUSH BACK goblin MATE */

    SDL_RenderCopyF(renderer, goblin.sprite.sprite_texture, NULL, &goblin.sprite.pos);

    return goblin;
}

Enemy villager(int x, int y){
    Enemy villager;
    villager.type = passive;
    villager.name = "villager";

    villager.sprite.HP = 50;
    villager.sprite.Bullets.dmg = 5;

    villager.sprite.sprite_bmp = IMG_Load("src/sprites/villager.png");
    villager.sprite.sprite_texture = SDL_CreateTextureFromSurface(renderer, villager.sprite.sprite_bmp);
    SDL_FreeSurface(villager.sprite.sprite_bmp);

    villager.wander.max.x = x;
    villager.wander.max.y = y;
    villager.wander.min.x = x;
    villager.wander.min.y = y;

    villager.sprite.pos.h = 60; /* 4 times the sprite size */
    villager.sprite.pos.w = 60;
    villager.sprite.pos.x = x;
    villager.sprite.pos.y = y;

    villager.speed = 0.77f;

    enemies.push_back(villager);

    SDL_RenderCopyF(renderer, villager.sprite.sprite_texture, NULL, &villager.sprite.pos);

    return villager;
}

void enemy_updates(float dt){
        update_enemy_bullets(dt);
        update_enemy_movement();
        update_enemy();
}

void print_enemies(){
    for(const auto& enemy : enemies){
        std::printf("NAME: %s, TYPE: %d\n",enemy.name.c_str(), enemy.type);
    }
}

uint scan_for_aggr_enemies(){
    int count = 0;

    for(auto& enemy : enemies){
        if(enemy.type == agressive){ count++; }
    }

    return count;
}