#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "tetromino/tetromino.h"
#include "util/sounds/sounds.h"
#include "util/fonts/fonts.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GRID_WIDTH_CELLS 10
#define GRID_HEIGHT_CELLS 20

static float game_speed = 200.0f;
static bool is_sequence_over = true;

static int board[GRID_WIDTH_CELLS][GRID_HEIGHT_CELLS] = {0};
static struct tetromino *current_tetromino = NULL;

void initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void create_window_and_renderer(const char *title, SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, window, renderer);
    SDL_SetWindowTitle(*window, title);

    if (*window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (*renderer == NULL)
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
        move_tetromino(current_tetromino, LEFT, true);
        break;
    case SDLK_RIGHT:
        move_tetromino(current_tetromino, RIGHT, true);
        break;
    case SDLK_DOWN:
        move_tetromino(current_tetromino, DOWN, true);
        break;
    case SDLK_SPACE:
        flip_tetromino(current_tetromino);
        break;
    }
}

void poll_events(bool *is_window_open)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *is_window_open = false;
            break;
        case SDL_KEYUP:
            handle_input(event);
            break;
        }
    }
}

void render_grid(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

    SDL_Rect cell;
    cell.w = cell.h = 30;

    for (int i = 0; i < GRID_WIDTH_CELLS; i++)
        for (int j = 0; j < GRID_HEIGHT_CELLS; j++)
        {
            cell.x = x + (i * 30);
            cell.y = y + (j * 30);
            SDL_RenderDrawRect(renderer, &cell);
        }
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    render_grid(renderer, 0, 0);
    render_tetromino(renderer, current_tetromino);
    render_score(renderer, 350, 20);

    SDL_RenderPresent(renderer);
    SDL_Delay(game_speed);
}

void generate_new_tetrominos()
{
    if (is_sequence_over == true)
    {
        current_tetromino = (struct tetromino *)malloc(sizeof(struct tetromino));
        current_tetromino = &possible_tetrominos[get_random_tetromino_index()];
        is_sequence_over = false;
    }
}

void keep_window_open(SDL_Renderer *renderer)
{
    bool is_window_open = true;
    play_sound("assets/sounds/music.wav");

    while (is_window_open)
    {
        generate_new_tetrominos();
        render(renderer);
        poll_events(&is_window_open);
        move_tetromino(current_tetromino, DOWN, false);
    }
}

int main(int argc, char *argv[])
{
    initialize_sdl();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    create_window_and_renderer("Tetris", &window, &renderer);
    keep_window_open(renderer);

    sound_cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}