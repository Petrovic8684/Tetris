#include "fonts.h"
#include <stdio.h>

void render_score(SDL_Renderer *renderer, int x, int y)
{
    TTF_Init();

    TTF_Font *Font = TTF_OpenFont("assets/fonts/runescape.ttf", 36);

    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Font, "Score: 0000000", white);

    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}