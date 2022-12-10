#include "Board.hpp"

bool Board::CheckSet(int x, int y)
{
    if (x >= 15 || y >= 15) { return false; }

    if (this->map[x][y] == ABSENCE) { return true; }
    else { return false; }
}

bool Board::CheckGameOver()
{
    int white_win = 0;
    int black_win = 0;

    // 가로 승리 체크
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (this->map[i][j] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[i][j] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }

    // 세로 승리 체크
    white_win = 0; black_win = 0;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (this->map[j][i] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[j][i] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }

    // 오른쪽 아래 방향 대각선 체크
    white_win = 0; black_win = 0;

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j + i < 15; j++)
        {
            if (this->map[j + i][j] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[j + i][j] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }

    for (int i = 1; i < 11; i++)
    {
        for (int j = 0; j + i < 15; j++)
        {
            if (this->map[j][j + i] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[j][j + i] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }


    // 왼쪽 아래 방향 대각선 체크
    white_win = 0; black_win = 0;

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j + i < 15; j++)
        {
            if (this->map[14 - (j + i)][14 - j] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[14 - (j + i)][14 - j] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }

    for (int i = 1; i < 11; i++)
    {
        for (int j = 0; j + i < 15; j++)
        {
            if (this->map[14 - j][14 - (j + i)] == BLACK_STONE)
            {
                black_win++;
                white_win = 0;
            }

            else if (this->map[14 - j][14 - (j + i)] == WHITE_STONE)
            {
                white_win++;
                black_win = 0;
            }

            else { white_win = 0; black_win = 0; }

            if (black_win == 5 || white_win == 5) { return true; }
        }
    }

    return false;
}

void Board::SetMap(int x, int y, State player_color)
{
    if (player_color == WHITE_STONE) { this->map[x][y] = WHITE_STONE; }

    else { this->map[x][y] = BLACK_STONE; } 
}



