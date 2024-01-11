#include "grid.h"

bool should_lock = false;
struct grid *grid = NULL;
struct grid *grid_snapshot = NULL;

void initialize_grid(void)
{
    grid = malloc(sizeof(struct grid));
    grid_snapshot = malloc(sizeof(struct grid));

    memset(grid->content, 0, sizeof(Uint8[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
    memset(grid_snapshot->content, 0, sizeof(Uint8[GRID_HEIGHT_CELLS][GRID_WIDTH_CELLS]));
}

void render_grid(SDL_Renderer *renderer)
{
    SDL_Rect cell;
    cell.w = cell.h = TILE_SIZE;

    SDL_Rect rect;
    rect.w = rect.h = TILE_SIZE;

    for (Uint8 i = 0; i < GRID_HEIGHT_CELLS; i++)
        for (Uint8 j = 0; j < GRID_WIDTH_CELLS; j++)
        {
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

            cell.x = j * TILE_SIZE;
            cell.y = i * TILE_SIZE;
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

void shift_grid_down(Uint8 row)
{
    for (Uint8 i = 0; i < row - 2; i++)
        for (Uint8 j = 0; j < GRID_WIDTH_CELLS; j++)
        {
            grid->content[row - i - 1][j] = grid->content[row - i - 2][j];
            grid_snapshot->content[row - i - 1][j] = grid_snapshot->content[row - i - 2][j];
        }

    for (Uint8 j = 0; j < GRID_WIDTH_CELLS; j++)
    {
        grid->content[0][j] = 0;
        grid_snapshot->content[0][j] = 0;
    }

    increase_lines_and_level();
}

void check_for_cleared_rows(void)
{
    auto Uint8 row_sum;
    auto Uint8 row_count = 0;
    for (Uint8 i = 0; i < GRID_HEIGHT_CELLS; i++)
    {
        row_sum = 0;
        for (Uint8 j = 0; j < GRID_WIDTH_CELLS; j++)
            row_sum += grid->content[i][j];

        if (row_sum == GRID_WIDTH_CELLS)
        {
            shift_grid_down(i + 1);
            row_count++;
        }
    }

    increase_score(row_count);
}

bool check_has_reached_end(void)
{
    bool grid_contains = false;
    bool snapshot_contains = false;

    for (Uint8 j = 0; j < GRID_WIDTH_CELLS; j++)
    {
        if (grid->content[0][j] == 1)
            grid_contains = true;
        if (grid_snapshot->content[0][j] == 1)
            snapshot_contains = true;
    }

    if (grid_contains == true && snapshot_contains == true)
        return true;
    return false;
}

void make_snapshot(void)
{
    if (check_has_reached_end())
        is_game_lost = true;

    memcpy(grid_snapshot, grid, sizeof(struct grid));                                                        // locks the current tetromino so it permanently stays on the board.
    memcpy(current_tetromino, &possible_tetrominos[get_random_tetromino_index()], sizeof(struct tetromino)); // generates a new tetromino.
    check_for_cleared_rows();
}

void update_grid(void)
{
    if (current_tetromino->position.y + current_tetromino->current_size.y > GRID_HEIGHT_CELLS) // if the tetromino reaches bottom
        make_snapshot();

    if (should_lock == true)
    {
        make_snapshot();
        should_lock = false;
    }

    memcpy(grid, grid_snapshot, sizeof(struct grid));
    for (Uint8 i = 0; i < current_tetromino->current_size.y; i++)
        for (Uint8 j = 0; j < current_tetromino->current_size.x; j++)
        {
            if (grid->content[i + current_tetromino->position.y][j + current_tetromino->position.x] == 1 && current_tetromino->content[i][j] == 0)
                continue;

            if (grid->content[i + current_tetromino->position.y + 1][j + current_tetromino->position.x] == 1 && current_tetromino->content[i][j] == 1) // if tetrominos overlap
                should_lock = true;

            grid->content[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->content[i][j];
            grid->color[i + current_tetromino->position.y][j + current_tetromino->position.x] = current_tetromino->color;
        }
}