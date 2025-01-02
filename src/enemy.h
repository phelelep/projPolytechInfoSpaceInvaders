#pragma once 
#include <SDL2/SDL.h> 

typedef struct 
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int lives;
}enemyGreen;

typedef struct 
{
   SDL_Texture *texture;
   SDL_Rect rect;
   int lives;
}enemyRed;

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int lives;
}enemyRose;


void createEnemyTextures(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    enemyGreen *green,
    enemyRed *red,
    enemyRose *rose,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose);

void handleEnemy(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    enemyGreen *green,
    enemyRed *red,
    enemyRose *rose,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose,
    int indexEnemyTouched,
    double enemyPosition);

void destroyEnemyTextures(enemyGreen *green, enemyRed *red, enemyRose *rose,
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose);

double handleEnemyPosition(double enemyPosition, int *enemyDirection);