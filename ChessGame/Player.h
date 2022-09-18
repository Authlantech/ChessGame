#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>
#include "Piece.h"
#include "GameBoard.h"

enum PlayerType
{
	BLACK,
	WHITE,
	
};



class Player
{
private :
	std::vector<Piece*>pieces;
	Square* choosedSquare = nullptr; 
	Square* choosedPiecesOwnerSquare = nullptr;
	PlayerType type;
	Piece* King = nullptr;
public : 
	void SetType(PlayerType type);
	void AddPiece(Piece* piece);
	void RemovePiece(Piece* piece);
	friend class Engine;
};

