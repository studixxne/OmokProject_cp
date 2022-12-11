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

void Game::ChangeTurn()
{
    if ( this->getTurn() == BLACK_STONE )
    {
        this->playerTurn = WHITE_STONE;
    }

    else { this->playerTurn = BLACK_STONE; }    
}