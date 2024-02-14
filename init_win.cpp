#include "init_win.h"

/**
 * @include in macros
 * @ifnot organise / optimize them
*/

int true_x;
int true_y;

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Surface* sprite;
SDL_Texture* pltexture;
SDL_Cursor* CURSOR;
Sprite pl; /* Player */
Sprite bullet; /* Bullets */
Sprite fence;

/*___________________________________________________________________________________________*/

// void init_background(void){

//     background_tile1.sprite_bmp = IMG_Load("src/sprites/tiles/tile (3).png");
//     background_tile_texture1 = SDL_CreateTextureFromSurface(renderer, background_tile1.sprite_bmp);
//     SDL_FreeSurface(background_tile1.sprite_bmp);

//     fence.sprite_bmp = IMG_Load("src/sprites/tiles/tile (15).png");
//     fence.sprite_texture = SDL_CreateTextureFromSurface(renderer,fence.sprite_bmp);
//     SDL_FreeSurface(fence.sprite_bmp);
// }

// void render_background(void){

//     true_x = screen_x / MESH_SIZE;
//     true_y = screen_y / MESH_SIZE + 1; /* The size is correct */

//     for (int i = 0 ; i < true_x; i++) {
//         for (int ii = 0 ; ii < true_y; ii++) {

//             SDL_FRect pos;

//             pos.h = MESH_SIZE;
//             pos.w = MESH_SIZE;
//             pos.x = i * MESH_SIZE;
//             pos.y = ii * MESH_SIZE;

//             SDL_RenderCopyF(renderer, background_tile_texture1, NULL, &pos);
//         }
//     }

//     fence.pos.w = MESH_SIZE;
//     fence.pos.h = MESH_SIZE;

//     for(int i = 0 ; i < screen_x / MESH_SIZE + 1; i++){
//         fence.pos.y = 0;
//         fence.pos.x = i * MESH_SIZE;

//         SDL_RenderCopyF(renderer,fence.sprite_texture, NULL, &fence.pos);   
//     }

//     for(int i = 0 ; i < screen_x / MESH_SIZE + 1; i++){
//         fence.pos.y = screen_y - MESH_SIZE;
//         fence.pos.x = i * MESH_SIZE;

//         SDL_RenderCopyF(renderer,fence.sprite_texture, NULL, &fence.pos);   
//     }

//     /**
//      * @note Fences this will have to change depending on the room seed that generates randomly
//     */
// }

/*___________________________________________________________________________________________*/

/* TODO: CONFIGURE THE BACKGROUND SIZE PROBLEM (test on laptop) */

void load_sprite_init(const char* name){

    #pragma region INIT

    srand(time(NULL)); /* Initialise once */

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO); /* Initialises the GUI library */
    IMG_Init(IMG_INIT_PNG);
    TTF_Init(); /* Initialise The Library */

   #pragma region AUDIO

        int audio_rate = 22050;
        Uint16 audio_format = AUDIO_S16SYS;
        int audio_channels = 2;
        int audio_buffers = 1000;

        /*  Initialise the mixer */
        Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

        /*___________________________________________________________________________________________*/

        SDL_Surface* icon = IMG_Load("src/sprites/icon.png");

        win = SDL_CreateWindow(name,0,0,SCREEN_HEIGHT,SCREEN_WIDTH,SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); /* Create A Window */
        renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */
        SDL_GetWindowSize(win, &screen_x, &screen_y);
        SDL_SetWindowIcon(win, icon);

    #pragma endregion AUDIO

    pl.sprite_bmp = IMG_Load("src/sprites/pitt.png"); /* PLAYER TEXTURE */

    pl.HP = 100; /* Base health */
    pl.Bullets.dmg = 5; /* Base damage */
    pl.pos.h = PLAYER_SIZE_Y;
    pl.pos.w = PLAYER_SIZE_X;
    pl.pos.y = 300;
    pl.pos.x = 900;
    pl.acc.velocity_x = 0.0f;
    pl.acc.velocity_y = 0.0f;

    pltexture = SDL_CreateTextureFromSurface(renderer,pl.sprite_bmp);
    SDL_FreeSurface(pl.sprite_bmp);

    #pragma endregion INIT

    #pragma region CURSOR

    Sprite cursor; /* Load it as a sprite (Surface will be deleted later) */

    cursor.sprite_bmp = IMG_Load("src/sprites/cursor.png"); /* It show the actual size of the image */                                      

    SDL_Cursor* CURSOR = SDL_CreateColorCursor(cursor.sprite_bmp,0,0);                          

    SDL_SetCursor(CURSOR);                                                                      

    SDL_ShowCursor(SDL_ENABLE);                                                                     

    SDL_FreeSurface(cursor.sprite_bmp);

    #pragma endregion CURSOR

    SDL_RenderClear(renderer);
}
