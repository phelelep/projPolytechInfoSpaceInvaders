#include "startWindow.h"
#include "tools.h"


void createLoadPage(
    SDL_Window *window, 
    SDL_Renderer *renderer, 
    SDL_Texture *textTexture4Title,
    SDL_Texture *textTexture4Design,
    SDL_Texture *textTexture4Play)
{
    TTF_Init(); // for text

    // text for the title
    SDL_Color color = COLOR_AURORA_TEAL;
    textTexture4Title =createTextTexture (renderer, FONT_PATH_TITLE,540, "Space Invaders", color);
    if (!textTexture4Title) 
    {
        printf("Failed to create title texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    // text for design
    SDL_Color color2 = COLOR_STAR_YELLOW;
    textTexture4Design =createTextTexture (renderer, FONT_PATH_DESIGN ,240, "Space Invaders", color2);
    if (!textTexture4Design) 
    {
        printf("Failed to create design texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    // text for the PLAY button 
    SDL_Color color3 = COLOR_SUPERNOVA;
    textTexture4Play =createTextTexture (renderer, FONT_PATH_PLAY,120, "Play", color3);
    if (!textTexture4Play) 
    {
        printf("Failed to create play texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    int titleWidth = 500;
    int titleHeight = 150;
    int designWidth = 750;
    int designHeight = 70;

    /// Rects ---  is used to define the position and size of a rectangular area on the screen
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 + 140 , 150, 50}; // x posiiton départ ,y ,width,hight  
    SDL_Rect textRectTitle = {WIDTH / 2 - titleWidth / 2, HEIGHT / 2 - 330, titleWidth, titleHeight};
    SDL_Rect textRectDesign = {WIDTH / 2 - designWidth / 2, HEIGHT / 2 + 260, designWidth, designHeight}; 
    SDL_Rect textRectPlay = {WIDTH/2 -70, HEIGHT/2 + 140, 140, 45};  

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

}

void createScoreBoard(
    SDL_Window *window,
    SDL_Renderer *renderer, 
    SDL_Texture *scoreboard, 
    SDL_Texture *score1, 
    SDL_Texture *score2, 
    SDL_Texture *score3
    )
{
    // text for the Scoreboard
    SDL_Color color = COLOR_PLANETARY_BLUE;
    scoreboard =createTextTexture (renderer, PATH_PREMIER ,340, "Scoreboard", color);
    if (!scoreboard) 
    {
        printf("Failed to create scoreboard texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color = COLOR_COSMIC_PINK;
    score1 =createTextTexture (renderer, PATH_PREMIER ,140, "First player", color);
    if (!score1) 
    {
        printf("Failed to create first player texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color = COLOR_COSMIC_PINK;
    score2 =createTextTexture (renderer, PATH_PREMIER ,140, "Second player", color);
    if (!score2) 
    {
        printf("Failed to create texture for second player.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color = COLOR_COSMIC_PINK;
    score3 =createTextTexture (renderer, PATH_PREMIER ,140, "Third player", color);
    if (!score3) 
    {
        printf("Failed to create texture for third player.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

}