#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "init_win.h"
#include "utils.h"

#ifndef UI
#define UI

extern SDL_Color text_colour;
extern SDL_Color text_colour_bg;
extern SDL_Surface * text;
extern SDL_Texture * txt;
extern SDL_Texture * b_txt;
extern TTF_Font* font;
extern SDL_FRect rect;
extern SDL_FRect b_rect;
extern SDL_FRect c_rect;

/* TODO: CREATE A BASIC UI THAT WILL SHOW THE ROOM NUMBER, THE NUMBER OF ENEMIES AND THE STATS OF THE PLAYER */

/**
 * @brief Presents data in the UI section of the screen
 * 
 * @param msg Message to display
*/
Render_t render_ui(const char* msg);

/**
 * @brief Updates the UI stats
*/
Update_t update_stats(void);

/**
 * @brief Initialises The UI
*/
Init_t init_ui(void); 

#endif/* UI */
