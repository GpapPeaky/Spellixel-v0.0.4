#include "ui.h"

SDL_Rect ui_rect;
SDL_Texture * ui_texture;

SDL_FRect HP_rect;
SDL_FRect att_rect;
SDL_FRect room_rect;

Init_t init_ui(void){

    SDL_Surface * ui = IMG_Load("src/sprites/win/ui.png");
    if(ui == NULL){
        std::printf("%s\n",SDL_GetError());
    }

    ui_texture = SDL_CreateTextureFromSurface(renderer, ui);
    if(ui_texture == NULL){
        std::printf("%s\n",SDL_GetError());
    }

    ui_rect.h = 56;
    ui_rect.w = SCREEN_WIDTH;
    ui_rect.x = 0;
    ui_rect.y = 1024;
}

Render_t render_ui_background(void){
    SDL_RenderCopy(renderer, ui_texture, NULL, &ui_rect);
    /* The texture will be changed in the future */
}

Render_t render_player_stats(void){

    HP_rect = { 15, 1064, 55, 55 };
    att_rect = { 85, 1064, 55, 55 }; /* 15 pixel space for each stat */
    room_rect = { 155, 1064, 55, 55 };

    render_text(("HP: " + std::to_string(pl.HP)).c_str(), &HP_rect);
    render_text(("ATT: " + std::to_string(pl.Bullets.dmg)).c_str(), &att_rect);
    render_text(("ROOM: " + std::to_string(current_map_idx)).c_str(), &room_rect);

    /* More stats will be added in the future */
}

Render_t render_UI(void){
    render_ui_background();
    render_player_stats();
}
