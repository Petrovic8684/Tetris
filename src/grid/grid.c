#include "grid.h"

void initialize_grid(void)
{
    grid = malloc(sizeof(struct grid));
    grid_snapshot = malloc(sizeof(struct grid));

    memset(grid->content, 0, sizeof(int[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
    memset(grid_snapshot->content, 0, sizeof(int[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
}

void render_grid(SDL_Renderer *renderer)
{
    SDL_Rect cell;
    cell.w = cell.h = 30;

    SDL_Rect rect;
    rect.w = rect.h = TILE_SIZE;

    for (int i = 0; i < GRID_HEIGHT_CELLS; i++)
        for (int j = 0; j < GRID_WIDTH_CELLS; j++)
        {
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

            cell.x = j * 30;
            cell.y = i * 30;
            SDL_RenderDrawRect(renderer, &cell);

            if (grid->content[i][j] == 1)
            {
                rect.x = j * TILE_SIZE;
                rect.y = i * TILE_SIZE;
                SDL_SetRenderDrawColor(renderer, grid->color[i][j].r, grid->color[i][j].g, grid->color[i][j].b, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
}

void update_grid(void)
{
    if (current_tetromino->position.y + current_tetromino->current_size.y < GRID_HEIGHT_CELLS)
    {
        memcpy(grid, grid_snapshot, sizeof(struct grid));
    }
    for (int i = 0; i < current_tetromino->size; i++)
        for (int j = 0; j < current_tetromino->size; j++)
        {
            if (current_tetromino->position.y + current_tetromino->current_size.y >= GRID_HEIGHT_CELLS)
            {
                memcpy(grid_snapshot, grid, sizeof(struct grid));                                                        // locks the current tetromino so it permanently stays on the board.
                memcpy(current_tetromino, &possible_tetrominos[get_random_tetromino_index()], sizeof(struct tetromino)); // generates a new tetromino.
                return;
            }

            grid->content[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->content[i][j];
            grid->color[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->color;
        }
}