#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool is_window_open = true;
bool is_game_lost = false;
float game_speed = STARTING_GAME_SPEED;

int score = 0;
int level = 0;
int lines = 0;

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
        move_current_tetromino(LEFT, true);
        break;
    case SDLK_RIGHT:
        move_current_tetromino(RIGHT, true);
        break;
    case SDLK_DOWN:
        move_current_tetromino(DOWN, true);
        break;
    case SDLK_UP:
        flip_current_tetromino();
        break;
    case SDLK_SPACE:
        // hard_drop();
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
    render_game_text(renderer);

    SDL_RenderPresent(renderer);
}

void initialize_everything(bool is_restart)
{
    if (is_restart == false)
    {
        TTF_Init();
        font = TTF_OpenFont("assets/fonts/runescape.ttf", 36);
        play_sound("assets/sounds/music.wav", &music);
    }

    score = 0;
    level = 0;
    lines = 0;

    game_speed = STARTING_GAME_SPEED;

    initialize_first_tetromino();
    initialize_grid();
}

void increase_lines_and_level(void)
{
    lines++;
    if (lines % 10 == 0)
        level++;

    has_text_changed = true;
}

void increase_score(int8_t rows_cleared_count)
{
    switch (rows_cleared_count)
    {
    case 1:
        score += 40 * (level + 1);
        break;
    case 2:
        score += 100 * (level + 1);
        break;
    case 3:
        score += 300 * (level + 1);
        break;
    case 4:
        score += 1200 * (level + 1);
    case -1:
        score++;
    }

    has_text_changed = true;
}

void start_game_and_keep_running(void)
{
    Uint32 start_time = SDL_GetTicks();
    Uint32 end_time, elapsed_time;

game:
    while (is_window_open == true && is_game_lost == false)
    {
        render();
        poll_events();

        end_time = SDL_GetTicks();
        elapsed_time = end_time - start_time;

        if (elapsed_time > game_speed)
        {
            start_time = end_time;
            move_current_tetromino(DOWN, false);
        }

        update_grid();
    }

    if (is_game_lost)
    {
        is_game_lost = false;
        cleanup(true);
        initialize_everything(true);

        SDL_Delay(1000);
        goto game;
    }
}

void cleanup(bool is_restart)
{
    free(current_tetromino);
    free(grid);
    free(grid_snapshot);

    if (is_restart == false)
    {
        text_cleanup(&score_text);
        text_cleanup(&level_text);
        text_cleanup(&line_text);
        free(font);
        sound_cleanup(&music);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
}