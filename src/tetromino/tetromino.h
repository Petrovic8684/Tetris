#ifndef TETROMINO_H
#define TETROMINO_H

#include "../game/game.h"

#define MAX_TETROMINO_CONTENT_SIZE 4
#define NUMBER_OF_TETROMINO_TYPES 7

struct vector2
{
    Uint8 x;
    Uint8 y;
};

enum movement_direction
{
    LEFT,
    RIGHT,
    DOWN
};

enum tetromino_shape
{
    SHAPE_I,
    SHAPE_O,
    SHAPE_T,
    SHAPE_S,
    SHAPE_Z,
    SHAPE_J,
    SHAPE_L
};

struct tetromino
{
    SDL_Color color;
    const enum tetromino_shape shape;
    struct vector2 position;
    struct vector2 current_size;
    Uint8 content[MAX_TETROMINO_CONTENT_SIZE][MAX_TETROMINO_CONTENT_SIZE];
};

extern struct tetromino *current_tetromino;
extern struct tetromino possible_tetrominos[NUMBER_OF_TETROMINO_TYPES];

Uint8 get_random_tetromino_index(void);
void move_current_tetromino(enum movement_direction direction, bool is_user);
void transpose_current_tetromino(void);
void reverse_columns_of_current_tetromino(void);
void flip_current_tetromino(void); // clockwise
void initialize_first_tetromino(void);

#endif