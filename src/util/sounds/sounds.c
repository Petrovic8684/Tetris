#include "sounds.h"

SDL_AudioDeviceID device_id;
struct sound music;

void play_sound(char *path, struct sound *sound)
{
    SDL_LoadWAV(path, &sound->wav_spec, &sound->wav_buffer, &sound->wav_length);

    SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &sound->wav_spec, NULL, 0);
    Uint8 success = SDL_QueueAudio(device_id, sound->wav_buffer, sound->wav_length);
    SDL_PauseAudioDevice(device_id, 0);
}

void sound_cleanup(struct sound *sound)
{
    if (device_id)
        SDL_CloseAudioDevice(device_id);
    SDL_FreeWAV(sound->wav_buffer);
}