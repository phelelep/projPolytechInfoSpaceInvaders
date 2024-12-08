#include <stdio.h>
#include <stdlib.h>  // for exit failure
#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h> // for text 
#include "tools.h"
#include "tools.c"

#define FONT_PATH_TITLE  "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Electron.ttf"
#define FONT_PATH_DESIGN "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Invaders.ttf"
#define FONT_PATH_PLAY   "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Electron.ttf"

#define COLOR_WHITE {255, 255, 255, 255}  // Bright White (Stars)
#define COLOR_STAR_YELLOW {255, 223, 0, 255}  // Star Yellow
#define COLOR_SUPERNOVA {255, 87, 51, 255}  // Supernova Orange-Red
#define COLOR_NEBULA_PURPLE {138, 43, 226, 255}  // Nebula Purple
#define COLOR_DEEP_SPACE {25, 25, 112, 255}  // Deep Space Blue
#define COLOR_GALACTIC_GREEN {60, 179, 113, 255}  // Galactic Green
#define COLOR_PLANETARY_BLUE {70, 130, 180, 255}  // Planetary Blue
#define COLOR_METEORITE_GRAY {112, 128, 144, 255}  // Meteorite Gray
#define COLOR_MOONLIGHT {192, 192, 192, 255}  // Moonlight Silver
#define COLOR_COSMIC_PINK {255, 105, 180, 255}  // Cosmic Pink
#define COLOR_BLACK_HOLE {0, 0, 0, 255}  // Absolute Black
#define COLOR_AURORA_TEAL {64, 224, 208, 255}  // Aurora Teal
#define COLOR_SOLAR_FLARE {255, 140, 0, 255}  // Solar Flare Orange
#define COLOR_STARDUST {218, 165, 32, 255}  // Stardust Gold
#define COLOR_ECLIPSE {72, 61, 139, 255}  // Eclipse Dark Blue



const int WIDTH = 960, HEIGHT = 720;


void cleanup(SDL_Window *window, SDL_Renderer *renderer) 
{
    printf("Cleaning up resources...\n");
    
    // Destroy window and renderer
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    // Quit SDL_ttf and SDL
    TTF_Quit(); 
    SDL_Quit();
}

void cleanupAll(SDL_Window *window, SDL_Renderer *renderer)
{

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

    // text for the title
    SDL_Color color = COLOR_WHITE;
    SDL_Texture * textTexture4Title =createTextTexture (renderer, FONT_PATH_TITLE,540, "Space Invaders", color);
    if (!textTexture4Title) {
        printf("Failed to create title texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    // text for design
    SDL_Color color2 = COLOR_STAR_YELLOW;
    SDL_Texture * textTexture4Design =createTextTexture (renderer, FONT_PATH_DESIGN ,240, "Space Invaders", color2);
    if (!textTexture4Design) {
        printf("Failed to create design texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    // text for the PLAY button 
    SDL_Color color3 = COLOR_SUPERNOVA;
    SDL_Texture * textTexture4Play =createTextTexture (renderer, FONT_PATH_PLAY,120, "Play", color3);
    if (!textTexture4Play) {
        printf("Failed to create play texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    int titleWidth = 400;
    int titleHeight = 200;
    int designWidth = 300;
    int designHeight = 100;

    /// Rects ---  is used to define the position and size of a rectangular area on the screen
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 - 25, 150, 50}; // x posiiton départ ,y ,width,hight  
    SDL_Rect textRectTitle = {WIDTH / 2 - titleWidth / 2, HEIGHT / 2 - 200, titleWidth, titleHeight};
    SDL_Rect textRectDesign = {WIDTH / 2 - designWidth / 2, HEIGHT / 2 + 100, designWidth, designHeight}; 
    SDL_Rect textRectPlay = {WIDTH/2 -70, HEIGHT/2 - 20, 140, 45};  

    // init screen
    SDL_SetRenderDrawColor (renderer, 18,15,109,255); // fill screen with black color
    SDL_RenderClear(renderer);

    // start button 
    SDL_SetRenderDrawColor(renderer, 32, 130, 100, 255); 
    SDL_RenderFillRect(renderer, &startButton); // asign the button to the var startButton
    

    /*
    This function renders the SDL_Texture (created from text surface) onto the screen at the position and size specified by the SDL_Rect
    */
    SDL_RenderCopy(renderer, textTexture4Title, NULL, &textRectTitle);
    SDL_RenderCopy(renderer, textTexture4Design, NULL, &textRectDesign);
    SDL_RenderCopy(renderer, textTexture4Play, NULL, &textRectPlay);



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
                    SDL_DestroyTexture(textTexture4Title);
                    SDL_DestroyTexture(textTexture4Design);
                    SDL_DestroyTexture(textTexture4Play);
                }

        }
      }
    }
    SDL_Delay(45); // ~25 FPS to reduce CPU usage


} 