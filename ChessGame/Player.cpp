#include "Player.h"

void Player::SetType(PlayerType type)
{
	this->type = type;
}

void Player::AddPiece(Piece* piece)
{
	pieces.push_back(piece);
	if (piece->type == Piece::PieceType::KING)
	{
		King = piece;
	}
}

void Player::RemovePiece(Piece* piece)
{
	if (pieces.size() > 0)
	{
		for (int a = 0; a < pieces.size(); a++)
		{
			if (pieces[a] == piece)
			{
				pieces.erase(pieces.begin() + a);;				
			}
		}
	}
}
