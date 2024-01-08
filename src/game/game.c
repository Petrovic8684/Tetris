#include "game.h"

void initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void create_window_and_renderer(const char *title)
{
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, title);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (renderer == NULL)
    {
        fprintf(stderr, "SDL renderer failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void handle_input(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        move_current_tetromino(LEFT);
        break;
    case SDLK_RIGHT:
        move_current_tetromino(RIGHT);
        break;
        // case SDLK_DOWN:  Causes major bug. Revisit.
        // move_current_tetromino(DOWN);
        // break;
    case SDLK_SPACE:
        flip_current_tetromino();
        break;
    }
}

void poll_events(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_window_open = false;
            break;
        case SDL_KEYUP:
            handle_input(event);
            break;
        }
    }
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    render_grid(renderer);
    render_score(renderer, 350, 20);

    SDL_RenderPresent(renderer);
    SDL_Delay(game_speed);
}

void keep_window_open(void)
{
    current_tetromino = (struct tetromino *)malloc(sizeof(struct tetromino));
    memcpy(current_tetromino, &possible_tetrominos[get_random_tetromino_index()], sizeof(struct tetromino)); // generates a new tetromino.
    play_sound("assets/sounds/music.wav");

    initialize_grid();

    while (is_window_open)
    {
        render();
        poll_events();
        move_current_tetromino(DOWN);
        update_grid();
    }
}

void cleanup(void)
{
    free(current_tetromino);
    free(grid);
    free(grid_snapshot);
    sound_cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}