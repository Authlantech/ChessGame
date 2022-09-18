#include "GameBoard.h"
#define FILES
#include "Macros.h"

void GameBoard::StartGameBoard()
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			boardSquares[x][y].sPos = sf::Vector2f(x * 100, y * 100);
			boardSquares[x][y].sPos2 = sf::Vector2f((x * 100) + 100, (y * 100) + 100); 
		}
	}
	setPosition(0, 0); 
	setSize(sf::Vector2f(800, 800));
	board_texture.loadFromFile(CHESS_BOARD_TEXTURE_FILE);
	setTexture(&board_texture);
}



bool Square::InSquare(Square* square, sf::Vector2f pos)
{
	if (
		pos.x > square->sPos.x &&
		pos.y > square->sPos.y &&
		pos.x < square->sPos2.x &&
		pos.y < square->sPos2.y
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

