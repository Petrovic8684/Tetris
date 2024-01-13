#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL_ttf.h>
#include "../../game/game.h"

struct text
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect text_rect;
};

extern TTF_Font *font;
extern struct text score_text;
extern struct text level_text;
extern struct text line_text;
extern struct text tetris_text;
extern struct text made_by_text;
extern struct text press_enter_to_start_text;

extern bool has_game_text_changed;
extern bool should_render_tetris_text;

void update_text(SDL_Renderer *renderer, const char *prefix, bool has_variable, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text);
void render_game_text(SDL_Renderer *renderer);
void render_tetris_text(SDL_Renderer *renderer);
void render_menu_text(SDL_Renderer *renderer);
void text_cleanup(struct text *text);

#endif