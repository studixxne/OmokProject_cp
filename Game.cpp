#include "Game.hpp"

Game::Game()
{
     this->boardGame = new Board;
     this->blackPlayer = new Player(BLACK_STONE);
     this->whitePlayer = new Player(WHITE_STONE);
}

Player* Game::getTurnPlayer()
{
    if (this->playerTurn == BLACK_STONE) { return blackPlayer; }

    else { return whitePlayer; }
}