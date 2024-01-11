#include "fonts.h"

TTF_Font *font = NULL;
struct text score_text;
struct text level_text;
struct text line_text;

bool has_text_changed = true;

void update_game_text(SDL_Renderer *renderer, const char *prefix, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text)
{
    char string[20];
    string[0] = '\0';

    if (add_padding == true)
        sprintf(string, "%s %06d", prefix, variable);
    else
        sprintf(string, "%s %d", prefix, variable);

    text->text_surface = TTF_RenderText_Solid(font, string, color);
    text->text_texture = SDL_CreateTextureFromSurface(renderer, text->text_surface);

    text->text_rect.x = x;
    text->text_rect.y = y;
    text->text_rect.w = text->text_surface->w;
    text->text_rect.h = text->text_surface->h;
}

void render_game_text(SDL_Renderer *renderer)
{
    if (has_text_changed == true)
    {
        update_game_text(renderer, "Score: ", score, color_magenta, 350, 20, true, &score_text);
        update_game_text(renderer, "Level: ", level, color_cyan, 350, 60, false, &level_text);
        update_game_text(renderer, "Lines: ", lines, color_red, 350, 100, false, &line_text);
        has_text_changed = false;
    }

    SDL_RenderCopy(renderer, score_text.text_texture, NULL, &score_text.text_rect);
    SDL_RenderCopy(renderer, level_text.text_texture, NULL, &level_text.text_rect);
    SDL_RenderCopy(renderer, line_text.text_texture, NULL, &line_text.text_rect);
}

void text_cleanup(struct text *text)
{
    SDL_FreeSurface(text->text_surface);
    SDL_DestroyTexture(text->text_texture);
}