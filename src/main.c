#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   

const int WIDTH = 800, HEIGHT = 500;


int main(int argc, char *argv[])
{

    SDL_Init( SDL_INIT_EVERYTHING );
    // window
    SDL_Window *window = SDL_CreateWindow(
        "Space Invaders", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_SHOWN);

    if (NULL == window) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Renderer not created: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // buton
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 - 25, 150, 50};
    unsigned int gameRunning = 0;

    SDL_Event event;
    

    // init butt
    SDL_SetRenderDrawColor (renderer, 0,150,12,255); // fill screen with black color
    SDL_RenderClear(renderer);

    // start button 
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //green
    SDL_RenderFillRect(renderer, &startButton); // asign the button to the var startButton
    SDL_RenderPresent(renderer);

    // game loop
    /*
    1. add logic to ensure that the screen is updated only when necessary
    2. modify button text and colors
    */
    while (1) 
    {
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
            printf("Ferme la game");
            // clean up to be placed in a function
            SDL_DestroyWindow (window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
            //exit(0);  program is closed imediatelly
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
                    gameRunning = 1;
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // to change color game is started
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer); // updates the screen
                }

        }
      }
    }
    SDL_Delay(16); // ~60 FPS to reduce CPU usage


} 