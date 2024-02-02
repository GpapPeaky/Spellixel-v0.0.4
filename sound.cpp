#include "sound.h"

void channel_finished_callback(int channel){
    Mix_Chunk *sound = Mix_GetChunk(channel);
    if(sound != NULL){
        Mix_FreeChunk(sound); // Free the memory associated with the Mix_Chunk
    }
}

void load_and_play_wav_music(std::string wav){

    std::string filename = ("src/sfx/music/" + wav + ".wav");

    Mix_Chunk *sound = Mix_LoadWAV(filename.c_str());
    if(sound == NULL){
        fprintf(stderr, "Unable to load WAV file '%s': %s\n", wav.c_str(), Mix_GetError());
        Mix_CloseAudio();
    }

    sound->volume = VOLUME;

    Mix_ChannelFinished(channel_finished_callback); /* Safely frees the memory */

    // while(true){
    //     Mix_PlayChannel(-1, sound, 0); /* BUG */
    // }

    Mix_PlayChannel(-1, sound, 0); /* Currently, the theme is played once */

    /*  TODO: make the theme keep playing until the program is terminated */

    // Mix_FreeChunk(sound); /* Freeing Memory */
}

void load_and_play_wav_sound(std::string wav){

    std::string filename = ("src/sfx/sound/" + wav + ".wav");

    // Load WAV file
    Mix_Chunk *sound = Mix_LoadWAV(filename.c_str());
    if(sound == NULL){
        fprintf(stderr, "Unable to load WAV file '%s': %s\n", wav.c_str(), Mix_GetError());
        Mix_CloseAudio();
    }

    sound->volume = VOLUME - 10; /* Not to produce "earrape" */

    Mix_ChannelFinished(channel_finished_callback); /* Safely frees the memory */

    Mix_PlayChannel(-1, sound, 0);

    // Mix_FreeChunk(sound); /* Freeing Memory */
}
