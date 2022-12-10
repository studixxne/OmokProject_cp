#ifndef PLAYER_H
#define PLAYER_H
#include "Board.hpp"

class Player
{
private:
    State player_color = BLACK_STONE;

public:
    void SetPiece(int x, int y, Board *b);
};


#endif