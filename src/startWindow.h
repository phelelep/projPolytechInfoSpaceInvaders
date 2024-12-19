#pragma once
#include <SDL2/SDL.h>   
//#include "tools.h"

// pointer arguments (not double pinter) all changes will be lost in the main funciton
void createLoadPage(
    SDL_Window *window,
    SDL_Renderer *renderer,
    SDL_Texture *textTexture4Title,
    SDL_Texture *textTexture4Design,
    SDL_Texture *textTexture4Play
    );

void createScoreBoard(
    SDL_Window *window,
    SDL_Renderer *renderer, 
    SDL_Texture *scoreboard, 
    SDL_Texture *score1, 
    SDL_Texture *score2, 
    SDL_Texture *score3
    );