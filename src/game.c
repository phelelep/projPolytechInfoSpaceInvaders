#include <stdio.h>
#include "tools.h"
#include "game.h"

int gameStarted(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state)
{   
    
    // home button
    SDL_Color color = COLOR_PLANETARY_BLUE;
    SDL_Texture *score = createTextTexture(renderer, PATH_PREMIER, 50, "Score", color);

    // home button
    SDL_Texture *homeButton= createTexture(window, renderer, PATH_HOME);    
    
    
    // player
    int playerLives = 2;
    SDL_Texture *playerTexture = createTexture(window, renderer, PATH_PLAYER);

    //enemy
    int nrEnemyGreen = 8;
    int nrEnemyRed = 5;
    int nrEnemyRose = 4;
    int indexEnemyTouched= -1;
    SDL_Texture *enemyGreenTextures [nrEnemyGreen];
    SDL_Texture *enemyRedTextures [nrEnemyRed];
    SDL_Texture *enemyRoseTextures [nrEnemyRose];
    int enemyGreenLives[nrEnemyGreen];
    int enemyRedLives[nrEnemyRed];
    int enemyRoseLives[nrEnemyRose];



    createEnemyTextures(window, renderer, 
                enemyGreenTextures, enemyRedTextures, enemyRoseTextures, 
                enemyGreenLives, enemyRedLives, enemyRoseLives,
                nrEnemyGreen, nrEnemyRed, nrEnemyRose);


    /// --- RECTS --- ///
   // SDL_Rect homeColorButtonRect = {20, 20 , 50, 50};
    SDL_Rect scoreRect = {WIDTH - 150, 20, 70, 25};
    SDL_Rect homeButtonRect = {20, 20 , 50, 50}; // x posiiton départ ,y ,width,hight 
    SDL_Rect playerRect = {WIDTH/2 - 50, HEIGHT - 50, 40, 35}; // x position, y position, width, height
 
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
                printf("Destroying textures\n");  
                SDL_DestroyTexture(homeButton);
                SDL_DestroyTexture(playerTexture);
                SDL_DestroyTexture(score);
                destroyEnemyTextures(enemyGreenTextures, enemyRedTextures, enemyRoseTextures, nrEnemyGreen, nrEnemyRed, nrEnemyRose);

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
                    printf("Destroying textures\n");  
                    SDL_DestroyTexture(homeButton);
                    SDL_DestroyTexture(playerTexture);
                    SDL_DestroyTexture(score);
                    destroyEnemyTextures(enemyGreenTextures, enemyRedTextures, enemyRoseTextures, nrEnemyGreen, nrEnemyRed, nrEnemyRose);

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
                        if (playerRect.x > 0) 
                            playerRect.x -= 14; 
                        break;
                    case SDLK_RIGHT:
                        if (playerRect.x < (WIDTH - playerRect.w))
                            playerRect.x += 14;
                        break;
                }
            }
        }
       
        SDL_Delay(20); 
        
       if (enemyPosition >=15)
       {
        enemyDirection = -1; // direction opposé
        printf("1-enemyDirection : %d\n", enemyDirection);
       }
       else if (enemyPosition <= -15)
       {
         enemyDirection  =1;
         printf("2-enemyDirection : %d\n", enemyDirection);
       }
        
        enemyPosition += enemyDirection*0.35;
        printf("EnemyPositon : %f\n", enemyPosition);
       
         // Clear the renderer and redraw everything
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255); // Set to black
        SDL_RenderClear(*renderer);

        SDL_RenderCopy(*renderer, homeButton, NULL, &homeButtonRect);
        SDL_RenderCopy(*renderer, score, NULL, &scoreRect);
        SDL_RenderCopy(*renderer, playerTexture, NULL, &playerRect);
        
        handleEnemy(window, renderer,
                    enemyGreenTextures, enemyRedTextures, enemyRoseTextures,
                    enemyGreenLives, enemyRedLives, enemyRoseLives,
                    nrEnemyGreen, nrEnemyRed, nrEnemyRose, indexEnemyTouched,
                    enemyPosition);
        SDL_RenderPresent(*renderer); // to update the screen
    }

    return 0;
}


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
    int nrEnemyRose)
{

    
    for (int i = 0; i < nrEnemyGreen; i++)
    {
        enemyGreenTextures[i] = createTexture(window, renderer, PATH_ENEMY_GREEN);
        enemyGreenLives[i] = 2;
    }
    for (int i = 0; i < nrEnemyRed; i++)
    {
        enemyRedTextures[i] = createTexture(window, renderer, PATH_ENEMY_RED);
        enemyRedLives[i] = 3;
    }
    for (int i = 0; i < nrEnemyRose; i++)
    {
        enemyRoseTextures[i] = createTexture(window, renderer, PATH_ENEMY_ROSE);
        enemyRoseLives[i] = 1;
    }
}

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
    double enemyPosition)
{

    /// --- GREEN ENEMY --- ///
    SDL_Rect enemyGreenRects[nrEnemyGreen];
    SDL_Rect enemyRedRects[nrEnemyRed];
    SDL_Rect enemyRoseRects[nrEnemyRose];
    int nrEnemyGreenLives[nrEnemyGreen];
    int nrEnemyRedLives[nrEnemyRed];
    int nrEnemyRoseLives[nrEnemyRose];
    
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
        enemyGreenRects[i] = tempRect;
        SDL_RenderCopy(*renderer, enemyGreenTextures[i], NULL, &enemyGreenRects[i]);
    }
    for (int i =0 ; i< nrEnemyRed; i++)
    {
        SDL_Rect tempRect2 ={startRed + i*(spacing+80)+ enemyPosition, 200, 80, 50};
        enemyRedRects[i] = tempRect2;
        SDL_RenderCopy(*renderer, enemyRedTextures[i], NULL, &enemyRedRects[i]);
    }
    for (int i =0 ; i< nrEnemyRose; i++)
    {
        SDL_Rect tempRect3 ={startRose + i*(spacing+50)+ enemyPosition, 100, 50, 50};
        enemyRoseRects[i] = tempRect3;
        SDL_RenderCopy(*renderer, enemyRoseTextures[i], NULL, &enemyRoseRects[i]);
    }
}

void destroyEnemyTextures(SDL_Texture **enemyGreenTextures, 
                    SDL_Texture **enemyRedTextures, 
                    SDL_Texture **enemyRoseTextures,
                    int nrEnemyGreen,
                    int nrEnemyRed,
                    int nrEnemyRose)

{
    for (int i = 0; i < nrEnemyGreen; i++) {
        if (enemyGreenTextures[i] != NULL) {
            SDL_DestroyTexture(enemyGreenTextures[i]);
            enemyGreenTextures[i] = NULL;
            printf("enemyGreenTextures[%d] destroyed\n", i);
        }
    }
    for (int i = 0; i < nrEnemyRed; i++) {
        if (enemyRedTextures[i] != NULL) {
            SDL_DestroyTexture(enemyRedTextures[i]);
            enemyRedTextures[i] = NULL;
            printf("enemyRedTextures[%d] destroyed\n", i);
        }
    }
    for (int i = 0; i < nrEnemyRose; i++) {
        if (enemyRedTextures[i] != NULL) {
            SDL_DestroyTexture(enemyRedTextures[i]);
            enemyRedTextures[i] = NULL;
            printf("enemyRoseTextures[%d] destroyed\n", i);
        }
    }
}