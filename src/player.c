#include "player.h"
#include "tools.h"


void handleHeart(SDL_Renderer **renderer, Heart *heart, int playerLives)
{
     for (int i=0; i<playerLives; i++)
            if (heart[i].active)
                SDL_RenderCopy(*renderer, heart[i].texture, NULL, &heart[i].rect);
    
}


void handleBullets(SDL_Renderer **renderer, Bullet *bullet, int nrBullets)
{
    for (int i =0; i<nrBullets; i++)
    {
        if (bullet[i].active)
        {
            if (bullet[i].rect.y > 30)
            {
                bullet[i].rect.y -=4;
                SDL_RenderCopy(*renderer, bullet[i].texture, NULL, &bullet[i].rect);
            }
            else 
                bullet[i].active = 0;
        }
    
    }
}

int handlePlayerTouched(SDL_Renderer **renderer, int *playerTouched, Player *player, Heart *heart)
{

    if (player->lives == 0)
    {
        printf("Game Over\n");
        SDL_Color color = COLOR_COSMIC_PINK;
        SDL_Texture *gameOverTxt = createTextTexture(renderer, PATH_PREMIER, 50, "Game Over", color);
        SDL_Rect gameOverRect = {WIDTH/2 - 100, HEIGHT/2 - 50, 200, 100};
        SDL_RenderCopy(*renderer, gameOverTxt, NULL, &gameOverRect);
        return 1;

    }
    if (*playerTouched)
    {
        *playerTouched =0;

        player->lives -=1;
        printf("Player lives : %d\n", player->lives);
        if (player->lives == 0)
        {
            printf("Game Over\n");
            SDL_Color color = COLOR_COSMIC_PINK;
            SDL_Texture *gameOverTxt = createTextTexture(renderer, PATH_PREMIER, 50, "Game Over", color);
            SDL_Rect gameOverRect = {WIDTH/2 - 100, HEIGHT/2 - 50, 200, 100};
            SDL_RenderCopy(*renderer, gameOverTxt, NULL, &gameOverRect);
            return 1;
         
        }
        else
        {
            for (int i = 0; i < player->lives; i++)
            {
                heart[i].active = 1;
            }
        }
    }
    return 0;
}