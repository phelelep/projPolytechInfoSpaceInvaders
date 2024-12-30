#include "startWindow.h"
#include <stdio.h>


int createLoadPage(SDL_Window *window, SDL_Renderer *renderer)
{
    TTF_Init(); // for text

    // text for the title
    SDL_Color color = COLOR_AURORA_TEAL;
    SDL_Texture *textTexture4Title =createTextTexture (renderer, FONT_PATH_TITLE,540, "Space Invaders", color);
    if (!textTexture4Title) 
    {
        printf("Failed to create title texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    // text for design
    SDL_Color color2 = COLOR_STAR_YELLOW;
    SDL_Texture * textTexture4Design =createTextTexture (renderer, FONT_PATH_DESIGN ,240, "Space Invaders", color2);
    if (!textTexture4Design) 
    {
        printf("Failed to create design texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    // text for the PLAY button 
    SDL_Color color3 = COLOR_SUPERNOVA;
    SDL_Texture * textTexture4Play =createTextTexture (renderer, FONT_PATH_PLAY,120, "Play", color3);
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
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 + 160 , 150, 50}; // x posiiton départ ,y ,width,hight  
    SDL_Rect textRectTitle = {WIDTH / 2 - titleWidth / 2, HEIGHT / 2 - 330, titleWidth, titleHeight};
    SDL_Rect textRectDesign = {WIDTH / 2 - designWidth / 2, HEIGHT / 2 + 260, designWidth, designHeight}; 
    SDL_Rect textRectPlay = {WIDTH/2 -70, HEIGHT/2 + 160, 140, 45};  

    // init screen
    SDL_SetRenderDrawColor (renderer, 18,15,109,255); // fill screen with color
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

    /*
    renderer is update textures no longer needed - free memory
    */
    printf("Destroying textures for scoreboard\n");  
    SDL_DestroyTexture(textTexture4Title);
    SDL_DestroyTexture(textTexture4Design);
    SDL_DestroyTexture(textTexture4Play);


    createScoreBoard(window, renderer);

}

int createScoreBoard(SDL_Window *window, SDL_Renderer *renderer)
{
    // text for the Scoreboard
    SDL_Color color = COLOR_PLANETARY_BLUE;
    SDL_Texture * scoreboard =createTextTexture (renderer, PATH_PREMIER ,340, "Scoreboard", color);
    if (!scoreboard) 
    {
        printf("Failed to create scoreboard texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color2 = COLOR_COSMIC_PINK;
    SDL_Texture * score1 =createTextTexture (renderer, PATH_PREMIER ,140, "First player", color2);
    if (!score1) 
    {
        printf("Failed to create first player texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color3 = COLOR_COSMIC_PINK;
    SDL_Texture * score2 =createTextTexture (renderer, PATH_PREMIER ,140, "Second player", color3);
    if (!score2) 
    {
        printf("Failed to create texture for second player.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Color color4 = COLOR_COSMIC_PINK;
    SDL_Texture * score3 =createTextTexture (renderer, PATH_PREMIER ,140, "Third player", color4);
    if (!score3) 
    {
        printf("Failed to create texture for third player.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    int scoreboardWidth = 150;
    int scoreboardHeight = 50;
    int scoreWidth = 120;
    int scoreHeight = 40;
    /// Rects --- is used to define the position and size of a rectangular area on the screen
    SDL_Rect scoreboardrect = {WIDTH/2- 75, HEIGHT/2 -150 , scoreboardWidth, scoreboardHeight}; // x position, y position, width, height
    SDL_Rect score1rect =     {WIDTH/2- 60, HEIGHT/2 -90 , scoreWidth, scoreHeight}; // x position, y position, width, height
    SDL_Rect score2rect =     {WIDTH/2- 60, HEIGHT/2 -50 , scoreWidth, scoreHeight}; // x position, y position, width, height
    SDL_Rect score3rect =     {WIDTH/2- 60, HEIGHT/2 -10, scoreWidth, scoreHeight}; // x position, y position, width, height
   
    //TODO put input player name
     /*
    This function renders the SDL_Texture (created from text surface) onto the screen at the position and size specified by the SDL_Rect
    */
    SDL_RenderCopy(renderer, scoreboard, NULL, &scoreboardrect);
    SDL_RenderCopy(renderer, score1, NULL, &score1rect);
    SDL_RenderCopy(renderer, score2, NULL, &score2rect);
    SDL_RenderCopy(renderer, score3, NULL, &score3rect);    



    SDL_RenderPresent(renderer); // to update the screen



    printf("Destroying textures for scoreboard\n");
    SDL_DestroyTexture(scoreboard);
    SDL_DestroyTexture(score1);
    SDL_DestroyTexture(score2);
    SDL_DestroyTexture(score3);
}
/*
Yes, you are correct. By passing the event and state variables by reference, you avoid creating unnecessary copies 
and allow the called function to modify the original variables in the caller function.
*/

int handleLoadPage(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event, GameState *state)
{
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 + 160, 150, 50};


    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) 
        { 
            int mouseX= event->button.x; // horizontal plan
            int mouseY= event->button.y; // vertical plan

            //check if the mouse was pressed inside the button 
            if (mouseX>= startButton.x && mouseX <=(startButton.x + startButton.w) && 
                mouseY>= startButton.y && mouseY <=(startButton.y)+ startButton.h)
                {  
                    printf("Button clicked\n");
                  
                    *state = GAME_STARTED;
                    //SDL_RenderClear(renderer);
                    //SDL_RenderPresent(renderer); // updates the screen
                   
                }

        }
}