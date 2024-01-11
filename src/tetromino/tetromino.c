#include "tetromino.h"

struct tetromino *current_tetromino = NULL;

struct tetromino possible_tetrominos[NUMBER_OF_TETROMINO_TYPES] = {
    {COLOR_CYAN, SHAPE_I, {4, 0}, {1, 4}, {{1}, {1}, {1}, {1}}},
    {COLOR_YELLOW, SHAPE_O, {4, 0}, {2, 2}, {{1, 1}, {1, 1}}},
    {COLOR_MAGENTA, SHAPE_T, {4, 0}, {3, 2}, {{0, 1, 0}, {1, 1, 1}}},
    {COLOR_GREEN, SHAPE_S, {4, 0}, {3, 2}, {{0, 1, 1}, {1, 1, 0}}},
    {COLOR_RED, SHAPE_Z, {4, 0}, {3, 2}, {{1, 1, 0}, {0, 1, 1}}},
    {COLOR_BLUE, SHAPE_J, {4, 0}, {2, 3}, {{0, 1}, {0, 1}, {1, 1}}},
    {COLOR_ORANGE, SHAPE_L, {4, 0}, {2, 3}, {{1, 0}, {1, 0}, {1, 1}}}};

Uint8 get_random_tetromino_index(void)
{
    srand(time(NULL));
    return rand() % NUMBER_OF_TETROMINO_TYPES;
}

void move_current_tetromino(enum movement_direction direction, bool is_user)
{
    switch (direction)
    {
    case LEFT:
        if (current_tetromino->position.x - 1 < 0)
            return;

        current_tetromino->position.x--;
        break;
    case RIGHT:
        if (current_tetromino->position.x + current_tetromino->current_size.x >= GRID_WIDTH_CELLS)
            return;

        current_tetromino->position.x++;
        break;
    case DOWN:
        current_tetromino->position.y++;
        if (is_user == true)
            increase_score(-1);
        break;
    }
}

void transpose_current_tetromino(void)
{
    struct vector2 transposed_size;

    transposed_size.x = current_tetromino->current_size.y;
    transposed_size.y = current_tetromino->current_size.x;

    Uint8 transposed_content[MAX_TETROMINO_CONTENT_SIZE][MAX_TETROMINO_CONTENT_SIZE];

    for (Uint8 i = 0; i < current_tetromino->current_size.y; i++)
        for (Uint8 j = 0; j < current_tetromino->current_size.x; j++)
        {
            transposed_content[j][i] = current_tetromino->content[i][j];
        }

    memcpy(current_tetromino->content, transposed_content, sizeof(Uint8[MAX_TETROMINO_CONTENT_SIZE][MAX_TETROMINO_CONTENT_SIZE]));
    current_tetromino->current_size = transposed_size;
}

void reverse_columns_of_current_tetromino(void)
{
    for (Uint8 i = 0; i < current_tetromino->current_size.y; i++)
        for (Uint8 j = 0; j < current_tetromino->current_size.x / 2; j++)
        {
            bool t = current_tetromino->content[i][j];
            current_tetromino->content[i][j] = current_tetromino->content[i][current_tetromino->current_size.x - j - 1];
            current_tetromino->content[i][current_tetromino->current_size.x - j - 1] = t;
        }
}

void flip_current_tetromino(void) // clockwise
{
    transpose_current_tetromino();
    reverse_columns_of_current_tetromino();
}

void initialize_first_tetromino(void)
{
    current_tetromino = (struct tetromino *)malloc(sizeof(struct tetromino));
    memcpy(current_tetromino, &possible_tetrominos[get_random_tetromino_index()], sizeof(struct tetromino)); // generates a new tetromino.
}