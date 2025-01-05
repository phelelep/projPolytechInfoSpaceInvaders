#include "startWindow.h"
#include <stdio.h>
#include <string.h>


int createLoadPage(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state, User *player1)
{
    TTF_Init(); // for text

    // text for the title
    Draw title;
    title.color =(SDL_Color)COLOR_AURORA_TEAL;
    title.texture =createTextTexture (renderer, FONT_PATH_TITLE,540, "Space Invaders", title.color);
    if (!title.texture) 
    {
        printf("Failed to create title texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }

    // text for design
    Draw design;
    design.color =(SDL_Color) COLOR_STAR_YELLOW;
    design.texture =createTextTexture (renderer, FONT_PATH_DESIGN ,240, "Space Invaders", design.color);
    if (!design.texture) 
    {
        printf("Failed to create design texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }


    // text for the PLAY button 
    Draw playButton;
    playButton.color =(SDL_Color) COLOR_SUPERNOVA;
    playButton.texture =createTextTexture (renderer, FONT_PATH_PLAY,120, "Play", playButton.color);
    if (!playButton.texture) 
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
    //SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 + 160 , 150, 50}; // x posiiton départ ,y ,width,hight  
    title.rect = (SDL_Rect){WIDTH / 2 - titleWidth / 2, HEIGHT / 2 - 330, titleWidth, titleHeight};
    design.rect = (SDL_Rect){WIDTH / 2 - designWidth / 2, HEIGHT / 2 + 260, designWidth, designHeight}; 
    playButton.rect =(SDL_Rect){WIDTH/2 -70, HEIGHT/2 + 160, 140, 45};  




    createScoreBoard(window, renderer, event, state, title, design, playButton, player1);
   
    printf("Destroying textures for text\n");  
    SDL_DestroyTexture(title.texture);
    SDL_DestroyTexture(design.texture);
    SDL_DestroyTexture(playButton.texture);


    return 0;

}

int createScoreBoard(SDL_Window **window, SDL_Renderer **renderer, SDL_Event *event, GameState *state,
                     Draw title, Draw design, Draw playButton, User *player1)
{
    PlayerScore playerScore[100];
    findTopThreeScores(playerScore);
    
    // text for the Scoreboard
    Draw scoreboard;
    scoreboard.color =(SDL_Color) COLOR_PLANETARY_BLUE;
    scoreboard.texture =createTextTexture (renderer, PATH_PREMIER ,340, "Scoreboard", scoreboard.color);
    if (!scoreboard.texture) 
    {
        printf("Failed to create scoreboard texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    Draw score1;
    score1.color =(SDL_Color) COLOR_COSMIC_PINK;
    char score1Text[50];
    sprintf(score1Text, "%s : %d", playerScore[0].name, playerScore[0].score);
    score1.texture =createTextTexture (renderer, PATH_PREMIER ,140, score1Text, score1.color);
    if (!score1.texture) 
    {
        printf("Failed to create first player texture.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    Draw score2;
    score2.color =(SDL_Color) COLOR_COSMIC_PINK;
    char score2Text[50];
    sprintf(score2Text, "%s : %d", playerScore[1].name, playerScore[1].score);
    score2.texture =createTextTexture (renderer, PATH_PREMIER ,140, score2Text, score2.color);
    if (!score2.texture) 
    {
        printf("Failed to create texture for second player.\n");
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    Draw score3;
    score3.color= (SDL_Color) COLOR_COSMIC_PINK;
    char score3Text[50];
    sprintf(score3Text, "%s : %d", playerScore[2].name, playerScore[2].score);
    score3.texture =createTextTexture (renderer, PATH_PREMIER ,140, score3Text, score3.color);
    if (!score3.texture) 
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
    scoreboard.rect =(SDL_Rect) {WIDTH/2- 75, HEIGHT/2 -150 , scoreboardWidth, scoreboardHeight}; // x position, y position, width, height
    score1.rect = (SDL_Rect) {WIDTH/2- 60, HEIGHT/2 -90 , scoreWidth, scoreHeight}; // x position, y position, width, height
    score2.rect = (SDL_Rect) {WIDTH/2- 60, HEIGHT/2 -50 , scoreWidth, scoreHeight}; // x position, y position, width, height
    score3.rect = (SDL_Rect) {WIDTH/2- 60, HEIGHT/2 -10, scoreWidth, scoreHeight}; // x position, y position, width, height
     


  
    handlePlayButton(renderer, event, state, title, design, playButton, scoreboard, score1, score2, score3, player1);

    printf("Destroying textures for scoreboard & score 1 & score 2 & score 3\n");
    SDL_DestroyTexture(scoreboard.texture);
    SDL_DestroyTexture(score1.texture);
    SDL_DestroyTexture(score2.texture);
    SDL_DestroyTexture(score3.texture);


    return 0;
}
/*
By passing the event and state variables by reference, you avoid creating unnecessary copies 
and allow the called function to modify the original variables in the caller function.
*/

void handlePlayButton(SDL_Renderer **renderer, SDL_Event *event, GameState *state,
                      Draw title, Draw design, Draw playButton,
                      Draw scoreboard, Draw score1, Draw score2, Draw score3,
                      User *player1)
{

     /// --- input player name
    
    strcpy(player1->Name, "Type your name");
    player1->color= (SDL_Color) COLOR_MOONLIGHT;
    player1->texture = createTextTexture(renderer, PATH_PREMIER, 50, player1->Name, player1->color);
    player1->rect=(SDL_Rect) {WIDTH/2 - 52, HEIGHT/2 + 115, 100, 30};
    /// ----------------- ///
     
    SDL_Rect startButton = {WIDTH/2 -75, HEIGHT/2 + 160, 150, 50};

    while (*state == LOAD_PAGE)
    {
        while (SDL_PollEvent(event))
        {
            printf("State is in load page\n");
            if (event->type == SDL_QUIT)
            {
                *state = GAME_OVER;
                 /// --- input player name
                printf("Destroying textures for name input\n");
                SDL_DestroyTexture(player1->texture);
                return;
            }
            else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) 
            { 
                printf("In the event mouse button down\n");
                int mouseX= event->button.x; // horizontal plan
                int mouseY= event->button.y; // vertical plan

                //check if the mouse was pressed inside the button 
                if (mouseX>= startButton.x && mouseX <=(startButton.x + startButton.w) && 
                    mouseY>= startButton.y && mouseY <=(startButton.y)+ startButton.h)
                {  
                    printf("Button play clicked\n");
                    
                    *state = GAME_STARTED;
                    return;
                    
                }

            }
            else if (event->type == SDL_TEXTINPUT)
            {
                // clean name avant input
                printf("Text input\n");
                if (strcmp(player1->Name, "Type your name") == 0)
                    player1->Name[0] = '\0';
            

                if (strlen(player1->Name) < 20 - 1)
                {
                    strcat(player1->Name, event->text.text); //concatener 2 chainnes de char
                    printf("Player name : %s\n", player1->Name);
                    player1->texture = createTextTexture(renderer, PATH_PREMIER, 50, player1->Name, player1->color);
                    player1->rect.w = strlen(player1->Name) * 10; // for each char lenght multiplies by 10
                }
            }
            else if (event->type == SDL_KEYDOWN)
            {
                printf("State is in key down\n");
                if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(player1->Name) > 0)
                {
                    player1->Name[strlen(player1->Name) - 1] = '\0';
                    printf("Player name : %s\n", player1->Name);
                    player1->texture = createTextTexture(renderer, PATH_PREMIER, 50, player1->Name, player1->color);
                    player1->rect.w = strlen(player1->Name)*10;
                }
            }
            
        }
        
        // init screen
        SDL_SetRenderDrawColor (*renderer, 18,15,109,255); // fill screen with color
        SDL_RenderClear(*renderer);

        SDL_SetRenderDrawColor(*renderer, 32, 130, 100, 255); 
        SDL_RenderFillRect(*renderer, &startButton); // asign the button to the var startButton

        SDL_RenderCopy(*renderer, title.texture, NULL, &title.rect);
        SDL_RenderCopy(*renderer, design.texture, NULL, &design.rect);
        SDL_RenderCopy(*renderer, playButton.texture, NULL, &playButton.rect);

       

        SDL_RenderCopy(*renderer, scoreboard.texture, NULL, &scoreboard.rect);
        SDL_RenderCopy(*renderer, score1.texture, NULL, &score1.rect);
        SDL_RenderCopy(*renderer, score2.texture, NULL, &score2.rect);
        SDL_RenderCopy(*renderer, score3.texture, NULL, &score3.rect);

        SDL_RenderCopy(*renderer, player1->texture, NULL, &player1->rect);
        SDL_RenderPresent(*renderer); // to update the screen // affichage de merde
        


        SDL_Delay(100); // ~FPS every 100ms listens to the event
    }

    
}
////When accessing elements in an array of structs, you use the dot operator (.)

void findTopThreeScores(PlayerScore *playerScore)
{
   char filepath[300] = "/Users/phelelep/Desktop/ProgProjGit/projPolytechInfoSpaceInvaders/score.txt";
   
   FILE *file = fopen(filepath, "r");
   
   if(!file)
   {
         printf("!!! Failed to open score date file !!!\n");
         return;
   }
   else
         printf("!!! Score date file opened !!!\n"); 

  
    int count = 0;

    while (fscanf(file, "Name: %19[^,], Score: %d;\n", playerScore[count].name, &playerScore[count].score) == 2)
    {
        count++;
    }

    printf("Found %d scores\n", count);

    fclose(file);

    // Trier les scores par ordre decroissante
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (playerScore[i].score < playerScore[j].score)
            {
                PlayerScore temp = playerScore[i];
                playerScore[i] = playerScore[j];
                playerScore[j] = temp;
            }
        }
    }

      
    for (int i = 0; i < 3 && i < count; i++)
    {
        printf("--- Top %d: %s with score %d\n", i + 1, playerScore[i].name, playerScore[i].score);
    }

}