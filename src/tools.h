
#pragma once

#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h> // for text 
/// fonts
#define FONT_PATH_TITLE  "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Electron.ttf"
#define FONT_PATH_DESIGN "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Invaders.ttf"
#define FONT_PATH_PLAY   "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Electron.ttf"
#define PATH_PREMIER "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\fonts\\Premier.ttf"
/// images
#define PATH_PLAYER "C:\\Users\\PHELELEP\\Documents\\GitHub\\projPolytechInfoSpaceInvaders\\img\\player.png"
/// colors 
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

#define WIDTH 960
#define HEIGHT 720



SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char *fontPath, int fontSize, const char *text, SDL_Color color);

int cleanup(SDL_Window *window, SDL_Renderer *renderer);

typedef enum 
{
    LOAD_PAGE,
    GAME_STARTED,
    GAME_OVER
}GameState;