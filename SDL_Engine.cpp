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
            // Get mouse Position
            int x, y;
            SDL_GetMouseState(&x, &y);
            int crrntX = this->getLowerBound_ord_x(x);
            int crrntY = this->getLowerBound_ord_y(y);
            std::cout << crrntX << ' ' << crrntY << '\n';

            if (crrntX != -1 && crrntY != -1)
            {
                int row = locationToRow(crrntY);
                int col = locationToCol(crrntX);
                std::cout << row << ' ' << col << '\n';

                /*
                if (this->GAMEobj->getBoard()->CheckSet(row, col))
                {
                    // 바둑알 놓기
                    this->GAMEobj->getTurnPlayer()->SetPiece(row, col, this->GAMEobj->getBoard());
                    
                    // 게임 오버
                    if (this->GAMEobj->getBoard()->CheckGameOver()) { this->close(); }

                    else { return; }                 
                }
                */

            }
            else { return; }
        }
    }
}

// 마우스 지점 확정
int SDL_Engine::getLowerBound_ord_x(int t)
{
    for (int i = 0; i < 15; i++)
    {
        if (t <= 60 * i + 120 + 10 && t >= 60 * i + 120 - 10)
        {
            return 120 + 60 * i;
        }
    }

    return -1;
}

// 마우스 지점 확정
int SDL_Engine::getLowerBound_ord_y(int t)
{
    for (int i = 0; i < 15; i++)
    {
        if (t <= 60 * i + 130 + 10 && t >= 60 * i + 130 - 10)
        {
            return 130 + 60 * i;
        }
    }

    return -1;
}

int SDL_Engine::locationToCol(int x)
{
    return (x - 120) / 60;
}

int SDL_Engine::locationToRow(int y)
{
    return (y - 130) / 60;
}