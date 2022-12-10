#ifndef PLAYER_H
#define PLAYER_H
#include "Board.hpp"

class Player
{
private:
    State player_color;

public:
    Player(State color) { player_color = color; }
    void SetPiece(int x, int y, Board *b);
};


#endif