#include "game/game.h"

int main(int argc, char *argv[])
{
    initialize_sdl();
    create_window_and_renderer("Tetris");

    keep_window_open();

    cleanup();
    SDL_Quit();

    return EXIT_SUCCESS;
}