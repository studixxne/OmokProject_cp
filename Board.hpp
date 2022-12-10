#ifndef BOARD_H
#define BOARD_H

enum State {ABSENCE, BLACK_STONE, WHITE_STONE};

class Board
{
private:
    State map[15][15] = {ABSENCE};
    State turn = BLACK_STONE;

public:
    bool CheckSet(int x, int y);
    bool CheckGameOver();
    void SetMap(int x, int y, State stone_Color);
};

#endif