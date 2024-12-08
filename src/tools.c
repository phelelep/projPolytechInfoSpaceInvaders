#include "tools.h"
#include <stdio.h>
#include <stdlib.h> 


SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char *fontPath, int fontSize, const char *text, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        printf("Failed to open font: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font); /// destroys the fost after it was used to create texture

    if (!texture) {
        printf("Failed to create texture: %s\n", TTF_GetError());
    }
    return texture; 
}
