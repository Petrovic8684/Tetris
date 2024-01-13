#include "fonts.h"

TTF_Font *font = NULL;
struct text score_text;
struct text level_text;
struct text line_text;

struct text tetris_text;
struct text made_by_text;
struct text press_enter_to_start_text;

bool has_game_text_changed = true;
bool should_render_tetris_text = true;

void update_text(SDL_Renderer *renderer, const char *prefix, bool has_variable, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text)
{
    if (has_variable == true)
    {
        char string[20];
        string[0] = '\0';
        if (add_padding == true)
            sprintf(string, "%s %06d", prefix, variable);
        else
            sprintf(string, "%s %d", prefix, variable);

        text->text_surface = TTF_RenderText_Solid(font, string, color);
    }
    else
    {
        text->text_surface = TTF_RenderText_Solid(font, prefix, color);
    }

    text->text_texture = SDL_CreateTextureFromSurface(renderer, text->text_surface);

    text->text_rect.x = x;
    text->text_rect.y = y;
    text->text_rect.w = text->text_surface->w;
    text->text_rect.h = text->text_surface->h;
}

void render_game_text(SDL_Renderer *renderer)
{
    if (has_game_text_changed == true)
    {
        update_text(renderer, "Score: ", true, score, color_magenta, 350, 20, true, &score_text);
        update_text(renderer, "Level: ", true, level, color_cyan, 350, 60, false, &level_text);
        update_text(renderer, "Lines: ", true, lines, color_red, 350, 100, false, &line_text);
        has_game_text_changed = false;
    }

    SDL_RenderCopy(renderer, score_text.text_texture, NULL, &score_text.text_rect);
    SDL_RenderCopy(renderer, level_text.text_texture, NULL, &level_text.text_rect);
    SDL_RenderCopy(renderer, line_text.text_texture, NULL, &line_text.text_rect);
}

void render_tetris_text(SDL_Renderer *renderer)
{
    if (should_render_tetris_text == true)
    {
        TTF_SetFontSize(font, 70);

        update_text(renderer, "T  E  T  R  I  S", false, -1, get_random_color(), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 30, false, &tetris_text);

        should_render_tetris_text = false;
    }
}

void render_menu_text(SDL_Renderer *renderer)
{
    TTF_SetFontSize(font, 36);
    update_text(renderer, "Made by Jovan Petrovic", false, -1, color_white, WINDOW_WIDTH / 5 + 25, WINDOW_HEIGHT / 3 + 75, false, &made_by_text);
    update_text(renderer, "Press ENTER to start", false, -1, color_white, WINDOW_WIDTH / 5 + 40, WINDOW_HEIGHT / 3 + 125, false, &press_enter_to_start_text);

    SDL_RenderCopy(renderer, tetris_text.text_texture, NULL, &tetris_text.text_rect);
    SDL_RenderCopy(renderer, made_by_text.text_texture, NULL, &made_by_text.text_rect);
    SDL_RenderCopy(renderer, press_enter_to_start_text.text_texture, NULL, &press_enter_to_start_text.text_rect);
};

void text_cleanup(struct text *text)
{
    SDL_FreeSurface(text->text_surface);
    SDL_DestroyTexture(text->text_texture);
}