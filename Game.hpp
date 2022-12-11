#ifndef GAME_H
#define GAME_H

#include "Board.hpp"
#include "Player.hpp"

class Game
{
private:
    Board* boardGame;
    State playerTurn = BLACK_STONE;
    Player* blackPlayer;
    Player* whitePlayer;

public:
    Game();
    Board* getBoard() { return boardGame; }
    Player* getTurnPlayer();
    State getTurn() { return playerTurn; }
    void ChangeTurn();

};


#endif