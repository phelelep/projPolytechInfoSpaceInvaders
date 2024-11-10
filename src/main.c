#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   

const int WIDTH = 800, HEIGHT = 500;


int main(int argc, char *argv[])
{

    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow("Soace Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


    if (NULL == window) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Event windowEvent;

    while(1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
    }
    SDL_DestroyWindow (window);
    SDL_Quit();
    exit(0); 
    return EXIT_SUCCESS;


} 