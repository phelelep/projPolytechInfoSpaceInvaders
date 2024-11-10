#include <stdio.h>
#include <SDL2/SDL.h>   

const int WIDTH = 309, HEIGHT = 343;


int main(int argc, char *argv[])
{
    printf("main void");

    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow ("Hello THere" SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


    if (NULL == window)
        printf("Could not create the window");

    SDL_Event windowEvent;

    while(true)
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

    return EXIT_SUCCESS;


} 