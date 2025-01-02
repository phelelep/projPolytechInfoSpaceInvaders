#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h> // for text 

// my includes
#include "startWindow.h"
#include "player.h"
#include "tools.h"
#include "game.h"

int main(int argc, char *argv[])
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Gestion de l'erreur d'initialisation SDL
        return EXIT_FAILURE;
    }
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
   
    // game loop
    /*todo
    1. add logic to ensure that the screen is updated only when necessary
    2. modify button text and colors
    */
    SDL_Event event;

    GameState state = LOAD_PAGE;


    while (1) 
    {
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
            state = GAME_OVER;
        }
        switch (state)
        {
            case LOAD_PAGE :
                createLoadPage(&window, &renderer, &event, &state);
                break;
            case GAME_STARTED :
                gameStarted(&window, &renderer, &event, &state);
                break;
            case GAME_OVER:
                cleanup(&window, &renderer);
                break; 
        }
      }
    }
    SDL_Delay(100); // ~FPS every 100ms listens to the event

} 