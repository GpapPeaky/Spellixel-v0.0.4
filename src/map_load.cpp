#include "map_load.h"

/* Always one up 1-TEXTURES */

std::vector<struct tile> meshes;

int current_map_idx = 1;

int total_rooms_count = 0;

std::vector<std::vector<int>> load_map(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int width, height;
    file >> width >> height;

    std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));

    for(int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            file >> map[y][x];
        }
    }

    file.close();
    return map;
}

Render_t render_background_tiles(std::vector<std::vector<int>>& map){
    SDL_Texture* textures[TEXTURES];

    for(int i = 1 ; i < TEXTURES ; i++){
        std::string texture_path = "assets/sprites/tiles/tile (" + std::to_string(i) + ").png"; /* Take the path */
        SDL_Surface* surface = IMG_Load(texture_path.c_str());
        textures[i] = SDL_CreateTextureFromSurface(renderer, surface); 
        SDL_FreeSurface(surface);
    }

    for(int i = 0 ; i < Y_S ; ++i){
        for(int j = 0 ; j < X_S ; j++){
            int tile_id = map[i][j];
            if(tile_id >= 1 && tile_id < TEXTURES){
                SDL_FRect pos = { j * MESH_SIZE * render_factor, i * MESH_SIZE * render_factor, MESH_SIZE * render_factor, MESH_SIZE * render_factor };
                SDL_RenderCopyF(renderer, textures[tile_id], NULL, &pos);
            }
        }
    }

    for (int i = 1; i < TEXTURES; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

Render_t render_mesh_tiles(std::vector<std::vector<int>>& map){
    Tiles textures[TEXTURES];
    meshes.clear();

    for(int i = 0 ; i < TEXTURES ; i++){
        std::string texture_path = "assets/sprites/tiles/tile (" + std::to_string(i) + ").png"; /* Take the path */
        textures[i].sprite_bmp = IMG_Load(texture_path.c_str());
        textures[i].sprite_texture = SDL_CreateTextureFromSurface(renderer, textures[i].sprite_bmp); 
        SDL_FreeSurface(textures[i].sprite_bmp);
        // meshes.push_back(textures[i]); // DECREASES PERFORMANCE FOR SOME REASON...
    }

    for(int i = 0 ; i < Y_S ; ++i){
        for(int j = 0 ; j < X_S ; j++){
            int tile_id = map[i][j];
            if(tile_id >= 1 && tile_id < TEXTURES){
                Tiles tile;

                tile.pos = { (int)(j * MESH_SIZE * render_factor), (int)(i * MESH_SIZE * render_factor), (int)(MESH_SIZE * render_factor), (int)(MESH_SIZE * render_factor) };
                meshes.push_back(tile);
                SDL_RenderCopy(renderer, textures[tile_id].sprite_texture, NULL, &tile.pos);
            }
        }
    }

    for (int i = 0; i < TEXTURES; ++i) {
        SDL_DestroyTexture(textures[i].sprite_texture);
    }
}

Update_t update_loaded_map(void){

    srand(time(NULL));

    static int prev_pl_x = pl.pos.x;
    static int prev_pl_y = pl.pos.y;

    int deltaX = pl.pos.x - prev_pl_x;
    int deltaY = pl.pos.y - prev_pl_y;

    if(pl.pos.x + pl.pos.w >= screen_x && (enemies.empty() == true || scan_for_aggr_enemies() == 0)){
        enemies.clear(); /* Clear the enemies vector */
        current_map_idx = 1 + (rand() % ROOMS);

        while(current_map_idx == 1){ /* IDX 1 IS THE STARTING POSITION */
            current_map_idx = 1 + (rand() % ROOMS);
        }

        std::printf("Currenty at map <%d>\n",current_map_idx);
        total_rooms_count++;

        pl.pos.x = 0 - pl.pos.w; /* Resetting position as we move along to a new map */
    }

    prev_pl_x = pl.pos.x;
    prev_pl_y = pl.pos.y;

    return;
}
