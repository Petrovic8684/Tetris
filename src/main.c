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

static bool should_spawn_tetromino = true;

static float game_speed = 150.0f;

struct grid
{
    int content[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS];
    SDL_Color color[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS];
};

static struct grid grid, grid_snapshot;

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
    SDL_Rect cell;
    cell.w = cell.h = 30;

    SDL_Rect rect;
    rect.w = rect.h = TILE_SIZE;

    for (int i = 0; i < GRID_HEIGHT_CELLS; i++)
        for (int j = 0; j < GRID_WIDTH_CELLS; j++)
        {
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

            cell.x = x + (j * 30);
            cell.y = y + (i * 30);
            SDL_RenderDrawRect(renderer, &cell);

            if (grid.content[i][j] == 1)
            {
                rect.x = j * TILE_SIZE;
                rect.y = i * TILE_SIZE;
                SDL_SetRenderDrawColor(renderer, grid.color[i][j].r, grid.color[i][j].g, grid.color[i][j].b, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
}

void lock_current_tetromino(void)
{
    memcpy(&grid_snapshot, &grid, sizeof(struct grid));
    current_tetromino = NULL;
    free(current_tetromino);
    should_spawn_tetromino = true;
}

void print_grid(void)
{
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++)
    {
        for (int j = 0; j < GRID_WIDTH_CELLS; j++)
        {
            fprintf(stdout, "%d ", grid.content[i][j]);
        }
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n\n");
}

void update_grid(void)
{
    memcpy(&grid, &grid_snapshot, sizeof(struct grid));
    for (int i = 0; i < current_tetromino->size; i++)
        for (int j = 0; j < current_tetromino->size; j++)
        {
            if (i + current_tetromino->position.y + current_tetromino->current_size.y > GRID_HEIGHT_CELLS)
            {
                lock_current_tetromino();
                return;
            }
            grid.content[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->content[i][j];
            grid.color[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->color;
        }

    print_grid();
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    render_grid(renderer, 0, 0);
    render_score(renderer, 350, 20);

    SDL_RenderPresent(renderer);
    SDL_Delay(game_speed);
}

void generate_new_tetrominos()
{
    if (should_spawn_tetromino == true)
    {
        current_tetromino = (struct tetromino *)malloc(sizeof(struct tetromino));
        memcpy(current_tetromino, &possible_tetrominos[get_random_tetromino_index()], sizeof(struct tetromino));
        should_spawn_tetromino = false;
    }
}

void initialize_grid(void)
{
    memset(&grid.content, 0, sizeof(int[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
    memset(&grid_snapshot.content, 0, sizeof(int[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
}

void keep_window_open(SDL_Renderer *renderer)
{
    bool is_window_open = true;
    play_sound("assets/sounds/music.wav");

    initialize_grid();

    while (is_window_open)
    {
        generate_new_tetrominos();
        render(renderer);
        poll_events(&is_window_open);
        move_tetromino(current_tetromino, DOWN, false);
        update_grid();
    }
}

int main(int argc, char *argv[])
{
    initialize_sdl();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    create_window_and_renderer("Tetris", &window, &renderer);
    keep_window_open(renderer);

    free(current_tetromino);
    sound_cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}