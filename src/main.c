#include "game/game.h"

int main(int argc, char *argv[])
{
    initialize_sdl();
    create_window_and_renderer("Tetris");
    initialize_sound();

    initialize_everything(false);
    start_game_and_keep_running();

    cleanup(false);
    SDL_Quit();

    return EXIT_SUCCESS;
}