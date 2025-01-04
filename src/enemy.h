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

typedef struct 
{
    SDL_Texture *texture;
    SDL_Rect rect;
    int active;
}BulletEnemy;


void createEnemyTextures(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    enemyGreen *green,
    enemyRed *red,
    enemyRose *rose,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose,
    BulletEnemy *bulletsEnemyGreen,
    BulletEnemy *bulletsEnemyRed,
    BulletEnemy *bulletsEnemyRose);

void handleEnemy(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    enemyGreen *green,
    enemyRed *red,
    enemyRose *rose,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose,
    double enemyPosition,
    BulletEnemy *enemyBulletsGreen,
    BulletEnemy *enemyBulletsRed,
    BulletEnemy *enemyBulletsRose);

void handleBulletsEnemy(SDL_Renderer **renderer, 
            BulletEnemy *bulletsEnemyGreen, 
            BulletEnemy *bulletsEnemyRed, 
            BulletEnemy *bulletsEnemyRose, 
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose);

void destroyEnemyTextures(enemyGreen *green, enemyRed *red, enemyRose *rose,
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose,
            BulletEnemy *bulletsEnemyGreen,
            BulletEnemy *bulletsEnemyRed,
            BulletEnemy *bulletsEnemyRose);

double handleEnemyPosition(double enemyPosition, int *enemyDirection);