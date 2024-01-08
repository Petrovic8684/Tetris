#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "../tetromino/tetromino.h"
#include "../grid/grid.h"
#include "../util/colors.h"
#include "../util/sounds/sounds.h"
#include "../util/fonts/fonts.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define TILE_SIZE 30

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static bool is_window_open = true;
static float game_speed = 150.0f;

void initialize_sdl(void);
void create_window_and_renderer(const char *title);
void handle_input(SDL_Event event);
void poll_events(void);
void render(void);
void keep_window_open(void);
void cleanup(void);

#endif