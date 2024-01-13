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
#include "../util/colors/colors.h"
#include "../util/sounds/sounds.h"
#include "../util/fonts/fonts.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define TILE_SIZE 30
#define MAX_FPS 60.0
#define MAX_SCORE 999999
#define STARTING_GAME_SPEED 1060;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern bool is_window_open;
extern bool is_paused;
extern bool is_in_menu;
extern bool is_game_lost;
extern int game_speed;

extern bool can_hard_drop;

extern int score;
extern int level;
extern int lines;

extern bool are_colors_randomized;
extern enum grid_style grid_style;

void initialize_sdl(void);
void create_window_and_renderer(const char *title);
void handle_input(SDL_Event event);
void poll_events(void);
void render(void);
void initialize_everything(bool is_restart);
void increase_game_speed(void);
void increase_lines_and_level(void);
void increase_score(int8_t rows_cleared_count);
void start_game_and_keep_running(void);
void cleanup(bool is_restart);

#endif