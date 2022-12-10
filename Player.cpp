#include "Player.hpp"

void Player::SetPiece(int x, int y, Board *b)
{
    if (b->CheckSet(x, y))
    {
        b->SetMap(x, y, player_color);
    }
}