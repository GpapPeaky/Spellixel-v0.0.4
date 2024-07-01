#include "item.h"

std::vector<Item> items;
Item current_item;
Item podium;

/* IDEA the item sprites will be saved onto a vector and they will be render over the character where each element is a different item and layer */
/* IDEA the items can be displaye by pressing a key */
/* IDEA another vector can have the item upgrades (dmg, rof ect) */
 
Init_t init_podium(void){
    podium.name = "podium";

    podium.item_png = IMG_Load("src/sprites/items/podium.png");
    if (podium.item_png == nullptr) {
        printf("Error loading image: %s\n", IMG_GetError());
    }

    podium.item_texture = SDL_CreateTextureFromSurface(renderer, podium.item_png);

    SDL_FreeSurface(podium.item_png);

    podium.item_pos.w = podium.item_png->w * 4;
    podium.item_pos.h = podium.item_png->h * 4;
}

Update_t spawn_item(int x, int y, std::string item_name){

    Item item_to_spawn;
    std::string filename = ("src/sprites/items/" + item_name +  ".png");
    item_to_spawn.name = item_name;

    item_to_spawn.item_png = IMG_Load(filename.c_str());
    if (item_to_spawn.item_png == nullptr) {
        printf("Error loading image: %s\n", IMG_GetError());
    }

    item_to_spawn.item_texture = SDL_CreateTextureFromSurface(renderer, item_to_spawn.item_png);

    SDL_FreeSurface(item_to_spawn.item_png);

    item_to_spawn.item_pos.w = (item_to_spawn.item_png->w * 4 * render_factor);
    item_to_spawn.item_pos.h = (item_to_spawn.item_png->h * 4 * render_factor);
    item_to_spawn.item_pos.x = x;
    item_to_spawn.item_pos.y = y;

    podium.item_pos.x = x;
    podium.item_pos.y = y;

    current_item = item_to_spawn;
    current_item.collected = false;

    // std::printf("%s\n", current_item.name.c_str());

    SDL_RenderCopyF(renderer, item_to_spawn.item_texture, NULL, &item_to_spawn.item_pos);
}

Render_t render_item(void){
    if(!current_item.collected){
        SDL_RenderCopyF(renderer, podium.item_texture, NULL, &podium.item_pos);
        SDL_RenderCopyF(renderer, current_item.item_texture, NULL, &current_item.item_pos);
        /* items are shown successfully, and with the correct size */
    }else{
        SDL_RenderCopyF(renderer, podium.item_texture, NULL, &podium.item_pos);
    }
}

void item_player_collision(void){
    if(SDL_HasIntersectionF(&pl.pos, &current_item.item_pos) && !current_item.collected){
        items.push_back(current_item);
        // std::printf("You Have Gained The %s\n",current_item.name.c_str());
        // std::printf("%d ITEMS", inventory.size());
        current_item.collected = true;
    }
}

void render_item_on_player(void){
    for(auto& item : items){
        SDL_RenderCopyF(renderer, item.item_texture, NULL, &pl.pos);
    }
}
