#pragma once
#include <SDL2/SDL.h>  
#include "enemy.h"
#include "player.h"
#include "startWindow.h"


typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Color color;
    int value;
}Score;


int gameStarted(
    SDL_Window **window, 
    SDL_Renderer **renderer, 
    SDL_Event *event, 
    GameState *state,
    User *player1);




void asteroidDestroyer(
    SDL_Texture **homeButton, 
    Score *score, 
    SDL_Texture **playerTexture, 
    Bullet *bullets, 
    Heart *hearts, 
    int nrBullets, 
    int playerLives);



int checkCollisionEnemy(
    Bullet *bullets, 
    int nrBullets,
    enemyGreen *green, 
    enemyRed *red, 
    enemyRose *rose, 
    int nrEnemyGreen, 
    int nrEnemyRed, 
    int nrEnemyRose,
    int *nrTotalDeadEnemy,
    Score *score);

int checkCollisionPlayer(
    Player player, 
    BulletEnemy *bulletsEnemyGreen, 
    BulletEnemy *bulletsEnemyRed, 
    BulletEnemy *bulletsEnemyRose, 
    int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose);


void handleLevelPassed (SDL_Renderer **renderer, int levelPassed, SDL_Color color);


void saveScore(User *player1, Score *score);


   