#include <stdio.h>
#include <stdlib.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL.h>   
#include "tools.h"


SDL_Texture* createTextTexture(SDL_Renderer **renderer, const char *fontPath, int fontSize, const char *text, SDL_Color color) 
{
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

    SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font); /// destroys the fost after it was used to create texture

    if (!texture) {
        printf("Failed to create texture: %s\n", TTF_GetError());
    }
    return texture; 
}


void cleanup(SDL_Window **window, SDL_Renderer **renderer) 
{
    printf("Cleaning up resources...\n");
    
    // Destroy window and renderer
    if (*window)
    {
        SDL_DestroyWindow(*window);
        printf("Window destroyed\n");
    }
    if (*renderer)
    {
        SDL_DestroyRenderer(*renderer);
        printf("Renderer destroyed\n");
    }
    // Quit SDL_ttf and SDL
    TTF_Quit(); 
    SDL_Quit();

    exit(EXIT_SUCCESS);
}


SDL_Texture* createTexture(SDL_Window **window, SDL_Renderer **renderer, const char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) 
    {
        printf("Failed to load image! SDL_image Error: %s\n", IMG_GetError());
        cleanup(window, renderer);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) 
    {
        printf("Failed to create texture! SDL Error: %s\n", SDL_GetError());
        cleanup(window, renderer);
    }

    return texture;
}