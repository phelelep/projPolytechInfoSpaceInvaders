#include "enemy.h"
#include "tools.h"

#include <stdio.h> 

void createEnemyTextures(
    SDL_Window **window, 
    SDL_Renderer **renderer,
    enemyGreen *green,
    enemyRed *red,
    enemyRose *rose,
    int nrEnemyGreen,
    int nrEnemyRed,
    int nrEnemyRose)
{

    
    for (int i = 0; i < nrEnemyGreen; i++)
    {
        green[i].texture = createTexture(window, renderer, PATH_ENEMY_GREEN);
        green[i].lives = 5;
    }
    for (int i = 0; i < nrEnemyRed; i++)
    {
        red[i].texture = createTexture(window, renderer, PATH_ENEMY_RED);
        red[i].lives = 10;
    }
    for (int i = 0; i < nrEnemyRose; i++)
    {
        rose[i].texture = createTexture(window, renderer, PATH_ENEMY_ROSE);
        rose[i].lives = 1;
    }
}

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
    double enemyPosition)
{

    /// --- GREEN ENEMY --- ///
    
    int spacing = 30;
    int totalWidthGreen = nrEnemyGreen *50 + (nrEnemyGreen - 1) * spacing;
    int startGreen = (WIDTH - totalWidthGreen) / 2;

    int totalWidthRed = nrEnemyRed *80 + (nrEnemyRed - 1) * spacing;
    int startRed = (WIDTH - totalWidthRed) / 2;

    int totalWidthRose = nrEnemyRose *50 + (nrEnemyRose - 1) * spacing;
    int startRose = (WIDTH - totalWidthRose) / 2;
   
    for (int i =0 ; i< nrEnemyGreen; i++)
    {
        SDL_Rect tempRect = {startGreen + i*(spacing+50)+ enemyPosition, 300, 50, 50}; //use temps rect de modify this shit
        green[i].rect = tempRect;
        SDL_RenderCopy(*renderer, green[i].texture, NULL, &green[i].rect);
    }
    for (int i =0 ; i< nrEnemyRed; i++)
    {
        SDL_Rect tempRect2 ={startRed + i*(spacing+80)+ enemyPosition, 200, 80, 50};
        red[i].rect = tempRect2;
        SDL_RenderCopy(*renderer, red[i].texture, NULL, &red[i].rect);
    }
    for (int i =0 ; i< nrEnemyRose; i++)
    {
        SDL_Rect tempRect3 ={startRose + i*(spacing+50)+ enemyPosition, 100, 50, 50};
        rose[i].rect = tempRect3;
        SDL_RenderCopy(*renderer, rose[i].texture, NULL, &rose[i].rect);
    }
}

void destroyEnemyTextures(enemyGreen *green, enemyRed *red, enemyRose *rose,
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose)
{
    for (int i = 0; i < nrEnemyGreen; i++) {
        if (green[i].texture != NULL) {
            SDL_DestroyTexture(green[i].texture);
            green[i].texture = NULL;
            printf("enemyGreenTextures[%d] destroyed\n", i);
        }
    }
    for (int i = 0; i < nrEnemyRed; i++) {
        if (red[i].texture != NULL) {
            SDL_DestroyTexture(red[i].texture);
            red[i].texture = NULL;
            printf("enemyRedTextures[%d] destroyed\n", i);
        }
    }
    for (int i = 0; i < nrEnemyRose; i++) {
        if (rose[i].texture != NULL) {
            SDL_DestroyTexture(rose[i].texture);
            rose[i].texture = NULL;
            printf("enemyRoseTextures[%d] destroyed\n", i);
        }
    }
}


double handleEnemyPosition(double enemyPosition, int *enemyDirection)
{
   if (enemyPosition >=15)
        *enemyDirection = -1; // direction opposé
   else if (enemyPosition <= -15)
        *enemyDirection  =1;

    enemyPosition += *enemyDirection*0.35;

    return enemyPosition;
}