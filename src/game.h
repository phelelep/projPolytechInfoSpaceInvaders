#pragma once
#include <SDL2/SDL.h>  



int gameStarted(
    SDL_Window **window, 
    SDL_Renderer **renderer, 
    SDL_Event *event, 
    GameState *state);

//If you don’t use typedef, you need to refer to the structure using struct bullet every time:

typedef struct 
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int lives;
}Player;

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int active;
}Heart;


typedef struct 
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int active;
}Bullet;


void asteroidDestroyer(
    SDL_Texture **homeButton, 
    SDL_Texture **score, 
    SDL_Texture **playerTexture, 
    Bullet *bullets, 
    Heart *hearts, 
    int nrBullets, 
    int playerLives);

void handleHeart(SDL_Renderer **renderer, Heart *heart, int playerLives);
void handleBullets(SDL_Renderer **renderer, Bullet *bullet, int nrBullets);


   