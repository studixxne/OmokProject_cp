#ifndef GAME_H
#define GAME_H

#include "Board.hpp"
#include "Player.hpp"

class Game
{
private:
    Board* boardGame;
    State playerTurn = BLACK_STONE;

public:
    Game() { this->boardGame = new Board; } ;

};


#endif