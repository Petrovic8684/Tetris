#ifndef GRID_H
#define GRID_H

#include "../game/game.h"

#define GRID_WIDTH_CELLS 10
#define GRID_HEIGHT_CELLS 20

struct grid
{
    Uint8 content[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS];
    SDL_Color color[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS];
};

enum grid_style
{
    GRID_ON,
    GRID_ONLY_TETROMINOES,
    GRID_OFF
};

extern bool should_lock;

extern struct grid *grid;
extern struct grid *grid_snapshot;
void initialize_grid(void);
void render_grid(SDL_Renderer *renderer);
void shift_grid_down(Uint8 row);
void check_for_cleared_rows(void);
void make_snapshot(void);
void update_grid(void);

#endif