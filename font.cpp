#include "font.h"

SDL_Color text_colour;
SDL_Color text_colour_bg;
SDL_Surface * text = NULL;
SDL_Texture * txt = NULL;
SDL_Texture * b_txt = NULL;
SDL_Texture * c_txt = NULL;
TTF_Font* font = NULL;

Init_t init_ui(void){

    font = TTF_OpenFont("src/font/FFFFORWA.TTF", 18);
    if(!font){
        std:printf("FONT: %s\n ", SDL_GetError());
    }
    text_colour = { 255, 255, 255}; /* White font */
    text_colour_bg = { 0, 0, 0}; /* White font */

    return;
}

Render_t render_ui(const char* msg){

    SDL_Surface * text = TTF_RenderUTF8_Solid(font, msg, text_colour);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    SDL_Texture * txt = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    text = TTF_RenderUTF8_Solid(font, msg, text_colour_bg);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    SDL_Texture * b_txt = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_FRect rect;
    rect.x = pl.pos.x - text->w / 2;
    rect.y = pl.pos.y - 20;
    rect.h = text->h;
    rect.w = text->w;

    SDL_FRect b_rect;
    b_rect.x = rect.x + 2;
    b_rect.y = pl.pos.y - 20 + 2;
    b_rect.h = text->h + 2;
    b_rect.w = text->w + 2;

    SDL_FRect c_rect;
    c_rect.x = rect.x - 2;
    c_rect.y = pl.pos.y - 20 - 2;
    c_rect.h = text->h;
    c_rect.w = text->w;

    SDL_RenderCopyF(renderer, b_txt, NULL, &c_rect);
    SDL_RenderCopyF(renderer, b_txt, NULL, &b_rect);
    SDL_RenderCopyF(renderer, txt, NULL, &rect);

    SDL_DestroyTexture(txt);
}
