#include "fx.h"

SDL_FRect shadow;

Render_t draw_sprite_shadow(Sprite entity, int w_fix){
    shadow = { entity.pos.x + (w_fix / 2), entity.pos.y + entity.pos.h - 2, entity.pos.w - w_fix - 2, entity.pos.h / 10 };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SHADOW_OPACITY); /* Black colour with low opacity */
    SDL_RenderFillRectF(renderer, &shadow);
    
    shadow = { entity.pos.x + (w_fix / 2) + 4, entity.pos.y + entity.pos.h + 4 , entity.pos.w - w_fix - 10, entity.pos.h / 25 };

    SDL_RenderFillRectF(renderer, &shadow);
}

Render_t draw_bullet_shadow(Bullet bul){
    shadow = { bul.bullet_pos.x - 2, bul.bullet_pos.y + bul.bullet_pos.h - 2, bul.bullet_pos.w, bul.bullet_pos.h / 10 };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SHADOW_OPACITY); /* Black colour with low opacity */
    SDL_RenderFillRectF(renderer, &shadow);
}
