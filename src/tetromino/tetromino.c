#include "tetromino.h"

struct tetromino possible_tetrominos[NUMBER_OF_TETROMINO_TYPES] = {
    {COLOR_CYAN, shape_I, {0, 0}, {1, 4}, 4, {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},
    {COLOR_YELLOW, shape_O, {0, 0}, {2, 2}, 2, {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {COLOR_MAGENTA, shape_T, {0, 0}, {2, 3}, 3, {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {COLOR_GREEN, shape_S, {0, 0}, {2, 3}, 3, {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}},
    {COLOR_RED, shape_Z, {0, 0}, {2, 3}, 3, {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
    {COLOR_BLUE, shape_J, {0, 0}, {3, 2}, 3, {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}},
    {COLOR_ORANGE, shape_L, {0, 0}, {3, 2}, 3, {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}};

int get_random_tetromino_index(void)
{
    srand(time(NULL));
    return rand() % NUMBER_OF_TETROMINO_TYPES;
}

void move_tetromino(struct tetromino *tetromino, enum movement_direction direction, bool is_user)
{
    switch (direction)
    {
    case LEFT:
        tetromino->position.x--;
        break;
    case RIGHT:
        tetromino->position.x++;
        break;
    case DOWN:
        tetromino->position.y++;
        break;
    }
}

void flip_sizes_of_tetromino(struct tetromino *tetromino)
{
    int temp_size;

    temp_size = (*tetromino).current_size.x;
    (*tetromino).current_size.x = (*tetromino).current_size.y;
    (*tetromino).current_size.y = temp_size;
}

struct tetromino transpose_tetromino(struct tetromino tetromino)
{
    struct tetromino temp = tetromino;
    for (int i = 0; i < tetromino.size; i++)
        for (int j = 0; j < tetromino.size; j++)
        {
            temp.content[i][j] = tetromino.content[j][i];
        }

    return temp;
}

struct tetromino reverse_columns_of_tetromino(struct tetromino tetromino)
{
    struct tetromino temp = tetromino;
    for (int i = 0; i < tetromino.size; i++)
        for (int j = 0; j < tetromino.size / 2; j++)
        {
            bool t = tetromino.content[i][j];
            temp.content[i][j] = tetromino.content[i][tetromino.size - j - 1];
            temp.content[i][tetromino.size - j - 1] = t;
        }

    return temp;
}

void flip_tetromino(struct tetromino *tetromino) // clockwise
{
    memcpy(tetromino->content, transpose_tetromino(*tetromino).content, sizeof(int[4][4]));
    flip_sizes_of_tetromino(tetromino);
    memcpy(tetromino->content, reverse_columns_of_tetromino(*tetromino).content, sizeof(int[4][4]));
}