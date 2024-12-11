#include "init_win.h"

float render_factor;
int true_x;
int true_y;
SDL_Window* win;
SDL_Renderer* renderer;
SDL_Surface* sprite;
SDL_Texture* pltexture;
SDL_Cursor* CURSOR;
Sprite pl; /* Player */
Sprite bullet; /* Bullets */

/* From def.aux */
int screen_x;
int screen_y;

/* MUST: CONFIGURE THE BACKGROUND SIZE PROBLEM (test on laptop) NATIVE_SIZE -> NEWWINDOWSIZE */

void load_sprite_init(const char* name){

    srand(time(NULL)); /* Initialise once */

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO); /* Initialises the GUI library */
    IMG_Init(IMG_INIT_PNG);
    TTF_Init(); /* Initialise The Library */

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    int local_x = display_mode.w;
    int local_y = display_mode.h;

    float diagonal_size = std::sqrt(local_x * local_x + local_y * local_y);

    const float base_diagonal_size = std::sqrt(1920 * 1920 + 1080 * 1080);

    render_factor = diagonal_size / base_diagonal_size; /* Calculate the factor */

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 1000;

    /*  Initialise the mixer */
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

    /*___________________________________________________________________________________________*/

    SDL_Surface* icon = IMG_Load("assets/sprites/icon.png");

    win = SDL_CreateWindow(name,0,0,SCREEN_HEIGHT,SCREEN_WIDTH,SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); /* Create A Window */
    renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */
    SDL_GetWindowSize(win, &screen_x, &screen_y);
    SDL_SetWindowIcon(win, icon);

    pl.sprite_bmp = IMG_Load("assets/sprites/pitt.png"); /* PLAYER TEXTURE */

    pl.HP = 100; /* Base health */
    pl.Bullets.dmg = 5; /* Base damage */
    pl.pos.h = PLAYER_SIZE_Y * render_factor;
    pl.pos.w = PLAYER_SIZE_X * render_factor;
    pl.pos.y = 300;
    pl.pos.x = 900;
    pl.acc.velocity_x = 0.0f;
    pl.acc.velocity_y = 0.0f;

    pltexture = SDL_CreateTextureFromSurface(renderer,pl.sprite_bmp);
    SDL_FreeSurface(pl.sprite_bmp);

    Sprite cursor; /* Load it as a sprite (Surface will be deleted later) */

    cursor.sprite_bmp = IMG_Load("assets/sprites/cursor.png"); /* It show the actual size of the image */                                      

    SDL_Cursor* CURSOR = SDL_CreateColorCursor(cursor.sprite_bmp,0,0);                          

    SDL_SetCursor(CURSOR);                                                                      

    SDL_ShowCursor(SDL_ENABLE);                                                                     

    SDL_FreeSurface(cursor.sprite_bmp);

    SDL_RenderClear(renderer);
}
