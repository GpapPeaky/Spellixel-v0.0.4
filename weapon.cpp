#include "weapon.h"

Uint32 last_shot_time = 0;

void handle_shooting(SDL_Event& e){

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if((e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION) && e.button.button == SDL_BUTTON_LEFT){

        Uint32 current_time = SDL_GetTicks();

        if(current_time - last_shot_time >= SHOOTING_RATE){

            load_and_play_wav_sound("firing"); /* Fire sound */

            pl.Bullets.bullet_pos.x = pl.pos.x + pl.pos.w / 2 - 15;
            pl.Bullets.bullet_pos.y = pl.pos.y + pl.pos.h / 2;

            pl.Bullets.bullet_angle = std::atan2(mouseY - pl.Bullets.bullet_pos.y, mouseX - pl.Bullets.bullet_pos.x);
            pl.Bullets.bullet_acc.velocity_x = __BULLET_SPEED__ * std::cos(pl.Bullets.bullet_angle);
            pl.Bullets.bullet_acc.velocity_y = __BULLET_SPEED__ * std::sin(pl.Bullets.bullet_angle);

            pl.Bullets.bullet_png = IMG_Load("src/sprites/bullets/bullet.png"); /* PLAYER BULLET TEXTURE */
            pl.Bullets.bullet_texture = SDL_CreateTextureFromSurface(renderer, pl.Bullets.bullet_png);

            pl.Bullets.bullet_pos.w = pl.Bullets.bullet_png->w * 4;
            pl.Bullets.bullet_pos.h = pl.Bullets.bullet_png->h * 4;
            
            pl.sprite_bullets.push_back(pl.Bullets);

            last_shot_time = current_time;
        }
    }
}

void update_bullets(float deltaTime){

    for(auto& bullet : pl.sprite_bullets){
        bullet.bullet_pos.x += bullet.bullet_acc.velocity_x * deltaTime;
        bullet.bullet_pos.y += bullet.bullet_acc.velocity_y * deltaTime;
    }

    auto newEnd = std::remove_if(pl.sprite_bullets.begin(), pl.sprite_bullets.end(), [&](const Bullet& bullet){
        bool isOutOfBounds = (bullet.bullet_pos.x > screen_x || bullet.bullet_pos.x < 0 ||
                            bullet.bullet_pos.y > screen_y || bullet.bullet_pos.y < 0);

        if(isOutOfBounds){
            SDL_FreeSurface(bullet.bullet_png);
            SDL_DestroyTexture(bullet.bullet_texture); // Destroy the texture
        }

        return isOutOfBounds;
    });

    pl.sprite_bullets.erase(newEnd, pl.sprite_bullets.end());
}

void render_player_bullets(void){
        for (const auto& bullet :pl.sprite_bullets){
            SDL_RenderCopyExF(renderer, bullet.bullet_texture, NULL, &bullet.bullet_pos, (bullet.bullet_angle) * (180.0 / M_PI) , NULL, SDL_FLIP_NONE);
        }

        /* bullet.angle -> randomise extra bluh bluh generatesa boomerang like effect */
}
