

/*


createPlayer(SDL_Window *window, SDL_Renderer *renderer,SDL_Texture * playerTexture)
{
    SDL_Rect playerRect = {WIDTH/2 - 25, HEIGHT - 50, 50, 50}; 

    // Load player texture

    
    playerTexture = IMG_LoadTexture(renderer, PATH_PLAYER);
    if (playerTexture == NULL) {
        printf("Failed to load player image: %s\n", SDL_GetError());
        cleanup(window, renderer);
        return EXIT_FAILURE;
    }
    
}
*/