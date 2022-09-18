#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>



class Piece : public sf::RectangleShape
{
private : 
	sf::Texture PieceTexture;		
public : 
	enum PieceType
	{
		PION,
		CASTLE,
		HORSE,
		ELEPHANT,
		QUEEN,
		KING
	}type;
	sf::Color color;
	bool firstmovement = true;
	bool killedTemporarely = false;
	void* ownerPlayerptr = nullptr;
	void StartPiece(sf::Vector2f pos,std::string texture_path,PieceType piecetype,sf::Color pieceColor,void*ownerPlayer);
	~Piece();
};
