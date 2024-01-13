#include "colors.h"

const SDL_Color color_white = COLOR_WHITE;
const SDL_Color color_gray = COLOR_GRAY;
const SDL_Color color_black = COLOR_BLACK;
const SDL_Color color_cyan = COLOR_CYAN;
const SDL_Color color_yellow = COLOR_YELLOW;
const SDL_Color color_green = COLOR_GREEN;
const SDL_Color color_magenta = COLOR_MAGENTA;
const SDL_Color color_orange = COLOR_ORANGE;
const SDL_Color color_red = COLOR_RED;
const SDL_Color color_blue = COLOR_BLUE;

SDL_Color get_random_color(void)
{
    SDL_Color random_color;

    random_color.r = rand() * 255;
    random_color.g = rand() * 255;
    random_color.b = rand() * 255;

    return random_color;
}