#include "SDL_Engine.hpp"
#include <bits/stdc++.h>

int main()
{
    SDL_Engine omok;

    // Start Init
    if (!omok.init())
    {
        std::cout << "초기화에 실패하였습니다.\n";
    }

    else
    {
        {
            bool quit = false;

            if (!omok.initBoard())
            {
                std::cout << "게임 보드 초기화에 실패하였습니다\n";
                omok.close();
                return 1;
            }

            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT) { quit = true; }

                    omok.handleEvent(&e);
                }
            }
        }
    }

    omok.close();

    return 0;
}