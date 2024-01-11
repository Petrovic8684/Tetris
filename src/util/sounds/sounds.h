#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_audio.h>

struct sound
{
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
};

extern struct sound music;

void play_sound(char *path, struct sound *sound);
void sound_cleanup(struct sound *sound);

#endif