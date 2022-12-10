#include "SDL_Engine.hpp"
#include <iostream>

bool SDL_Engine::init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL 초기화 실패\n";    
        success = false;
    }
    else
    {
        TTF_Init();
        // create window
        this->gameWindow = SDL_CreateWindow("Omok", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_SHOWN);
        if (this->gameWindow == NULL)
        {
            std::cout << "WINDOW 생성 실패\n";
            success = false;
        }

        else
        {
            this->renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (this->renderer == NULL)
            {
                std::cout << "RENDERER 생성 실패\n";
                success = false;
            }
            SDL_SetRenderDrawColor(renderer, 235, 229, 215, 92);
            SDL_RenderClear(this->renderer);
        }
    }

    return success;
}

bool SDL_Engine::initBoard()
{
    turnText(WHITE_STONE);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    
    // 세로 줄 그리기
    for (int i = 0; i < 15; i++)
    {
        SDL_RenderDrawLine(this->renderer, 120 + 60 * i, 130, 120 + 60 * i, 970);
    }

    // 가로 줄 그리기
    for (int i = 0; i < 15; i++)
    {
        SDL_RenderDrawLine(this->renderer, 120, 130 + 60 * i, 960, 130 + 60 * i);
    }

    SDL_RenderPresent(this->renderer);

    return true;
}

void SDL_Engine::close()
{
    SDL_Quit();
}

void SDL_Engine::turnText(State turn)
{
    TTF_Font* font = TTF_OpenFont("Font.ttf", 22);
    SDL_Color black = {0, 0, 0};
    SDL_Surface* surfaceMessage;

    if (turn == BLACK_STONE)
    {
        surfaceMessage = TTF_RenderText_Solid(font, "*  Black Player Turn  *", black);
    }

    else if (turn == WHITE_STONE)
    {
        surfaceMessage = TTF_RenderText_Solid(font, "*  White Player Turn  *", black);
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
    SDL_Rect message_rect;
    message_rect.x = 470;
    message_rect.y = 60;
    message_rect.w = 140;
    message_rect.h = 20;

    SDL_RenderCopy(this->renderer, message, NULL, &message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void SDL_Engine::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        if (e->button.button == SDL_BUTTON_LEFT)
        {
            
        }
    }
}