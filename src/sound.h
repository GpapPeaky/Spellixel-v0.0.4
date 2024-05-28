#include  <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>
#include "init_win.h"
#include "macros.h"

#ifndef SOUND
#define SOUND

/**
 * @brief Fress the allocated memory of an audio channel
 * 
 * @param channel Channel to be fried
*/
void channel_finished_callback(int channel);

/**
 * @brief Loads a .wav file (FROM MUSIC)
 * 
 * @param wav Wav file to be loaded 
*/
void load_and_play_wav_music(std::string wav);

/**
 * @brief Loads a .wav file (FROM SOUND)
 * 
 * @param wav Wav file to be loaded 
*/
void load_and_play_wav_sound(std::string wav);


#endif /* SOUND */
