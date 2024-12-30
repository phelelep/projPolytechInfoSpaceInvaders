#include "game.h"
#include <stdio.h>
#include "tools.h"

int gameStarted(SDL_Window *window, SDL_Renderer *renderer)
{   
    
    SDL_Color color = COLOR_STAR_YELLOW;
    SDL_Texture *homeButtonText= createTextTexture(renderer, FONT_PATH_PLAY, 20, "Home", color);    
    if (!homeButtonText) 
    {
        printf("Failed to create Home Button !\n");
        cleanup(window, renderer);
    }

    SDL_Rect homeButtonRect = {20, 20 , 50, 50}; // x posiiton départ ,y ,width,hight 
    SDL_Rect startButton  = {20, 20 , 50, 50}; 
    

   

    // window color noir 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // to change color game is started to noir
    SDL_RenderClear(renderer);
    


    // start button 
    SDL_SetRenderDrawColor(renderer, 0, 200, 240, 255);
    SDL_RenderFillRect(renderer, &startButton); // asign the button to the var startButton

    


    // to display only the button text
    SDL_RenderCopy(renderer, homeButtonText, NULL, &homeButtonRect);

    SDL_RenderPresent(renderer); // to update the screen

    printf("Destroying textures for scoreboard\n");  
    SDL_DestroyTexture(homeButtonText);
}