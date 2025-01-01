#pragma once
#include <SDL2/SDL.h>  

int gameStarted(
    SDL_Window **window, 
    SDL_Renderer **renderer, 
    SDL_Event *event, 
    GameState *state);


void createEnemyTextures(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    SDL_Texture **enemyGreenTextures, // pointer to array 
    SDL_Texture **enemyRedTextures,
    SDL_Texture **enemyRoseTextures, 
    int *enemyGreenLives,
    int *enemyRedLives,
    int *enemyRoseLives,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose);

void handleEnemy(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    SDL_Texture **enemyGreenTextures, // pointer to array 
    SDL_Texture **enemyRedTextures,
    SDL_Texture **enemyRoseTextures, 
    int *enemyGreenLives,
    int *enemyRedLives,
    int *enemyRoseLives,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose,
    int indexEnemyTouched,
    double enemyPosition);

void destroyEnemyTextures(
    SDL_Texture **enemyGreenTextures, 
    SDL_Texture **enemyRedTextures, 
    SDL_Texture **enemyRoseTextures,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose);

   