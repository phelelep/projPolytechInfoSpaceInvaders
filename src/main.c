#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h> // for text 


const int WIDTH = 960, HEIGHT = 720;


void cleanup(SDL_Window *window, SDL_Renderer *renderer) 
{
    printf("Ferme la game");
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit(); 
    SDL_Quit();
}



int main(int argc, char *argv[])
{
    //init
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init(); // for text

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
    // font & textSurface & textTexture
    TTF_Font *font = TTF_OpenFont("C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Halo_Dek.ttf", 140);
    SDL_Color textColor = { 255, 255, 255,255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font,"Play", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface (textSurface);

    if (!font || !textSurface || !textTexture)
    {
        printf("Failed in creating text (font, texture or surface ... ): %s\n", TTF_GetError());
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    // buton
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 - 25, 150, 50};
    SDL_Rect textRect = {WIDTH/2 -70, HEIGHT/2 - 20, 140, 45};    // x posiiton départ ,y ,width,hight  
    

    // init screen
    SDL_SetRenderDrawColor (renderer, 18,15,109,255); // fill screen with black color
    SDL_RenderClear(renderer);

    // start button 
    SDL_SetRenderDrawColor(renderer, 32, 130, 100, 255); 
    SDL_RenderFillRect(renderer, &startButton); // asign the button to the var startButton
    

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


    SDL_RenderPresent(renderer); // to update the screen

    // game loop
    /*todo
    1. add logic to ensure that the screen is updated only when necessary
    2. modify button text and colors
    */

    SDL_Event event;
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
                    //gameRunning = 1;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // to change color game is started
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer); // updates the screen
                }

        }
      }
    }
    SDL_Delay(45); // ~25 FPS to reduce CPU usage


} 