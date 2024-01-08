#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>

void play_sound(char *path);
void sound_cleanup(void);

#endif