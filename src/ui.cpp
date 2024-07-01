#include "ui.h"

SDL_Rect ui_rect;
SDL_Texture *ui_texture;

SDL_FRect HP_rect;
SDL_FRect att_rect;
SDL_FRect room_rect;
SDL_FRect enemies_rect;

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

    return;
}

Render_t render_ui_background(void){
    SDL_RenderCopy(renderer, ui_texture, NULL, &ui_rect);
    /* The texture will be changed in the future */
    return;
}

Render_t render_player_stats(void){

    HP_rect = { 15, 1064, 55 * render_factor, 55 * render_factor };
    att_rect = { 85, 1064, 55 * render_factor, 55 * render_factor }; /* 15 pixel space for each stat */
    room_rect = { 155, 1064, 55 * render_factor, 55 * render_factor };
    enemies_rect = { 240, 1064, 55 * render_factor, 55 * render_factor };

    render_text(("HP: " + std::to_string(pl.HP)).c_str(), &HP_rect);
    render_text(("ATT: " + std::to_string(pl.Bullets.dmg)).c_str(), &att_rect);
    render_text(("ROOM: " + std::to_string(total_rooms_count)).c_str(), &room_rect);
    render_text(("ENEMIES: " + std::to_string(scan_for_aggr_enemies())).c_str(), &enemies_rect);

    return;
    /* More stats will be added in the future */
}

Render_t render_UI(void){
    render_ui_background();
    render_player_stats();
}
