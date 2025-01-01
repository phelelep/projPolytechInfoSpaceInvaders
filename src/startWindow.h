#pragma once
#include <SDL2/SDL.h>   
#include "tools.h"
//#include "tools.h"

// pointer arguments (not double pinter) all changes will be lost in the main funciton
int createLoadPage(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state);

int createScoreBoard(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state);

void handlePlayButton(SDL_Event *event, GameState *state);