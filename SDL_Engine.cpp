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
        // Text 초기화
        TTF_Init();
        this->gameFont = TTF_OpenFont("Font.ttf", 18);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "사운드 초기화 실패";
			success = false;
		}

        this->setSound = Mix_LoadWAV("Sound.wav");

        // PNG 초기화
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}

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


bool SDL_Engine::initPictures()
{
    // 검정 돌 초기화
    SDL_Surface* temp = NULL;
    temp = IMG_Load("black_d.png");
    
    if (temp == NULL)
    {
        std::cout << "블랙 이미지 로드 실패";
        return false;
    }

    this->gameTexture[0] = SDL_CreateTextureFromSurface(this->renderer, temp);
    SDL_FreeSurface(temp);
    temp = NULL;

    // 흰색 돌 초기화
    temp = IMG_Load("white_d.png");
    
    if (temp == NULL)
    {
        std::cout << "화이트 이미지 로드 실패";
        return false;
    }

    this->gameTexture[1] = SDL_CreateTextureFromSurface(this->renderer, temp);
    SDL_FreeSurface(temp);
    temp = NULL;

    return true;
}


bool SDL_Engine::initBoard()
{
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
    SDL_DestroyTexture(this->gameTexture[0]);
    SDL_DestroyTexture(this->gameTexture[1]);
    this->gameTexture[0] = NULL;
    this->gameTexture[1] = NULL;
    
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->gameWindow);
    this->renderer = NULL;
    this->gameWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    exit(0);
}

void SDL_Engine::gameOverText(State turn)
{
    TTF_Font* font = TTF_OpenFont("Font.ttf", 18);
    SDL_Color black = {0, 0, 0};
    SDL_Surface* surfaceMessage;

    if (turn == BLACK_STONE)
    {
        surfaceMessage = TTF_RenderText_Solid(font, "*  Black Player Win!  *", black);
    }

    else if (turn == WHITE_STONE)
    {
        surfaceMessage = TTF_RenderText_Solid(font, "*  White Player Win!  *", black);
    }

    this->gameTexture[2] = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
    SDL_Rect message_rect;
    message_rect.x = 450;
    message_rect.y = 60;
    message_rect.w = surfaceMessage->w;
    message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(this->renderer, this->gameTexture[2], NULL, &message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(this->gameTexture[2]);
    SDL_RenderPresent(this->renderer);
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

            if (crrntX != -1 && crrntY != -1)
            {
                int row = locationToRow(crrntY);
                int col = locationToCol(crrntX);

                if (this->GAMEobj->getBoard()->CheckSet(row, col))
                {
                    // 바둑알 놓기
                    Mix_PlayChannel(-1, this->setSound, 0);
                    this->GAMEobj->getTurnPlayer()->SetPiece(row, col, this->GAMEobj->getBoard());
                    this->drawOmokPng(crrntX, crrntY, this->GAMEobj->getTurn());
                    SDL_RenderPresent(this->renderer);

                    // 게임 오버
                    if (this->GAMEobj->getBoard()->CheckGameOver()) 
                    {
                        this->gameOverText(this->GAMEobj->getTurn());
                        SDL_Delay(10000);
                        this->close(); 
                    }

                    // 턴 변경
                    else
                    {
                        this->GAMEobj->ChangeTurn();
                        return;
                    }                 
                }

            }
            else { return; }
        }
    }
}


// 마우스 지점 인식
int SDL_Engine::getLowerBound_ord_x(int t)
{
    for (int i = 0; i < 15; i++)
    {
        if (t <= 60 * i + 120 + 15 && t >= 60 * i + 120 - 15)
        {
            return 120 + 60 * i;
        }
    }

    return -1;
}

// 마우스 지점 인식
int SDL_Engine::getLowerBound_ord_y(int t)
{
    for (int i = 0; i < 15; i++)
    {
        if (t <= 60 * i + 130 + 15 && t >= 60 * i + 130 - 15)
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

void SDL_Engine::drawOmokPng(const int x, const int y, State turn)
{
    SDL_Rect src, dst;

    src.h = 225;
    src.w = 225;
    src.x = 0;
    src.y = 0;

    dst.h = 50;
    dst.w = 50;
    dst.x = x - 23;
    dst.y = y - 20;

    if (turn == BLACK_STONE)
    {
        SDL_QueryTexture(this->gameTexture[0], NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(this->renderer, this->gameTexture[0], &src, &dst);
    }

    else
    {
        SDL_QueryTexture(this->gameTexture[1], NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(this->renderer, this->gameTexture[1], &src, &dst);
    }
}