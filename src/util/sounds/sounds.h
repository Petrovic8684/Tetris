#ifndef SOUNDS_H
#define SOUNDS_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

extern Mix_Music *music_sound;
extern Mix_Chunk *clear_row_sound;

void initialize_sound(void);
void load_sounds(void);
void play_music(void);
void play_clear_row_sound(void);
void sound_cleanup(void);

#endif