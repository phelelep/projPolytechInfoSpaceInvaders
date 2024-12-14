#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h> // for text 
//#include "tools.h"

#include "startWindow.c"
#include "player.c"


void cleanup(SDL_Window *window, SDL_Renderer *renderer) 
{
    printf("Cleaning up resources...\n");
    
    // Destroy window and renderer
    if (window)
    {
        SDL_DestroyWindow(window);
        printf("Window destroyed\n");
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        printf("Renderer destroyed\n");
    }
    // Quit SDL_ttf and SDL
    TTF_Quit(); 
    SDL_Quit();
}



int main(int argc, char *argv[])
{
    SDL_Init( SDL_INIT_EVERYTHING);
    //init
    SDL_Window *window = SDL_CreateWindow(
        "Space Invaders", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_SHOWN);
    if (window==NULL) 
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer  = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Renderer not created: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture *textTexture4Title  = NULL;
    SDL_Texture *textTexture4Design = NULL;
    SDL_Texture *textTexture4Play   = NULL;
    SDL_Texture *playerTexture      = NULL;
    SDL_Texture *enemyTexture       = NULL;
    //SDL_Texture *bulletTexture      = NULL;
    //SDL_Texture *backgroundTexture  = NULL;
    //SDL_Texture *explosionTexture   = NULL;
    //SDL_Texture *obstacleTexture    = NULL;
    //SDL_Texture *gameOverTexture    = NULL;
    /*
    Pass pointer by value will not modify the value in the main function -  all changes in start function will be lost
    */
    createLoadPage(window, renderer, textTexture4Title, textTexture4Design, textTexture4Play);
    //createPlayer(window, renderer, playerTexture);
   



    // game loop
    /*todo
    1. add logic to ensure that the screen is updated only when necessary
    2. modify button text and colors
    */
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 - 25, 150, 50};
    SDL_Event event;
    int gameRunning = 0;
    while (1) 
    {
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
            cleanup(window, renderer);
            return EXIT_SUCCESS;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
        {
            int mouseX= event.button.x; // horizontal plan
            int mouseY= event.button.y; // vertical plan

            //check if the mouse was pressed inside the button 
            if (mouseX>= startButton.x && mouseX <=(startButton.x + startButton.w) && 
                mouseY>= startButton.y && mouseY <=(startButton.y)+ startButton.h)
                {   
                    printf("Button clicked\n");
                    gameRunning = 1;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // to change color game is started
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer); // updates the screen
                    SDL_DestroyTexture(textTexture4Title);
                    SDL_DestroyTexture(textTexture4Design);
                    SDL_DestroyTexture(textTexture4Play);
                }

        }
        if (gameRunning)
        {

        }
      }
    }
    SDL_Delay(45); // ~25 FPS to reduce CPU usage

} 