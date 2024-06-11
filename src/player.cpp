#include "player.h"

std::unordered_set<SDL_Keycode> activeKeys;
SDL_FRect shadow_rect;

void handle_input(SDL_Event& e){
    if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
        if(e.type == SDL_KEYDOWN){
            activeKeys.insert(e.key.keysym.sym); /* While it is is pressed */
        }else if(e.type == SDL_KEYUP){  
            activeKeys.erase(e.key.keysym.sym); /* While it is not pressed*/
        }

        /* Exit game */

        if(SDLK_e == e.key.keysym.sym){
                SDL_DestroyTexture(pltexture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(win);
                SDL_Quit();

                std::printf("Window Closed Successfully\n");
                exit(EXIT_SUCCESS);
        }

        if(SDLK_q == e.key.keysym.sym){
            std::printf("Debug input key\n");
        }
    }
}

void update_player(float deltaTime){

    if(activeKeys.count(SDLK_w) || activeKeys.count(SDLK_a) || activeKeys.count(SDLK_s) || activeKeys.count(SDLK_d)){
        if(activeKeys.count(SDLK_w)){
            pl.acc.velocity_y -= __SPEED_UP__;
        }
        if(activeKeys.count(SDLK_a)){
            pl.acc.velocity_x -= __SPEED_UP__;
        }
        if(activeKeys.count(SDLK_s)){
            pl.acc.velocity_y += __SPEED_UP__;
        }
        if(activeKeys.count(SDLK_d)){
            pl.acc.velocity_x += __SPEED_UP__;
        }

        pl.pos.x += pl.acc.velocity_x * deltaTime * 0.8; /* dx = du*dt */
        pl.pos.y += pl.acc.velocity_y * deltaTime * 0.8;
    }

    pl.acc.velocity_x *= __SLOW_DOWN__;
    pl.acc.velocity_y *= __SLOW_DOWN__; /* For smoother decceleration */

    if (fabs(pl.acc.velocity_x) < 0.01) pl.acc.velocity_x = 0;
    if (fabs(pl.acc.velocity_y) < 0.01) pl.acc.velocity_y = 0;

    /* Screen Collisions (Ping Pong Type Of Shit) */

    if(pl.pos.x < 0){
        pl.pos.x = 0;
        pl.acc.velocity_x = -pl.acc.velocity_x; 
    }
    if(pl.pos.x + pl.pos.w > screen_x){
        pl.pos.x = screen_x - pl.pos.w;
        pl.acc.velocity_x = -pl.acc.velocity_x; 
    }
    if(pl.pos.y < 0){
        pl.pos.y = 0;
        pl.acc.velocity_y = -pl.acc.velocity_y; 
    }
    if(pl.pos.y + pl.pos.h > screen_y){
        pl.pos.y = screen_y - pl.pos.h;
        pl.acc.velocity_y = -pl.acc.velocity_y; 
    }

    update_bullets(deltaTime);
}

Render_t render_player_and_enemies(void){

    const auto& first_enemy = enemies.empty() ? nullptr : &enemies.front();

    /* Empty Enemies Array */
    if(!first_enemy){
        draw_sprite_shadow(pl, 0);
        SDL_RenderCopyF(renderer, pltexture, NULL, &pl.pos); /* Player */
        render_item_on_player();
        return;
    }

    for(const auto& enemy : enemies){
        if(pl.pos.y < enemy.sprite.pos.y){
        draw_sprite_shadow(pl, 0);
        SDL_RenderCopyF(renderer, pltexture, NULL, &pl.pos); /* Player */
        render_item_on_player();
        render_enemies();
        return;
        }else{
            render_enemies();
            draw_sprite_shadow(pl, 0);
            SDL_RenderCopyF(renderer, pltexture, NULL, &pl.pos); /* Player */
            render_item_on_player();
            return;
        }
    }
}
