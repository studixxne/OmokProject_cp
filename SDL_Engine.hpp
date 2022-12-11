#ifndef SDL_ENGINE
#define SDL_ENGINE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"


class SDL_Engine
{
private:
    const int WIDTH = 1080;
    const int HEIGHT = 1020;
    SDL_Window* gameWindow = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* gameTexture[3];
    Mix_Chunk* setSound = NULL;
    TTF_Font* gameFont = NULL;
    Game* GAMEobj = new Game();
    bool gameOver = false;

public:
    bool init();
    bool initBoard();
    bool initPictures();
    void close();
    void gameOverText(State turn);
    void handleEvent(SDL_Event* e);
    int getLowerBound_ord_x(int t);
    int getLowerBound_ord_y(int t);
    int locationToCol(int mouse_x);
    int locationToRow(int mouse_y);
    void drawOmokPng(const int x, const int y, State turn);
};

#endif