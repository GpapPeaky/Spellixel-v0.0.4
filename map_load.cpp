#include "map_load.h"

/* TODO: MAKE THE ROOMS RANDOMLY GENERATE WITH EACH DOOR PASSED */

/* Always one up 1-TEXTURES */

std::vector<struct tile> meshes;

int current_map_idx = 1;

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

void render_background_tiles(std::vector<std::vector<int>>& map){
    SDL_Texture* textures[TEXTURES];

    for(int i = 1 ; i < TEXTURES ; i++){
        std::string texture_path = "src/sprites/tiles/tile (" + std::to_string(i) + ").png"; /* Take the path */
        SDL_Surface* surface = IMG_Load(texture_path.c_str());
        textures[i] = SDL_CreateTextureFromSurface(renderer, surface); 
        SDL_FreeSurface(surface);
    }

    for(int i = 0 ; i < Y_S ; ++i){
        for(int j = 0 ; j < X_S ; j++){
            int tile_id = map[i][j];
            if(tile_id >= 1 && tile_id < TEXTURES){
                SDL_Rect pos = { j * MESH_SIZE, i * MESH_SIZE, MESH_SIZE, MESH_SIZE };
                SDL_RenderCopy(renderer, textures[tile_id], NULL, &pos);
            }
        }
    }

    for (int i = 1; i < TEXTURES; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

void render_mesh_tiles(std::vector<std::vector<int>>& map ){
    Tiles textures[TEXTURES];
    meshes.clear();

    for(int i = 0 ; i < TEXTURES ; i++){
        std::string texture_path = "src/sprites/tiles/tile (" + std::to_string(i) + ").png"; /* Take the path */
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

                tile.pos = { j * MESH_SIZE, i * MESH_SIZE, MESH_SIZE, MESH_SIZE };
                meshes.push_back(tile);
                SDL_RenderCopy(renderer, textures[tile_id].sprite_texture, NULL, &tile.pos);
            }
        }
    }

    for (int i = 0; i < TEXTURES; ++i) {
        SDL_DestroyTexture(textures[i].sprite_texture);
    }
}
