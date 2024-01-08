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

static struct grid *grid, *grid_snapshot;
void initialize_grid(void);
void render_grid(SDL_Renderer *renderer);
void update_grid(void);

#endif