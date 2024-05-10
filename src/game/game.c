#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool is_window_open = true;
bool is_paused = false;
bool is_in_menu = true;
bool is_game_lost = false;
int game_speed = STARTING_GAME_SPEED;

bool can_hard_drop = true;

int score = 0;
int level = 0;
int lines = 0;

bool are_colors_randomized = false;
enum grid_style grid_style = GRID_ON;

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
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

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
    case SDLK_RETURN:
        if (is_in_menu == false)
            return;
        is_in_menu = false;
        break;
    case SDLK_ESCAPE:
        if (is_in_menu == true)
            return;
        if (is_paused == true)
            is_paused = false;

        is_in_menu = true;
    case SDLK_p:
        if (is_in_menu == true)
            return;
        is_paused = !is_paused;
        has_game_text_changed = true;
        break;
    case SDLK_LEFT:
        if (is_in_menu == true || is_paused == true)
            return;
        move_current_tetromino(LEFT, true);
        break;
    case SDLK_RIGHT:
        if (is_in_menu == true || is_paused == true)
            return;
        move_current_tetromino(RIGHT, true);
        break;
    case SDLK_DOWN:
        if (is_in_menu == true || is_paused == true)
            return;
        move_current_tetromino(DOWN, true);
        break;
    case SDLK_UP:
        if (is_in_menu == true || is_paused == true)
            return;
        flip_current_tetromino();
        break;
    case SDLK_SPACE:
        if (is_in_menu == true || is_paused == true)
            return;
        if (can_hard_drop == true)
        {
            hard_drop();
            can_hard_drop = false;
        }
        break;
    case SDLK_g:
        if (is_in_menu == true || is_paused == true)
            return;
        grid_style = (grid_style + 1) % 3;
        break;
    case SDLK_c:
        if (is_in_menu == true || is_paused == true)
            return;

        are_colors_randomized = !are_colors_randomized;
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
    SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
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

        load_sounds();
        play_music();
    }

    score = 0;
    level = 0;
    lines = 0;

    has_game_text_changed = true;

    game_speed = STARTING_GAME_SPEED;

    initialize_first_tetromino();
    initialize_grid();
}

inline void increase_game_speed(void)
{
    game_speed = STARTING_GAME_SPEED - 35 * level;
}

void increase_lines_and_level(void)
{
    lines++;
    if (lines % 10 == 0 && level < 30)
    {
        level++;
        increase_game_speed();
    }

    has_game_text_changed = true;
}

void increase_score(int8_t rows_cleared_count)
{
    if (score >= MAX_SCORE)
        return;

    switch (rows_cleared_count)
    {
    case 1:
        if (score + 40 * (level + 1) >= MAX_SCORE)
            return;
        score += 40 * (level + 1);
        break;
    case 2:
        if (score + 100 * (level + 1) >= MAX_SCORE)
            return;
        score += 100 * (level + 1);
        break;
    case 3:
        if (score + 300 * (level + 1) >= MAX_SCORE)
            return;
        score += 300 * (level + 1);
        break;
    case 4:
        if (score + 1200 * (level + 1) >= MAX_SCORE)
            return;
        score += 1200 * (level + 1);
    case -1:
        if (score + 1 >= MAX_SCORE)
            return;
        score++;
    }

    has_game_text_changed = true;
}

void restart_game(void)
{
    is_game_lost = false;
    cleanup(true);
    initialize_everything(true);
}

void start_game_and_keep_running(void)
{
    Uint32 start_time = SDL_GetTicks();
    Uint32 end_time, elapsed_time;

menu:
    restart_game();
    while (is_window_open == true && is_in_menu == true)
    {
        SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
        SDL_RenderClear(renderer);

        end_time = SDL_GetTicks();
        elapsed_time = end_time - start_time;

        if (elapsed_time > 1500)
        {
            start_time = end_time;
            should_render_tetris_text = true;
        }

        render_tetris_text(renderer);
        render_menu_text(renderer);

        poll_events();
        SDL_RenderPresent(renderer);
    }

    start_time = SDL_GetTicks();

game:
    while (is_window_open == true && is_game_lost == false)
    {
        render();
        poll_events();

        if (is_in_menu == true)
            goto menu;

        if (is_paused == false)
        {
            end_time = SDL_GetTicks();
            elapsed_time = end_time - start_time;

            if (elapsed_time > game_speed)
            {
                start_time = end_time;
                if (can_hard_drop == false)
                    can_hard_drop = true;
                move_current_tetromino(DOWN, false);
            }

            update_grid();
        }
    }

    if (is_game_lost)
    {
        restart_game();
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
        text_cleanup(&tetris_text);
        text_cleanup(&made_by_text);
        text_cleanup(&press_enter_to_start_text);
        sound_cleanup();
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
}