#include <stdio.h>
#include "tools.h"
#include "game.h"
#include "enemy.h"

int gameStarted(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state)
{   
    
    // home button
    SDL_Color color = COLOR_PLANETARY_BLUE;
    SDL_Texture *score = createTextTexture(renderer, PATH_PREMIER, 50, "Score", color);

    // home button
    SDL_Texture *homeButton= createTexture(window, renderer, PATH_HOME);    
    
    
    // player
    Player player;
    player.texture = createTexture(window, renderer, PATH_PLAYER);
    player.rect = (SDL_Rect){WIDTH/2 - 50, HEIGHT - 50, 40, 35};
    player.lives = 3;
    Heart heart[player.lives];
    for (int i = 0; i < player.lives; i++)
    {  
        heart[i].texture = createTexture(window, renderer, PATH_HEART);
        heart[i].rect = (SDL_Rect){20 + i*30,HEIGHT- 40, 20, 20};
        heart[i].active = 1;
    }
    
    //bullets
    int nrBullets = 15;
    int indexBullet = 0;
    Bullet bullet[nrBullets];
    for (int i =0; i<nrBullets; i++)
    {
        bullet[i].texture = createTexture(window, renderer, PATH_BULLET);
        bullet[i].rect.w = 15;
        bullet[i].rect.h = 15;
        bullet[i].active = 0;
    }
 


    /// --- enemy --- ///
    int nrEnemyGreen = 2;
    int nrEnemyRed = 2;
    int nrEnemyRose = 2;

    enemyGreen green[nrEnemyGreen];
    enemyRed red[nrEnemyRed];
    enemyRose rose[nrEnemyRose];


    /// --- enemy Bullets ---/// 
    BulletEnemy bulletsEnemyGreen[nrEnemyGreen];
    BulletEnemy bulletsEnemyRed[nrEnemyRed];
    BulletEnemy bulletsEnemyRose[nrEnemyRose];

    createEnemyTextures(window, renderer, 
                green, red, rose,
                nrEnemyGreen, nrEnemyRed, nrEnemyRose,
                bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose);


    /// --- RECTS --- ///
   // SDL_Rect homeColorButtonRect = {20, 20 , 50, 50};
    SDL_Rect scoreRect = {WIDTH - 150, 20, 70, 25};
    SDL_Rect homeButtonRect = {20, 20 , 50, 50}; // x posiiton départ ,y ,width,hight 


    /// --- init variables ---///
    double enemyPosition = 0;
    int enemyDirection =1;
    int levelPassed =0;
    int nrTotalDeadEnemy= 0;
    int playerTouched = 0;
    int playerDead =0;

    while (*state == GAME_STARTED) 
    {
        while (SDL_PollEvent(event)) 
        {
            if (event->type == SDL_QUIT)  //quited
            {
                *state = GAME_OVER;
                /// --- CLEANUP --- ///
                asteroidDestroyer(&homeButton, &score, &player.texture, bullet, heart, nrBullets, player.lives);
                destroyEnemyTextures(green, red, rose, nrEnemyGreen, nrEnemyRed, nrEnemyRose, bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose);
                return 0;
            }
            else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) 
            {
                int mouseX = event->button.x;
                int mouseY = event->button.y;
                if (mouseX>= homeButtonRect.x && mouseX <=(homeButtonRect.x + homeButtonRect.w) && 
                    mouseY>= homeButtonRect.y && mouseY <=(homeButtonRect.y)+ homeButtonRect.h)
                {  
                    printf("Exit button clicked\n");
                    *state = LOAD_PAGE;
                    /// --- CLEANUP --- ///
                    asteroidDestroyer(&homeButton, &score, &player.texture, bullet, heart, nrBullets, player.lives);
                    destroyEnemyTextures(green, red, rose, nrEnemyGreen, nrEnemyRed, nrEnemyRose, bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose);
                    return 0;
                }
            }
            // kayboard button pressed
            else if (event->type ==SDL_KEYDOWN)
            {
                printf("Key pressed : %c\n", event->key.keysym.sym);
                switch (event->key.keysym.sym)
                {
                     case SDLK_LEFT:
                        if (player.rect.x > 0) 
                            player.rect.x -= 14; 
                        break;
                    case SDLK_RIGHT:
                        if (player.rect.x < (WIDTH - player.rect.w))
                            player.rect.x += 14;
                        break;
                    case SDLK_SPACE :
                        bullet[indexBullet].rect.x = player.rect.x + 13;
                        bullet[indexBullet].rect.y = player.rect.y - 10;
                        bullet[indexBullet].active = 1;
                        indexBullet = (indexBullet + 1) % nrBullets; // when Bullets = max -> Bullets =0
                        break;
                }
            }
        }
       
        SDL_Delay(20); 
        
        /// --- enemy movement
        enemyPosition = handleEnemyPosition(enemyPosition, &enemyDirection);


        /// --- Clear the renderer and redraw everything
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255); // Set to black
        SDL_RenderClear(*renderer);

        SDL_RenderCopy(*renderer, homeButton, NULL, &homeButtonRect);
        SDL_RenderCopy(*renderer, score, NULL, &scoreRect);
        SDL_RenderCopy(*renderer, player.texture, NULL, &player.rect);


        handleHeart(renderer, heart, player.lives);
       
        if (!playerDead)
        {
            handleEnemy(window, renderer,
                        green, red, rose,
                        nrEnemyGreen, nrEnemyRed, nrEnemyRose,
                        enemyPosition, 
                        bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose);

            handleBullets(renderer, bullet, nrBullets);
            handleBulletsEnemy(renderer, bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose, nrEnemyGreen, nrEnemyRed, nrEnemyRose);  


            playerTouched = checkCollisionPlayer(player, bulletsEnemyGreen, bulletsEnemyRed, bulletsEnemyRose, nrEnemyGreen, nrEnemyRed, nrEnemyRose);
            levelPassed = checkCollisionEnemy(bullet, nrBullets, green, red, rose, nrEnemyGreen, nrEnemyRed, nrEnemyRose, &nrTotalDeadEnemy);

          
            handleLevelPassed(renderer, levelPassed, color);
        }
        playerDead = handlePlayerTouched(renderer, &playerTouched, &player, heart);
        SDL_RenderPresent(*renderer); // to update the screen
    }

    return 0;
}




void asteroidDestroyer(
    SDL_Texture **homeButton, 
    SDL_Texture **score, 
    SDL_Texture **playerTexture, 
    Bullet *bullets, 
    Heart *hearts, 
    int nrBullets, 
    int playerLives)
{
    // Exemple de destruction des textures
    if (*homeButton) {
        printf("Destroying home button texture\n");
        SDL_DestroyTexture(*homeButton);
        *homeButton = NULL;
    }
    if (*score) {
        printf("Destroying score texture\n");
        SDL_DestroyTexture(*score);
        *score = NULL;
    }
    if (*playerTexture) {
        printf("Destroying player texture\n");
        SDL_DestroyTexture(*playerTexture);
        *playerTexture = NULL;
    }

    for (int i = 0; i < nrBullets; i++) {
        if (bullets[i].texture) {
            printf("Destroying bullet texture %d\n",i);
            SDL_DestroyTexture(bullets[i].texture);
            bullets[i].texture = NULL;
        }
    }

    for (int i = 0; i < playerLives; i++) {
        if (hearts[i].texture) {
            printf("Destroying heart texture %d\n", i);
            SDL_DestroyTexture(hearts[i].texture);
            hearts[i].texture = NULL;
        }
    }
}

void handleHeart(SDL_Renderer **renderer, Heart *heart, int playerLives)
{
     for (int i=0; i<playerLives; i++)
            if (heart[i].active)
                SDL_RenderCopy(*renderer, heart[i].texture, NULL, &heart[i].rect);
    
}

void handleBullets(SDL_Renderer **renderer, Bullet *bullet, int nrBullets)
{
    for (int i =0; i<nrBullets; i++)
    {
        if (bullet[i].active)
        {
            if (bullet[i].rect.y > 30)
            {
                bullet[i].rect.y -=4;
                SDL_RenderCopy(*renderer, bullet[i].texture, NULL, &bullet[i].rect);
            }
            else 
                bullet[i].active = 0;
        }
    
    }
}


int checkCollisionEnemy(
    Bullet *bullets, 
    int nrBullets,
    enemyGreen *green, 
    enemyRed *red, 
    enemyRose *rose, 
    int nrEnemyGreen, 
    int nrEnemyRed, 
    int nrEnemyRose,
    int *nrTotalDeadEnemy)


{
    

    for (int i = 0; i < nrBullets; i++)
    {
        if (bullets[i].active)
        {
            for (int j = 0; j < nrEnemyGreen; j++)
            {
                if (green[j].lives > 0)
                {
                    if (SDL_HasIntersection(&bullets[i].rect, &green[j].rect))
                    {
                        green[j].lives--;
                        bullets[i].active = 0;
                        if (green[j].lives == 0)
                        {
                            *nrTotalDeadEnemy+=1;
                        }
                    }
                }
            }
            for (int j = 0; j < nrEnemyRed; j++)
            {
                if (red[j].lives > 0)
                {
                    if (SDL_HasIntersection(&bullets[i].rect, &red[j].rect))
                    {
                        red[j].lives--;
                        bullets[i].active = 0;
                        if (red[j].lives == 0)
                        {
                            *nrTotalDeadEnemy+=1;
                        }
                    }
                }
            }
            for (int j = 0; j < nrEnemyRose; j++)
            {
                if (rose[j].lives > 0)
                {
                    if (SDL_HasIntersection(&bullets[i].rect, &rose[j].rect))
                    {
                        rose[j].lives--;
                        bullets[i].active = 0;
                        if (rose[j].lives == 0)
                        {
                            *nrTotalDeadEnemy+=1;
                        }
                    }
                }
            }
        }
    }
    int totalEnemy = nrEnemyGreen+nrEnemyRed+nrEnemyRose;

    if ( *nrTotalDeadEnemy == totalEnemy)
    {
        printf("All enemy destroyed\n");
        printf("Level Passed !!! go next\n");
        return 1;
    }
    else 
        return 0;
}


int checkCollisionPlayer(
    Player player, 
    BulletEnemy *bulletsEnemyGreen, 
    BulletEnemy *bulletsEnemyRed, 
    BulletEnemy *bulletsEnemyRose, 
    int nrEnemyGreen, int nrEnemyRed, int nrEnemyRose)
{
    for (int i = 0; i < nrEnemyGreen; i++)
    {
        if (SDL_HasIntersection(&player.rect, &bulletsEnemyGreen[i].rect))
        {
            printf("Player touched by green enemy bullet %d\n", i);
            bulletsEnemyGreen[i].active = 0;
            bulletsEnemyGreen[i].rect.y = HEIGHT + 200; // fix bug
            printf("Bulle enemy avtive status : %d (should not be active)\n", bulletsEnemyGreen[i].active);
            SDL_Delay(10);
            return 1;
        }
    }
    for (int i = 0; i < nrEnemyRed; i++)
    {
        if (SDL_HasIntersection(&player.rect, &bulletsEnemyRed[i].rect))
        {
            bulletsEnemyRed[i].active = 0;
            bulletsEnemyRed[i].rect.y = HEIGHT + 200; // fix bug
            printf("Player touched by red enemy bullet\n");
            return 1;
        }
    }
    for (int i = 0; i < nrEnemyRose; i++)
    {
        if (SDL_HasIntersection(&player.rect, &bulletsEnemyRose[i].rect))
        {
            bulletsEnemyRose[i].active = 0;
            bulletsEnemyRose[i].rect.y = HEIGHT + 200; // fix bug
            printf("Player touched by rose enemy bullet\n");
            return 1;
        }
    }
    return 0;
}


int handlePlayerTouched(SDL_Renderer **renderer, int *playerTouched, Player *player, Heart *heart)
{

    if (player->lives == 0)
    {
        printf("Game Over\n");
        SDL_Color color = COLOR_COSMIC_PINK;
        SDL_Texture *gameOverTxt = createTextTexture(renderer, PATH_PREMIER, 50, "Game Over", color);
        SDL_Rect gameOverRect = {WIDTH/2 - 100, HEIGHT/2 - 50, 200, 100};
        SDL_RenderCopy(*renderer, gameOverTxt, NULL, &gameOverRect);
        return 1;

    }
    if (*playerTouched)
    {
        *playerTouched =0;

        player->lives -=1;
        printf("Player lives : %d\n", player->lives);
        if (player->lives == 0)
        {
            printf("Game Over\n");
            SDL_Color color = COLOR_COSMIC_PINK;
            SDL_Texture *gameOverTxt = createTextTexture(renderer, PATH_PREMIER, 50, "Game Over", color);
            SDL_Rect gameOverRect = {WIDTH/2 - 100, HEIGHT/2 - 50, 200, 100};
            SDL_RenderCopy(*renderer, gameOverTxt, NULL, &gameOverRect);
            return 1;
         
        }
        else
        {
            for (int i = 0; i < player->lives; i++)
            {
                heart[i].active = 1;
            }
        }
    }
    return 0;
}

void handleLevelPassed(SDL_Renderer **renderer, int levelPassed, SDL_Color color)
{
    if (levelPassed)
            {
                SDL_Texture *lvlPassedTxt = createTextTexture(renderer, PATH_PREMIER, 50, "Level Passed", color);
                SDL_Rect lvlPassedRect = {WIDTH/2 - 100, HEIGHT/2 - 50, 200, 100};
                SDL_RenderCopy(*renderer, lvlPassedTxt, NULL, &lvlPassedRect);
            }
}