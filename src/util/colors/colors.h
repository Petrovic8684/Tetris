#ifndef COLORS_H
#define COLORS_H

#include <SDL2/SDL.h>

#define COLOR_WHITE        \
    {                      \
        255, 255, 255, 255 \
    }

#define COLOR_GRAY      \
    {                   \
        20, 20, 20, 255 \
    }

#define COLOR_BLACK  \
    {                \
        0, 0, 0, 255 \
    }

#define COLOR_CYAN       \
    {                    \
        0, 255, 255, 255 \
    }

#define COLOR_YELLOW     \
    {                    \
        255, 255, 0, 255 \
    }

#define COLOR_GREEN    \
    {                  \
        0, 255, 0, 255 \
    }

#define COLOR_MAGENTA    \
    {                    \
        255, 0, 255, 255 \
    }

#define COLOR_ORANGE     \
    {                    \
        255, 129, 0, 255 \
    }

#define COLOR_RED      \
    {                  \
        255, 0, 0, 255 \
    }

#define COLOR_BLUE     \
    {                  \
        0, 0, 255, 255 \
    }

extern const SDL_Color color_magenta;
extern const SDL_Color color_cyan;
extern const SDL_Color color_red;
extern const SDL_Color color_gray;
extern const SDL_Color color_black;

#endif