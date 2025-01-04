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
    int nrEnemyRose,
    BulletEnemy *enemyBulletsGreen,
    BulletEnemy *enemyBulletsRed,
    BulletEnemy *enemyBulletsRose)
{

    //green
    for (int i = 0; i < nrEnemyGreen; i++)
    {
        //enemy
        green[i].texture = createTexture(window, renderer, PATH_ENEMY_GREEN);
        if (green[i].texture == NULL)
        {
            printf("Failed to create enemyGreen texture\n");
            cleanup(window, renderer);
        }
        green[i].lives = 5;
        //bullet
        enemyBulletsGreen[i].active = 0;
        enemyBulletsGreen[i].texture = createTexture(window, renderer, PATH_BULLET_ENEMY_GREEN);
        if (enemyBulletsGreen[i].texture == NULL)
        {
            printf("Failed to create enemyGreen bullet texture\n");
            cleanup(window, renderer);
        }

    }
    // red
    for (int i = 0; i < nrEnemyRed; i++)
    {
        red[i].texture = createTexture(window, renderer, PATH_ENEMY_RED);
        if (red[i].texture == NULL)
        {
            printf("Failed to create enemyRed texture\n");
            cleanup(window, renderer);
        }
        else
            printf("enemyRed texture created\n");
        red[i].lives = 10;
        enemyBulletsRed[i].active =0;
        enemyBulletsRed[i].texture = createTexture(window, renderer, PATH_BULLET_ENEMY_RED);
        if (enemyBulletsRed[i].texture == NULL)
        {
            printf("Failed to create enemyRed bullet texture\n");
            cleanup(window, renderer);
        }
        else 
            printf("enemyRed bullet texture created\n");
    }

    //rose
    for (int i = 0; i < nrEnemyRose; i++)
    {
        rose[i].texture = createTexture(window, renderer, PATH_ENEMY_ROSE);
        if (rose[i].texture == NULL)
        {
            printf("Failed to create enemyRose texture\n");
            cleanup(window, renderer);
        }
        else    
            printf("enemyRose texture created\n");
        rose[i].lives = 5;
        enemyBulletsRose[i].active =0;
        enemyBulletsRose[i].texture = createTexture (window, renderer, PATH_BULLET_ENEMY_ROSE);
        if (enemyBulletsRose[i].texture == NULL)
        {
            printf("Failed to create enemyRose bullet texture\n");
            cleanup(window, renderer);
        }
        else 
            printf("enemyRose bullet texture created\n");
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
    double enemyPosition,
    BulletEnemy *enemyBulletsGreen,
    BulletEnemy *enemyBulletsRed,
    BulletEnemy *enemyBulletsRose)
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
        if (green[i].lives >0)
        {
            SDL_Rect tempRect = {startGreen + i*(spacing+50)+ enemyPosition, 300, 50, 50}; //use temps rect de modify this shit
            green[i].rect = tempRect;
            SDL_RenderCopy(*renderer, green[i].texture, NULL, &green[i].rect);

            // bullets (eggs)
            if (!enemyBulletsGreen[i].active)
            {
                printf("Creating new bullet for green enemy and setting status to active\n");
                SDL_Rect tempRect1 = {green[i].rect.x+15, green[i].rect.y+50, 20, 30};
                enemyBulletsGreen[i].rect = tempRect1;
                SDL_RenderCopy(*renderer, enemyBulletsGreen[i].texture,NULL, &enemyBulletsGreen[i].rect);
                enemyBulletsGreen[i].active =1;        
            }
        }
    }
    for (int i =0 ; i< nrEnemyRed; i++)
    {
        if (red[i].lives)
        {
            SDL_Rect tempRect2 ={startRed + i*(spacing+80)- enemyPosition, 200, 80, 50};
            red[i].rect = tempRect2;
            SDL_RenderCopy(*renderer, red[i].texture, NULL, &red[i].rect);

            if (!enemyBulletsRed[i].active)
            {
                SDL_Rect tempRect22 = {red[i].rect.x+30, red[i].rect.y+50, 20, 30};
                enemyBulletsRed[i].rect = tempRect22;
                SDL_RenderCopy(*renderer, enemyBulletsRed[i].texture, NULL, &enemyBulletsRed[i].rect);
                enemyBulletsRed[i].active =1;
            }
        }
    }
    for (int i =0 ; i< nrEnemyRose; i++)
    {
        if (rose[i].lives >0)
        {
            SDL_Rect tempRect3 ={startRose + i*(spacing+50)+ enemyPosition, 100, 50, 50};
            rose[i].rect = tempRect3;
            SDL_RenderCopy(*renderer, rose[i].texture, NULL, &rose[i].rect);

            if (!enemyBulletsRose[i].active)
            {
                SDL_Rect tempRect33 = {rose[i].rect.x+15, rose[i].rect.y+50, 20, 30};
                enemyBulletsRose[i].rect = tempRect33;
                SDL_RenderCopy(*renderer, enemyBulletsRose[i].texture,NULL, &enemyBulletsRose[i].rect); 
                enemyBulletsRose[i].active =1;
            }
        }
    }
}


void handleBulletsEnemy(SDL_Renderer **renderer, 
        BulletEnemy *enemyBulletsGreen,
        BulletEnemy *enemyBulletsRed,
        BulletEnemy *enemyBulletsRose,
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose)
{
    for (int i=0; i< nrEnemyGreen; i++)
    {
        if (enemyBulletsGreen[i].active)
        {
            printf("Bullet %d active\n", i);
            enemyBulletsGreen[i].rect.y += 1;
            SDL_RenderCopy(*renderer, enemyBulletsGreen[i].texture,NULL, &enemyBulletsGreen[i].rect);

            if (enemyBulletsGreen[i].rect.y > HEIGHT-55)
            {
                enemyBulletsGreen[i].active =0; 
                enemyBulletsGreen[i].rect.y +=200; // fix bug
            }
        }
    }

    for (int i = 0; i<nrEnemyRed; i++)
    {
        if (enemyBulletsRed[i].active)
        {
            enemyBulletsRed[i].rect.y += 1;
            SDL_RenderCopy(*renderer, enemyBulletsRed[i].texture, NULL, &enemyBulletsRed[i].rect);

            if (enemyBulletsRed[i].rect.y > HEIGHT-55)
                {
                    enemyBulletsRed[i].active =0;
                    enemyBulletsRed[i].rect.y +=200;
                }
        }
    }

    for (int i=0; i<nrEnemyRose; i++)
    {
        if (enemyBulletsRose[i].active)
        {
            enemyBulletsRose[i].rect.y += 1;
            SDL_RenderCopy(*renderer, enemyBulletsRose[i].texture, NULL, &enemyBulletsRose[i].rect);

            if (enemyBulletsRose[i].rect.y > HEIGHT-55)
            {
                enemyBulletsRose[i].active =0;
                enemyBulletsRose[i].rect.y +=200;
            }
        }
    }
}

void destroyEnemyTextures(enemyGreen *green, enemyRed *red, enemyRose *rose,
            int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose,
            BulletEnemy *bulletsEnemyGreen, BulletEnemy *bulletsEnemyRed, BulletEnemy *bulletsEnemyRose)
{
    for (int i = 0; i < nrEnemyGreen; i++) {
        if (green[i].texture != NULL) {
            SDL_DestroyTexture(green[i].texture);
            green[i].texture = NULL;
            printf("enemyGreenTextures[%d] destroyed\n", i);

            if (bulletsEnemyGreen[i].texture != NULL) {
                SDL_DestroyTexture(bulletsEnemyGreen[i].texture);
                bulletsEnemyGreen[i].texture = NULL;
                printf("enemyGreenBulletTextures[%d] destroyed\n", i);
            }

        }
    }
    for (int i = 0; i < nrEnemyRed; i++) {
        if (red[i].texture != NULL) {
            SDL_DestroyTexture(red[i].texture);
            red[i].texture = NULL;
            printf("enemyRedTextures[%d] destroyed\n", i);

            if (bulletsEnemyRed[i].texture != NULL) {
                SDL_DestroyTexture(bulletsEnemyRed[i].texture);
                bulletsEnemyRed[i].texture = NULL;
                printf("enemyRedBulletTextures[%d] destroyed\n", i);
            }
        }
    }
    for (int i = 0; i < nrEnemyRose; i++) {
        if (rose[i].texture != NULL) {
            SDL_DestroyTexture(rose[i].texture);
            rose[i].texture = NULL;
            printf("enemyRoseTextures[%d] destroyed\n", i);

            if (bulletsEnemyRose[i].texture != NULL) {
                SDL_DestroyTexture(bulletsEnemyRose[i].texture);
                bulletsEnemyRose[i].texture = NULL;
                printf("enemyRoseBulletTextures[%d] destroyed\n", i);
            }
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