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
    int nrBullets = 9;
    int indexBullet = 0;
    Bullet bullet[nrBullets];
    for (int i =0; i<nrBullets; i++)
    {
        bullet[i].texture = createTexture(window, renderer, PATH_BULLET);
        bullet[i].rect.w = 15;
        bullet[i].rect.h = 15;
        bullet[i].active = 0;
    }
 


    //enemy
    int nrEnemyGreen = 8;
    int nrEnemyRed = 5;
    int nrEnemyRose = 4;
    int indexEnemyTouched= -1;

    enemyGreen green[nrEnemyGreen];
    enemyRed red[nrEnemyRed];
    enemyRose rose[nrEnemyRose];



    createEnemyTextures(window, renderer, 
                green, red, rose,
                nrEnemyGreen, nrEnemyRed, nrEnemyRose);


    /// --- RECTS --- ///
   // SDL_Rect homeColorButtonRect = {20, 20 , 50, 50};
    SDL_Rect scoreRect = {WIDTH - 150, 20, 70, 25};
    SDL_Rect homeButtonRect = {20, 20 , 50, 50}; // x posiiton départ ,y ,width,hight 

    double enemyPosition = 0;
    int enemyDirection =1;
    while (*state == GAME_STARTED) 
    {
        while (SDL_PollEvent(event)) 
        {
            if (event->type == SDL_QUIT)  //quited
            {
                *state = GAME_OVER;
                /// --- CLEANUP --- ///
                asteroidDestroyer(&homeButton, &score, &player.texture, bullet, heart, nrBullets, player.lives);
                destroyEnemyTextures(green, red, rose, nrEnemyGreen, nrEnemyRed, nrEnemyRose);
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
                    destroyEnemyTextures(green, red, rose, nrEnemyGreen, nrEnemyRed, nrEnemyRose);
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
       
        handleBullets(renderer, bullet, nrBullets);

       // checkCollision(bullet, nrBullets, enemyGreenRect, enemyGreenLives, nrEnemyGreen);

        handleEnemy(window, renderer,
                    green, red, rose,
                    nrEnemyGreen, nrEnemyRed, nrEnemyRose, indexEnemyTouched,
                    enemyPosition);
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