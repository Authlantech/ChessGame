#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>
#include "Piece.h"

#define pos(x,y) sf::Vector2f(x,y)

struct Square
{
	sf::Vector2f sPos;
	sf::Vector2f sPos2; 

	Piece* ownedPiece = nullptr;

	static bool InSquare(Square* square, sf::Vector2f pos);
	
};


class GameBoard : public sf::RectangleShape
{
private :
	Square boardSquares[8][8];
	sf::Texture board_texture;
public : 
	void StartGameBoard();	
	friend class Engine;
};