#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>  


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


void handleHeart(SDL_Renderer **renderer, Heart *heart, int playerLives);
void handleBullets(SDL_Renderer **renderer, Bullet *bullet, int nrBullets);


int handlePlayerTouched(SDL_Renderer **renderer, int *playerTouched, Player *player, Heart *heart);
