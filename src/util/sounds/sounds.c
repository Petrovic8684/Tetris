#include "sounds.h"

Mix_Music *music_sound = NULL;
Mix_Chunk *clear_row_sound = NULL;

void initialize_sound(void)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "SDL_mixer failed to initialise: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
}

void load_sounds(void)
{
    music_sound = Mix_LoadMUS("assets/sounds/music.wav");

    if (music_sound == NULL)
    {
        fprintf(stderr, "Music failed to load: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    clear_row_sound = Mix_LoadWAV("assets/sounds/clear_row.wav");
    if (clear_row_sound == NULL)
    {
        fprintf(stderr, "Clear row sound failed to load: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
}

void play_music(void)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music_sound, -1);
    }
}

void play_clear_row_sound(void)
{
    Mix_PlayChannel(-1, clear_row_sound, 0);
}

void sound_cleanup(void)
{
    Mix_FreeMusic(music_sound);
    Mix_FreeChunk(clear_row_sound);

    music_sound = NULL;
    clear_row_sound = NULL;
}