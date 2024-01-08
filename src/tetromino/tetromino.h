#ifndef TETROMINO_H
#define TETROMINO_H

#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../util/colors.h"

#define MAX_TETROMINO_CONTENT_SIZE 4
#define NUMBER_OF_TETROMINO_TYPES 7

struct vector2
{
    int x;
    int y;
};

enum movement_direction
{
    LEFT,
    RIGHT,
    DOWN
};

enum tetromino_shape
{
    shape_I,
    shape_O,
    shape_T,
    shape_S,
    shape_Z,
    shape_J,
    shape_L
};

struct tetromino
{
    const SDL_Color color;
    const enum tetromino_shape shape;
    struct vector2 position;
    struct vector2 current_size;
    int size;
    int content[MAX_TETROMINO_CONTENT_SIZE][MAX_TETROMINO_CONTENT_SIZE];
};

extern struct tetromino *current_tetromino;
extern struct tetromino possible_tetrominos[NUMBER_OF_TETROMINO_TYPES];

int get_random_tetromino_index(void);
void render_tetromino(SDL_Renderer *renderer, struct tetromino *tetromino);
void move_tetromino(struct tetromino *tetromino, enum movement_direction direction, bool is_user);
struct tetromino transpose_tetromino(struct tetromino tetromino);
struct tetromino reverse_columns_of_tetromino(struct tetromino tetromino);
void flip_tetromino(struct tetromino *tetromino); // clockwise

#endif