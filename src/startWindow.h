#pragma once
#include <SDL2/SDL.h>   
#include "tools.h"

typedef struct
{
   SDL_Texture *texture;
   SDL_Rect rect;
   SDL_Color color;
}Draw;

typedef struct
{
    char name[20];
    int score;
}PlayerScore;

typedef struct 
{
    char Name[20];
    int Score;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Color color;
}User;


// pointer arguments (not double pinter) all changes will be lost in the main funciton
int createLoadPage(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state, User *player1);

int createScoreBoard(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state,
                     Draw title, Draw design, Draw playButton, User *player1);

void handlePlayButton(SDL_Renderer **renderer, SDL_Event *event, GameState *state,
                      Draw title, Draw design, Draw playButton,
                      Draw scoreboard, Draw score1, Draw score2, Draw score3, User *player1);

void findTopThreeScores(PlayerScore *playerScore);