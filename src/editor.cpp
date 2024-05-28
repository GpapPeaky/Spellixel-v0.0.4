#include "editor.h"

/* IDEA: LOAD MDF FILES FOR EDITING */
/* MUST: CONFIGURE MAKE FILE, AND SOURCE CODE */
/* MUST: CROSS DEVICE EDITOR / REMOVE REGEX */

SDL_Window* window;
SDL_Renderer* renderer;
std::vector<std::vector<int>> map_data;
int current_tile = 0;
std::unordered_map<int, SDL_Texture*> tile_textures;

Init_t init(void){

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Map Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, EDITOR_SCRN_W, EDITOR_SCRN_H, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    std::string tile_dir = "src/sprites/tiles";
    DIR* dir;
    struct dirent* ent;
    if((dir = opendir(tile_dir.c_str())) != NULL){
        while((ent = readdir(dir)) != NULL){
            if(ent->d_type == DT_REG){
                std::string tile_fname = ent->d_name;
                
                std::regex num_regex("\\((\\d+)\\)");
                std::smatch match;

                if(std::regex_search(tile_fname, match, num_regex)){
                    int tile_id = std::stoi(match[1].str());

                    std::string tile_img_path = tile_dir + "/" + tile_fname;
                    SDL_Surface* tile_surface = IMG_Load(tile_img_path.c_str());

                    if(tile_surface == NULL){
                        std::cerr << "Unable to load image: " << tile_img_path << "! IMG_Load Error: " << IMG_GetError() << std::endl;
                        exit(1);
                    }

                    SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_surface);
                    SDL_FreeSurface(tile_surface);

                    if(tile_texture == NULL){
                        std::cerr << "Unable to create texture from image: " << tile_img_path << "! SDL_Error: " << SDL_GetError() << std::endl;
                        exit(1);
                    }

                    tile_textures[tile_id] = tile_texture;
                }
            }
        }
        closedir(dir);
    }else{
        std::cerr << "Could not open directory: " << tile_dir << std::endl;
        exit(1);
    }
}

Update_t tile_on_click(SDL_Event& event){
    if(event.type == SDL_QUIT){
        std::ofstream file("_FILE.mdf");
        file << map_data[0].size() << " " << map_data.size() << std::endl;

        for(const auto& row : map_data){
            for(int value : row){
                file << value << " ";
            }
            file << std::endl;
        }

        file.close();

        exit(0);
    }else if(event.type == SDL_MOUSEBUTTONDOWN){
        int mouse_x = event.button.x / LOCAL_TILE_SIZE;
        int mouse_y = event.button.y / LOCAL_TILE_SIZE;

        if (mouse_y >= 0 && mouse_y < map_data.size() && mouse_x >= 0 && mouse_x < map_data[0].size()) {
            map_data[mouse_y][mouse_x] = current_tile;
        }
    }else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_ESCAPE: {
                std::ofstream file("map.mdf"); /* Save the map whenever I exit */
                file << map_data[0].size() << " " << map_data.size() << std::endl;

                for(const auto& row : map_data){
                    for (int value : row){
                        file << value << " ";
                    }
                    file << std::endl;
                }

                file.close();

                exit(0);
            }
            case SDLK_e: {
                current_tile = (current_tile + 1);
                if(current_tile == TEXTURES){
                    current_tile == 1;
                }
                break;
            }
            case SDLK_q: {
                current_tile = (current_tile - 1);
                if(current_tile < 0){
                    current_tile == TEXTURES;
                }
                break;
            }
        }
    }
}

Render_t render(void) {
    SDL_RenderClear(renderer);

    for(int i = 0; i < map_data.size(); ++i){
        for(int j = 0; j < map_data[i].size(); ++j){
            SDL_Rect tile_rect = { j * LOCAL_TILE_SIZE, i * LOCAL_TILE_SIZE, LOCAL_TILE_SIZE, LOCAL_TILE_SIZE };

            /* Render the texture for the current tile type */
            SDL_RenderCopy(renderer, tile_textures[map_data[i][j]], NULL, &tile_rect);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
            SDL_RenderDrawRect(renderer, &tile_rect);
        }
    }

    int current_tile_area_x = 1080; 
    int current_tile_area_y = EDITOR_SCRN_H/2; 
    int current_tile_area_size = LOCAL_TILE_SIZE * 2;

    SDL_Rect current_tileAreaRect = {current_tile_area_x, current_tile_area_y, current_tile_area_size, current_tile_area_size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &current_tileAreaRect);

    int current_tile_texture_x = ( current_tile_area_x + LOCAL_TILE_SIZE / 2 ) - 105;
    int current_tile_texture_y = EDITOR_SCRN_H / 2 - current_tile_area_size / 2 - 15;

    SDL_Rect current_tile_texture_rect = {current_tile_texture_x, current_tile_texture_y, 5 * LOCAL_TILE_SIZE, 5 * LOCAL_TILE_SIZE};
    SDL_RenderCopy(renderer, tile_textures[current_tile], NULL, &current_tile_texture_rect);


    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv){
    init();

    /* INITIALISE MAP WITH 0 30x16 */
    int map_w = 960 / LOCAL_TILE_SIZE;
    int map_h = EDITOR_SCRN_H / LOCAL_TILE_SIZE;
    map_data.resize(map_h, std::vector<int>(map_w, 0));

    SDL_Event e;

    while(true){
        while (SDL_PollEvent(&e) != 0){
            tile_on_click(e);
        }

        render();
    }

    return 0;
}
