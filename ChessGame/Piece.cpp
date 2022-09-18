#include "Piece.h"

void Piece::StartPiece(sf::Vector2f pos, std::string texture_path,PieceType piecetype,sf::Color pieceColor,void*ownerPlayer)
{
	color = pieceColor;
	type = piecetype;
	setPosition(pos); 
	setSize(sf::Vector2f(100, 100));
	PieceTexture.loadFromFile(texture_path);
	setTexture(&PieceTexture);
	ownerPlayerptr = ownerPlayer;
}

Piece::~Piece()
{
}
