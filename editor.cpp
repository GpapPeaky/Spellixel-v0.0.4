#include "editor.h"

/* IDEA: LOAD MDF FILES FOR EDITING */
/* MUST: CONFIGURE MAKE FILE, AND SOURCE CODE */
/* MUST: CROSS DEVICE EDITOR / REMOVE REGEX */

const int LOCAL_TILE_SIZE = 32;
const int scrn_w = 1180;
const int scrn_h = 512;

SDL_Window* window;
SDL_Renderer* renderer;

std::vector<std::vector<int>> mapData;
int currentTile = 0;

std::unordered_map<int, SDL_Texture*> tileTextures;

Init_t init(void){

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Map Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scrn_w, scrn_h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Load textures for tiles from a directory
    std::string tileDirectory = "src/sprites/tiles";  // Adjust the directory based on your setup
    DIR* dir;
    struct dirent* ent;
    if((dir = opendir(tileDirectory.c_str())) != NULL){
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                std::string tileFileName = ent->d_name;
                
                // Use regular expressions to extract the tile number
                std::regex numberRegex("\\((\\d+)\\)");
                std::smatch match;

                if(std::regex_search(tileFileName, match, numberRegex)){
                    int tileNumber = std::stoi(match[1].str());

                    std::string tileImagePath = tileDirectory + "/" + tileFileName;
                    SDL_Surface* tileSurface = IMG_Load(tileImagePath.c_str());

                    if(tileSurface == NULL){
                        std::cerr << "Unable to load image: " << tileImagePath << "! IMG_Load Error: " << IMG_GetError() << std::endl;
                        exit(1);
                    }

                    SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
                    SDL_FreeSurface(tileSurface);

                    if(tileTexture == NULL){
                        std::cerr << "Unable to create texture from image: " << tileImagePath << "! SDL_Error: " << SDL_GetError() << std::endl;
                        exit(1);
                    }

                    tileTextures[tileNumber] = tileTexture;
                }
            }
        }
        closedir(dir);
    }else{
        std::cerr << "Could not open directory: " << tileDirectory << std::endl;
        exit(1);
    }
}

Update_t tile_on_click(SDL_Event& event){
    if(event.type == SDL_QUIT){
        std::ofstream file("_FILE.mdf");
        file << mapData[0].size() << " " << mapData.size() << std::endl;

        for(const auto& row : mapData){
            for(int value : row){
                file << value << " ";
            }
            file << std::endl;
        }

        file.close();

        exit(0);
    }else if(event.type == SDL_MOUSEBUTTONDOWN){
        int mouseX = event.button.x / LOCAL_TILE_SIZE;
        int mouseY = event.button.y / LOCAL_TILE_SIZE;

        if (mouseY >= 0 && mouseY < mapData.size() && mouseX >= 0 && mouseX < mapData[0].size()) {
            mapData[mouseY][mouseX] = currentTile;
        }
    }else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_ESCAPE: {
                std::ofstream file("_FILE.mdf"); /* Save the map whenever I exit */
                file << mapData[0].size() << " " << mapData.size() << std::endl;

                for(const auto& row : mapData){
                    for (int value : row){
                        file << value << " ";
                    }
                    file << std::endl;
                }

                file.close();

                exit(0);
            }
            case SDLK_e: {
                currentTile = (currentTile + 1);
                if(currentTile == TEXTURES){
                    currentTile == 1;
                }
                break;
            }
            case SDLK_q: {
                currentTile = (currentTile - 1);
                if(currentTile < 0){
                    currentTile == TEXTURES;
                }
                break;
            }
        }
    }
}

Render_t render(void) {
    SDL_RenderClear(renderer);

    for(int i = 0; i < mapData.size(); ++i){
        for(int j = 0; j < mapData[i].size(); ++j){
            SDL_Rect tileRect = { j * LOCAL_TILE_SIZE, i * LOCAL_TILE_SIZE, LOCAL_TILE_SIZE, LOCAL_TILE_SIZE };

            /* Render the texture for the current tile type */
            SDL_RenderCopy(renderer, tileTextures[mapData[i][j]], NULL, &tileRect);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
            SDL_RenderDrawRect(renderer, &tileRect);
        }
    }

    int currentTileAreaX = 1080; 
    int currentTileAreaY = scrn_h/2; 
    int currentTileAreaSize = LOCAL_TILE_SIZE * 2;

    SDL_Rect currentTileAreaRect = {currentTileAreaX, currentTileAreaY, currentTileAreaSize, currentTileAreaSize};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &currentTileAreaRect);

    int currentTileTextureX = ( currentTileAreaX + LOCAL_TILE_SIZE / 2 ) - 105;
    int currentTileTextureY = scrn_h / 2 - currentTileAreaSize / 2 - 15;

    SDL_Rect currentTileTextureRect = {currentTileTextureX, currentTileTextureY, 5 * LOCAL_TILE_SIZE, 5 * LOCAL_TILE_SIZE};
    SDL_RenderCopy(renderer, tileTextures[currentTile], NULL, &currentTileTextureRect);


    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv){
    init();

    /* INITIALISE MAP WITH 0 30x16 */
    int mapWidth = 960 / LOCAL_TILE_SIZE;
    int mapHeight = scrn_h / LOCAL_TILE_SIZE;
    mapData.resize(mapHeight, std::vector<int>(mapWidth, 0));

    SDL_Event e;

    while(true){
        while (SDL_PollEvent(&e) != 0){
            tile_on_click(e);
        }

        render();
    }

    return 0;
}
