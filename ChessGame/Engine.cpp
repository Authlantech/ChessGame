#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Macros.h"
#include <windows.h>


#define Find(a) line.find(a) != std::string::npos
#define pause system("pause")

void Engine::GetInput(sf::Vector2f pos)
{	
	if (pieceToBeChanged != nullptr)
	{
		for (int a = 0; a < 4; a++)
		{
			if (
				SelectionSquares[a].getPosition().x < pos.x &&
				SelectionSquares[a].getPosition().x + SelectionSquares[a].getSize().x > pos.x &&
				SelectionSquares[a].getPosition().y < pos.y &&
				SelectionSquares[a].getPosition().y + SelectionSquares[a].getSize().x > pos.y
				)
			{

				Piece* newPiece = new Piece;

				switch (a)
				{
				case 0:
					if (ownerPlayerofPiece->type == PlayerType::WHITE)
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_WHITE_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::White, ownerPlayerofPiece);
					else
					{
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_BLACK_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::Black, ownerPlayerofPiece);
					}
					board->boardSquares[(int)pieceToBeChanged->getPosition().x / 100][(int)pieceToBeChanged->getPosition().y / 100].ownedPiece = newPiece;
					ownerPlayerofPiece->RemovePiece(pieceToBeChanged);
					ownerPlayerofPiece->AddPiece(newPiece);
					newPiece->setPosition(pieceToBeChanged->getPosition());
					pieceToBeChanged = nullptr;
					ownerPlayerofPiece = nullptr;
					break;
				case 1:	
					if (ownerPlayerofPiece->type == PlayerType::WHITE)
					{
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_WHITE_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::White, ownerPlayerofPiece);
					}
					else
					{
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_BLACK_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::Black, ownerPlayerofPiece);
					}
					board->boardSquares[(int)pieceToBeChanged->getPosition().x / 100][(int)pieceToBeChanged->getPosition().y / 100].ownedPiece = newPiece;
					ownerPlayerofPiece->RemovePiece(pieceToBeChanged);
					ownerPlayerofPiece->AddPiece(newPiece);
					newPiece->setPosition(pieceToBeChanged->getPosition());
					pieceToBeChanged = nullptr;
					ownerPlayerofPiece = nullptr;
					break;
				case 2:
					if (ownerPlayerofPiece->type == PlayerType::WHITE)
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_WHITE_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::White, ownerPlayerofPiece);
					else
					{
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_BLACK_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::Black, ownerPlayerofPiece);
					}
					board->boardSquares[(int)pieceToBeChanged->getPosition().x / 100][(int)pieceToBeChanged->getPosition().y / 100].ownedPiece = newPiece;
					ownerPlayerofPiece->RemovePiece(pieceToBeChanged);
					ownerPlayerofPiece->AddPiece(newPiece);
					newPiece->setPosition(pieceToBeChanged->getPosition());
					pieceToBeChanged = nullptr;
					ownerPlayerofPiece = nullptr;
					break;
				case 3:
					if (ownerPlayerofPiece->type == PlayerType::WHITE)
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_WHITE_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::White, ownerPlayerofPiece);
					else
					{
						newPiece->StartPiece(pieceToBeChanged->getPosition(), CHESS_BLACK_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::Black, ownerPlayerofPiece);
					}
					board->boardSquares[(int)pieceToBeChanged->getPosition().x / 100][(int)pieceToBeChanged->getPosition().y / 100].ownedPiece = newPiece;
					ownerPlayerofPiece->RemovePiece(pieceToBeChanged);
					ownerPlayerofPiece->AddPiece(newPiece);
					newPiece->setPosition(pieceToBeChanged->getPosition());
					pieceToBeChanged = nullptr;
					ownerPlayerofPiece = nullptr;
					break;
				};

				//Checking if game is over : 

				int placenumberEnemyCanMove = 0;

				for (int a = 0; a < UnchoosedPlayer()->pieces.size(); a++)
				{
					std::vector<Square*>everywherepiececanmove = FindMovablePositions(UnchoosedPlayer()->pieces[a], UnchoosedPlayer());
					placenumberEnemyCanMove = placenumberEnemyCanMove + everywherepiececanmove.size();
				}


				if (placenumberEnemyCanMove == 0)
				{
					gameOver = true;
					std::vector<Square*>EverySquareSelectedPlayerSees;
					for (int a = 0; a < selectedPlayer->pieces.size(); a++)
					{
						std::vector<Square*>temp = FindPieceRange(selectedPlayer->pieces[a], selectedPlayer);
						for (int b = 0; b < temp.size(); b++)
						{
							EverySquareSelectedPlayerSees.push_back(temp[b]);
						}
					}
					if (
						std::find(EverySquareSelectedPlayerSees.begin(), EverySquareSelectedPlayerSees.end(), &board->boardSquares[(int)UnchoosedPlayer()->King->getPosition().x / 100][(int)UnchoosedPlayer()->King->getPosition().y / 100])
						==
						EverySquareSelectedPlayerSees.end()
						)
					{
						winner_player = nullptr;
					}
					else
					{
						winner_player = selectedPlayer;
					}
				}

				if (selectedPlayer == players)
				{
					selectedPlayer = &players[1];
				}
				else
				{
					selectedPlayer = players;
				}

				PositionsInRange.clear();
				MovablePositions_.clear();

				return;

			}
		}
	}

	else if (selectedPlayer->choosedPiecesOwnerSquare == nullptr)
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				bool result = Square::InSquare(&board->boardSquares[x][y], pos);
				if (result)
				{
					if (board->boardSquares[x][y].ownedPiece == nullptr)
					{
						return;
					}
					else
					{
						if (std::find(selectedPlayer->pieces.begin(), selectedPlayer->pieces.end(), board->boardSquares[x][y].ownedPiece) == selectedPlayer->pieces.end())
						{
							return;
						}
						selectedPlayer->choosedPiecesOwnerSquare = &board->boardSquares[x][y];
						PositionsInRange = FindPieceRange(board->boardSquares[x][y].ownedPiece, selectedPlayer);
						MovablePositions_ = FindMovablePositions(board->boardSquares[x][y].ownedPiece, selectedPlayer);
						return;
					}
				}
			}
		}
	}	

	else
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				bool result = Square::InSquare(&board->boardSquares[x][y], pos);
				if (result)
				{

					//Deciding what to do if choosed square is not empty : 

					if (board->boardSquares[x][y].ownedPiece != nullptr)
					{
						Piece* pieceonsquare = board->boardSquares[x][y].ownedPiece;
						if (std::find(selectedPlayer->pieces.begin(), selectedPlayer->pieces.end(), pieceonsquare) != selectedPlayer->pieces.end())
						{
							//Situation that a player clicks on another piece owned by himself : 

							selectedPlayer->choosedPiecesOwnerSquare = &board->boardSquares[x][y];
							PositionsInRange = FindPieceRange(board->boardSquares[x][y].ownedPiece, selectedPlayer);
							MovablePositions_ = FindMovablePositions(board->boardSquares[x][y].ownedPiece, selectedPlayer);
							return;
						}

					}

					if (std::find(PositionsInRange.begin(), PositionsInRange.end(), &board->boardSquares[x][y]) == PositionsInRange.end())
					{
						//Situation that choosed square cannot be played : 
						return;
					}

					Player* enemyPlayerptr = UnchoosedPlayer();

					//Avoiding player from leaving it's king in danger

					{
						sf::Vector2f kingindex;

						//Deciding where is king : 

						if (selectedPlayer->choosedPiecesOwnerSquare->ownedPiece->type == Piece::PieceType::KING)
						{
							kingindex = sf::Vector2f(x, y);
						}
						else
						{
							kingindex = sf::Vector2f(selectedPlayer->King->getPosition().x / 100, selectedPlayer->King->getPosition().y / 100);
						}

						//Saving board layout before playing virtually : 

						void* adresses[] = {
							board->boardSquares[x][y].ownedPiece,					//Saving what is inside of choosed square before playing 
							selectedPlayer->choosedPiecesOwnerSquare->ownedPiece,	//Saving the addres of choosed piece 
							selectedPlayer->choosedPiecesOwnerSquare,				//Saving the addres of choosed piece's owner square 
							selectedPlayer->choosedSquare							
						};

						//Finding what happens when decided piece is moved to decided square (playing virtually): 

						if (board->boardSquares[x][y].ownedPiece != nullptr)
						{
							board->boardSquares[x][y].ownedPiece->killedTemporarely = true;
						}

						board->boardSquares[x][y].ownedPiece = selectedPlayer->choosedPiecesOwnerSquare->ownedPiece;
						selectedPlayer->choosedPiecesOwnerSquare->ownedPiece = nullptr;
						selectedPlayer->choosedPiecesOwnerSquare = nullptr;
						selectedPlayer->choosedSquare = nullptr;

						std::vector<Square*>EverySquareEnemycanPlay;
						for (int a = 0; a < enemyPlayerptr->pieces.size(); a++)
						{
							std::vector<Square*>PositionsPieceCanPlay = FindPieceRange(enemyPlayerptr->pieces[a], enemyPlayerptr);
							for (int b = 0; b < PositionsPieceCanPlay.size(); b++)
							{
								EverySquareEnemycanPlay.push_back(PositionsPieceCanPlay[b]);
							}
						}

						//Ending playing virtually (Returning to last saved board layout) : 

						board->boardSquares[x][y].ownedPiece = (Piece*)adresses[0];
						selectedPlayer->choosedPiecesOwnerSquare = (Square*)adresses[2];
						selectedPlayer->choosedPiecesOwnerSquare->ownedPiece = (Piece*)adresses[1];
						selectedPlayer->choosedSquare = (Square*)adresses[3];

						if (board->boardSquares[x][y].ownedPiece != nullptr)
						{
							board->boardSquares[x][y].ownedPiece->killedTemporarely = false;
						}

						//Deciding if piece can move : 

						if (std::find(EverySquareEnemycanPlay.begin(), EverySquareEnemycanPlay.end(), &board->boardSquares[(int)kingindex.x][(int)kingindex.y]) != EverySquareEnemycanPlay.end())
						{
							return;
						}

					}

					// Moving piece to choosed position : 

					if(board->boardSquares[x][y].ownedPiece != nullptr)
					{ 
						if (!(std::find(selectedPlayer->pieces.begin(), selectedPlayer->pieces.end(), board->boardSquares[x][y].ownedPiece) != selectedPlayer->pieces.end()) &&
							std::find(PositionsInRange.begin(), PositionsInRange.end(), &board->boardSquares[x][y]) != PositionsInRange.end()
							)
						{
							//Situation that player chooses another square that owns a piece owned by enemy player :

							UnchoosedPlayer()->RemovePiece(board->boardSquares[x][y].ownedPiece);
						}
					}															

					Piece* movedPiece = selectedPlayer->choosedPiecesOwnerSquare->ownedPiece;
					board->boardSquares[x][y].ownedPiece = selectedPlayer->choosedPiecesOwnerSquare->ownedPiece;
					selectedPlayer->choosedPiecesOwnerSquare->ownedPiece->firstmovement = false;
					selectedPlayer->choosedPiecesOwnerSquare->ownedPiece->setPosition(x * 100, y * 100);
					selectedPlayer->choosedPiecesOwnerSquare->ownedPiece = nullptr;
					selectedPlayer->choosedPiecesOwnerSquare = nullptr; 
					selectedPlayer->choosedSquare = nullptr; 					
					
				endMove : 

					//Checking if game is over : 

					int placenumberEnemyCanMove = 0;

					for (int a = 0; a < UnchoosedPlayer()->pieces.size(); a++)
					{
						std::vector<Square*>everywherepiececanmove = FindMovablePositions(UnchoosedPlayer()->pieces[a], UnchoosedPlayer());
						placenumberEnemyCanMove = placenumberEnemyCanMove + everywherepiececanmove.size();
					}


					if (placenumberEnemyCanMove == 0)
					{
						gameOver = true;
						std::vector<Square*>EverySquareSelectedPlayerSees; 
						for (int a = 0; a < selectedPlayer->pieces.size(); a++)
						{
							std::vector<Square*>temp = FindPieceRange(selectedPlayer->pieces[a], selectedPlayer);
							for (int b = 0; b < temp.size(); b++)
							{
								EverySquareSelectedPlayerSees.push_back(temp[b]);
							}
						}
						if (
							std::find(EverySquareSelectedPlayerSees.begin(), EverySquareSelectedPlayerSees.end(), &board->boardSquares[(int)UnchoosedPlayer()->King->getPosition().x / 100][(int)UnchoosedPlayer()->King->getPosition().y / 100])
							==
							EverySquareSelectedPlayerSees.end()
							)
						{
							winner_player = nullptr;
						}
						else
						{
							winner_player = selectedPlayer;
						}
					}				

					//Checking if any pawn is at the end : 

					if (movedPiece->type == Piece::PieceType::PION)
					{
						sf::Vector2f piecepos = sf::Vector2f(movedPiece->getPosition().x / 100, movedPiece->getPosition().y / 100);
						if (movedPiece->color == sf::Color::White)
						{
							if (piecepos.y == 0)
							{
								pieceToBeChanged = movedPiece;
								ownerPlayerofPiece = selectedPlayer;	
								for (int a = 0; a < 4; a++)
								{
									SelectionSquares[a].setTexture(&SelectionSquaresWhiteTextures[a]);
								}
								
								if (pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + (SelectionSquares->getSize().x * 2) > 800)
								{
									SelectionSquares[0].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - (SelectionSquares->getSize().x * 2),pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y));
									SelectionSquares[1].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - SelectionSquares->getSize().x,pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y));
									SelectionSquares[2].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - (SelectionSquares->getSize().x * 2),pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y + SelectionSquares->getSize().y));
									SelectionSquares[3].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y + SelectionSquares->getSize().y));
								}		
								
								else
								{
									SelectionSquares[0].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x,pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y));
									SelectionSquares[1].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y));
									SelectionSquares[2].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x, pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y + SelectionSquares->getSize().y));
									SelectionSquares[3].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y + pieceToBeChanged->getSize().y + SelectionSquares->getSize().y));
								}

								return;
							}
						}
						else
						{
							if (piecepos.y == 7)
							{
								pieceToBeChanged = movedPiece;
								ownerPlayerofPiece = selectedPlayer;
								for (int a = 0; a < 4; a++)
								{
									SelectionSquares[a].setTexture(&SelectionSquaresBlackTextures[a]);
								}

								if (pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + (SelectionSquares->getSize().x * 2) > 800)
								{
									SelectionSquares[0].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - (SelectionSquares->getSize().x * 2), pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y));
									SelectionSquares[1].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y));
									SelectionSquares[2].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - (SelectionSquares->getSize().x * 2), pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y - SelectionSquares->getSize().y));
									SelectionSquares[3].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x - SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y - SelectionSquares->getSize().y));
								}

								else
								{
									SelectionSquares[0].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y));
									SelectionSquares[1].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y));
									SelectionSquares[2].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y - SelectionSquares->getSize().y));
									SelectionSquares[3].setPosition(sf::Vector2f(pieceToBeChanged->getPosition().x + pieceToBeChanged->getSize().x + SelectionSquares->getSize().x, pieceToBeChanged->getPosition().y - SelectionSquares->getSize().y - SelectionSquares->getSize().y));
								}


								return;
							}
						}						
					}

					if (selectedPlayer == players)
					{
						selectedPlayer = &players[1];
					}
					else
					{
						selectedPlayer = players; 
					}	
					PositionsInRange.clear();
					MovablePositions_.clear();

					return;
				}
			}
		}
	}
}

Player* Engine::UnchoosedPlayer()
{
	if (players == selectedPlayer)
	{
		return &players[1];
	}
	else
	{
		return players;
	}
}

std::vector<Square*> Engine::FindPieceRange(Piece* piece,Player*ownerPlayer)
{

	if (piece->killedTemporarely)
	{
		return std::vector<Square*>();
	}

	std::vector<std::vector<Square*>>MovableSquares;	
	std::vector<Square*>SquareBlock;

	sf::Vector2i piecePos = sf::Vector2i(piece->getPosition().x / 100, piece->getPosition().y / 100);

	int x = piecePos.x; 
	int y = piecePos.y;

	switch (piece->type)
	{
	case Piece::PieceType::QUEEN : 

		while (x < 8)
		{
			x++;
			if (x >= 8) break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}

		if(SquareBlock.size() > 0)
		{ 
			MovableSquares.push_back(SquareBlock); 
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;

		while(x >= 0)
		{
			x--;
			if (x < 0) break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;

		while (y < 8)
		{
			y++; 
			if (y >= 8) break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		y = piecePos.y;
		x = piecePos.x;

		while (y >= 0)
		{
			y--; 
			if (y < 0)break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		y = piecePos.y;
		x = piecePos.x;


		while (
			x >= 0 &&
			y >= 0
			)
		{
			x--; 
			y--;
			if (x < 0 || y < 0) break; 
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;

		while (
			x < 8 &&
			y < 8
			)
		{
			x++; 
			y++; 
			if (x >= 8 || y >= 8)break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;

		while (
			x < 8 &&
			y >= 0
			)
		{
			x++; 
			y--;
			if (x >= 8 || y < 0)break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;

		while (
			x >= 0 &&
			y < 8 
			)
		{
			x--; 
			y++; 
			if (x < 0 || y >= 8)break;
			SquareBlock.push_back(&board->boardSquares[x][y]);
		}
		if(SquareBlock.size() > 0)
		{
			MovableSquares.push_back(SquareBlock);
			SquareBlock.clear();
		}
		x = piecePos.x;
		y = piecePos.y;
			
		break; 
		case Piece::PieceType::ELEPHANT: 
			while (
				x < 8 &&
				y < 8
				)
			{
				x++; 
				y++; 
				if (x >= 8 || y >= 8)
				{
					break;
				}				
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}

			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock); 
				SquareBlock.clear();
			}
			x = piecePos.x; 
			y = piecePos.y;

			while (
				x >= 0 &&
				y >= 0
				)
			{
				x--; 
				y--; 
				if (
					x < 0 || y < 0
					)
				{
					break;
				}
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}

			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			x = piecePos.x;
			y = piecePos.y;
	
			while (
				x >= 0 &&
				y < 8
				)
			{
				x--; 
				y++; 
				if (
					x < 0 ||
					y >= 8
					)
				{
					break;
				}
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}

			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			x = piecePos.x;
			y = piecePos.y;

			while (
				x < 8 &&
				y >= 0
				)
			{
				x++; 
				y--; 
				if (
					x >= 8 || y < 0
					)
				{
					break;
				}
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}

			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			x = piecePos.x;
			y = piecePos.y;
			break;
		case Piece::PieceType::CASTLE : 
			while (x < 8)
			{
				x++;
				if (x >= 8) break;
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}

			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			x = piecePos.x;
			y = piecePos.y;

			while (x >= 0)
			{
				x--;
				if (x < 0) break;
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}
			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			x = piecePos.x;
			y = piecePos.y;

			while (y < 8)
			{
				y++;
				if (y >= 8) break;
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}
			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			y = piecePos.y;
			x = piecePos.x;

			while (y >= 0)
			{
				y--;
				if (y < 0)break;
				SquareBlock.push_back(&board->boardSquares[x][y]);
			}
			if (SquareBlock.size() > 0)
			{
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			y = piecePos.y;
			x = piecePos.x;
			break;
		case Piece::PieceType::KING : 
			if (
				x - 1 >= 0 &&
				y - 1 >= 0
				)
			{
				SquareBlock.push_back(&board->boardSquares[x - 1][y - 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			if (
				y - 1 >= 0
				)
			{
				SquareBlock.push_back(&board->boardSquares[x][y - 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			

			if (
				y - 1 >= 0 &&
				x + 1 < 8
				)
			{
				SquareBlock.push_back(&board->boardSquares[x + 1][y - 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			if (
				x - 1 >= 0
				)
			{
				SquareBlock.push_back(&board->boardSquares[x - 1][y]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			if (
				x + 1 < 8
				)
			{
				SquareBlock.push_back(&board->boardSquares[x + 1][y]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			//Handling above : 

			if (
				x - 1 >= 0 &&
				y + 1 < 8
				)
			{
				SquareBlock.push_back(&board->boardSquares[x - 1][y + 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}
			

			if (
				y + 1 < 8 
				)
			{
				SquareBlock.push_back(&board->boardSquares[x][y + 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			if (
				y + 1 < 8 &&
				x + 1 < 8
				)
			{
				SquareBlock.push_back(&board->boardSquares[x + 1][y + 1]);
				MovableSquares.push_back(SquareBlock);
				SquareBlock.clear();
			}

			break;			
			case Piece::PieceType::PION: 
				if (piece->color == sf::Color::Black)
				{
					if (y + 1 < 8)
					{
						if(board->boardSquares[x][y + 1].ownedPiece == nullptr)
						{ 
						SquareBlock.push_back(&board->boardSquares[x][y + 1]);
						if (piece->firstmovement && y + 2 < 8 && board->boardSquares[x][y + 2].ownedPiece == nullptr)
						{
							SquareBlock.push_back(&board->boardSquares[x][y + 2]);
						}						
						MovableSquares.push_back(SquareBlock);
						SquareBlock.clear();													
						}

						if (
							x + 1 < 8 && 
							board->boardSquares[x + 1][y + 1].ownedPiece != nullptr && 
							board->boardSquares[x + 1][y + 1].ownedPiece->ownerPlayerptr != (void*)ownerPlayer
							)
						{							
							SquareBlock.push_back(&board->boardSquares[x + 1][y + 1]);
						}
						MovableSquares.push_back(SquareBlock);
						SquareBlock.clear();
						if (
							x - 1 >= 0 && 
							board->boardSquares[x - 1][y + 1].ownedPiece != nullptr && 
							board->boardSquares[x - 1][y + 1].ownedPiece->ownerPlayerptr != (void*)ownerPlayer
							)
						{
							SquareBlock.push_back(&board->boardSquares[x - 1][y + 1]);
						}
						MovableSquares.push_back(SquareBlock);
						SquareBlock.clear();
					}								
				}
				else if (piece->color == sf::Color::White)
				{
					if (y - 1 >= 0)
					{
						if (board->boardSquares[x][y - 1].ownedPiece == nullptr)
						{
							SquareBlock.push_back(&board->boardSquares[x][y - 1]);
							if (piece->firstmovement && y - 2 >= 0 && board->boardSquares[x][y - 2].ownedPiece == nullptr)
							{
								SquareBlock.push_back(&board->boardSquares[x][y - 2]);
							}
							MovableSquares.push_back(SquareBlock);
							SquareBlock.clear();
						}

						if (
							x + 1 < 8 &&
							board->boardSquares[x + 1][y - 1].ownedPiece != nullptr &&
							board->boardSquares[x + 1][y - 1].ownedPiece->ownerPlayerptr != (void*)ownerPlayer
							)
						{
							SquareBlock.push_back(&board->boardSquares[x + 1][y - 1]);
						}
						MovableSquares.push_back(SquareBlock);
						SquareBlock.clear();
						if (
							x - 1 >= 0 &&
							board->boardSquares[x - 1][y - 1].ownedPiece != nullptr &&
							board->boardSquares[x - 1][y - 1].ownedPiece->ownerPlayerptr != (void*)ownerPlayer
							)
						{
							SquareBlock.push_back(&board->boardSquares[x - 1][y - 1]);
						}
						MovableSquares.push_back(SquareBlock);
						SquareBlock.clear();
					}
				}
				break;
			case Piece::PieceType::HORSE : 
				if (x - 1 >= 0 && y - 2 >= 0)
				{
					SquareBlock.push_back(&board->boardSquares[x - 1][y - 2]); 
					MovableSquares.push_back(SquareBlock); 
					SquareBlock.clear();
				}
				if (x - 2 >= 0 && y - 1 >= 0)
				{
					SquareBlock.push_back(&board->boardSquares[x - 2][y - 1]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				if (x - 1 >= 0 && y + 2 < 8)
				{
					SquareBlock.push_back(&board->boardSquares[x - 1][y + 2]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				if (x - 2 >= 0 && y + 1 < 8)
				{
					SquareBlock.push_back(&board->boardSquares[x - 2][y + 1]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}


				if (x + 1 < 8 && y - 2 >= 0)
				{
					SquareBlock.push_back(&board->boardSquares[x + 1][y - 2]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				if (x + 2 < 8 && y - 1 >= 0)
				{
					SquareBlock.push_back(&board->boardSquares[x + 2][y - 1]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				if (x + 1 < 8 && y + 2 < 8)
				{
					SquareBlock.push_back(&board->boardSquares[x + 1][y + 2]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				if (x + 2 < 8  && y + 1 < 8)
				{
					SquareBlock.push_back(&board->boardSquares[x + 2][y + 1]);
					MovableSquares.push_back(SquareBlock);
					SquareBlock.clear();
				}
				break;			
	}

	
	for (int a = 0; a < MovableSquares.size(); a++)
	{
		for (int b = 0; b < MovableSquares[a].size(); b++)
		{

			if (MovableSquares[a][b]->ownedPiece == nullptr) continue;
			else {
				if (std::find(ownerPlayer->pieces.begin(), ownerPlayer->pieces.end(), MovableSquares[a][b]->ownedPiece) == ownerPlayer->pieces.end())
				{
					//There is a enemy piece on way: 
					if (b != MovableSquares[a].size() - 1)
						MovableSquares[a].erase(MovableSquares[a].begin() + (b + 1), MovableSquares[a].end());
				}
				else
				{
					//There is a piece in same team with this : 
					if (b != MovableSquares[a].size() - 1)
						MovableSquares[a].erase(MovableSquares[a].begin() + b, MovableSquares[a].end());
					else
					{
						MovableSquares[a].pop_back();
					}
				}
			}
		}

	}

	std::vector<Square*>Result; 
	for (int a = 0; a < MovableSquares.size(); a++)
	{
		for (int b = 0; b < MovableSquares[a].size(); b++)
		{
			Result.push_back(MovableSquares[a][b]);
		}
	}

	return Result;
}

std::vector<Square*> Engine::FindMovablePositions(Piece* piece, Player* ownerPlayer)
{
	Player* otherPlayer = nullptr; 
	if (players == ownerPlayer)
		otherPlayer = &players[1];
	else
		otherPlayer = players;

	std::vector<Square*>Conclusion;

	std::vector<Square*>pieceRange = FindPieceRange(piece, ownerPlayer); 
	if (pieceRange.size() == 0)
	{
		return Conclusion;
	}


	Square* originalPlaceOfTestesPiece = &board->boardSquares[(int)piece->getPosition().x / 100][(int)piece->getPosition().y / 100];
	originalPlaceOfTestesPiece->ownedPiece = nullptr;

	for (Square*currSquare : pieceRange)
	{
		sf::Vector2f kingindex; 
		if (piece->type == Piece::PieceType::KING)
		{
			kingindex = sf::Vector2f(currSquare->sPos.x / 100, currSquare->sPos.y / 100);
		}
		else
		{
			kingindex = sf::Vector2f((int)ownerPlayer->King->getPosition().x / 100, (int)ownerPlayer->King->getPosition().y / 100);				
		}

		Piece* pieceincurrSquare = currSquare->ownedPiece; 

		if (pieceincurrSquare != nullptr)
		{
			pieceincurrSquare->killedTemporarely = true;
		}

		currSquare->ownedPiece = piece; 

		std::vector<Square*>PositionsEnemyCanMoveto; 
		for (int a = 0; a < otherPlayer->pieces.size(); a++)
		{
			std::vector<Square*>temp = FindPieceRange(otherPlayer->pieces[a], otherPlayer); 
			for (int b = 0; b < temp.size(); b++)
			{
				PositionsEnemyCanMoveto.push_back(temp[b]);
			}
		}

		currSquare->ownedPiece = pieceincurrSquare; 
		if (pieceincurrSquare != nullptr)
		{
			pieceincurrSquare->killedTemporarely = false;
		}

		if (std::find(PositionsEnemyCanMoveto.begin(), PositionsEnemyCanMoveto.end(), &board->boardSquares[(int)kingindex.x][(int)kingindex.y]) == PositionsEnemyCanMoveto.end())
		{
			Conclusion.push_back(currSquare);
		}
	}

	originalPlaceOfTestesPiece->ownedPiece = piece; 

	return Conclusion;

}

void Engine::StartComponents()
{	

	std::ofstream save("save.dat"); 
	save << "_NO_SAVED_DATA";
	save.close();

	board = new GameBoard; 
	board->StartGameBoard();
	
	//Setting players[0]

	Piece* piece = new Piece[8];

	for (int a = 0; a < 8; a++)
	{
		piece[a].StartPiece(sf::Vector2f(a * 100, 600), CHESS_WHITE_PION_TEXTURE_FILE,Piece::PieceType::PION,sf::Color::White,players);
		players[0].AddPiece(&piece[a]);
	}

	players->SetType(PlayerType::WHITE); 
	players[1].SetType(PlayerType::BLACK);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(0, 700), CHESS_WHITE_CASTLE_TEXTURE_FILE,Piece::PieceType::CASTLE, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(700, 700), CHESS_WHITE_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(100, 700), CHESS_WHITE_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(600, 700), CHESS_WHITE_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(200, 700), CHESS_WHITE_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(500, 700), CHESS_WHITE_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(300, 700), CHESS_WHITE_KING_TEXTURE_FILE, Piece::PieceType::KING, sf::Color::White,players);
	players[0].AddPiece(piece);

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(400, 700), CHESS_WHITE_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::White,players);
	players[0].AddPiece(piece);

	
	//Setting players[1]

	piece = new Piece[8];

	for(int a = 0;a < 8;a++)
	{
		piece[a].StartPiece(sf::Vector2f(a * 100, 100), CHESS_BLACK_PION_TEXTURE_FILE, Piece::PieceType::PION, sf::Color::Black,&players[1]);
		players[1].AddPiece(&piece[a]);
	}

	
	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(0, 0),CHESS_BLACK_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece); 

	piece = new Piece;
	piece->StartPiece(sf::Vector2f(700, 0), CHESS_BLACK_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(100, 0), CHESS_BLACK_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece); 

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(600, 0), CHESS_BLACK_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(200, 0), CHESS_BLACK_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(500, 0), CHESS_BLACK_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(300, 0), CHESS_BLACK_KING_TEXTURE_FILE, Piece::PieceType::KING, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	piece = new Piece; 
	piece->StartPiece(sf::Vector2f(400, 0), CHESS_BLACK_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::Black,&players[1]);
	players[1].AddPiece(piece);

	
	for (Player& player : players)
	{
		for (int a = 0; a < player.pieces.size(); a++)
		{
			sf::Vector2f pos = player.pieces[a]->getPosition();
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = player.pieces[a];
		}
	}
		
	gui->ChangeScreen(1);

}

void Engine::StartComponentsFromSave()
{

	std::ifstream save("save.dat");

	board = new GameBoard;
	board->StartGameBoard();

	players->SetType(PlayerType::WHITE);
	players[1].SetType(PlayerType::BLACK);

	while (save)
	{
		std::string line;
		std::getline(save, line); 

		if (Find("_NO_SAVED_DATA") || !save.is_open())
		{
			delete board; 
			board = nullptr;
			return;
		}

		if (Find("White_Pion: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos; 
			std::string in; 
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100; 
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_PION_TEXTURE_FILE, Piece::PieceType::PION, sf::Color::White, players);
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in); 
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("White_King: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_KING_TEXTURE_FILE, Piece::PieceType::KING, sf::Color::White, players);
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());

		}
		else if (Find("White_Queen: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::White, players);
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("White_Elephant: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::White, players); 
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("White_Horse: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::White, players); 
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("White_Castle: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_WHITE_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::White, players); 
			players->AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}

		//Black Pieces :

		else if (Find("Black_Pion: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_PION_TEXTURE_FILE, Piece::PieceType::PION, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("Black_King: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_KING_TEXTURE_FILE, Piece::PieceType::KING, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());

		}
		else if (Find("Black_Queen: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_QUEEN_TEXTURE_FILE, Piece::PieceType::QUEEN, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("Black_Elephant: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_ELEPHANT_TEXTURE_FILE, Piece::PieceType::ELEPHANT, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("Black_Horse: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_HORSE_TEXTURE_FILE, Piece::PieceType::HORSE, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}
		else if (Find("Black_Castle: "))
		{
			Piece* piece = new Piece;
			sf::Vector2f pos;
			std::string in;
			getline(save, in);
			pos.x = atoi(in.substr(0, 1).c_str());
			pos.y = atoi(in.substr(2, 1).c_str());
			pos.x = pos.x * 100;
			pos.y = pos.y * 100;
			piece->StartPiece(pos, CHESS_BLACK_CASTLE_TEXTURE_FILE, Piece::PieceType::CASTLE, sf::Color::Black, &players[1]);
			players[1].AddPiece(piece);
			board->boardSquares[(int)pos.x / 100][(int)pos.y / 100].ownedPiece = piece;
			getline(save, in);
			piece->firstmovement = !atoi(in.substr(7).c_str());
		}

		else if (Find("Choosed Player : "))
		{
			std::string playerType = line.substr(17); 
			if (playerType == "black")
			{
				selectedPlayer = &players[1];
			}
			else
			{
				selectedPlayer = players;
			}
		}
	}


	gui->ChangeScreen(1);
}


void Engine::RunGame()
{
	window->setFramerateLimit(60);

	while (window->isOpen())
	{
		while (window->pollEvent((*eventHolder)))
		{
			if ((*eventHolder).type == sf::Event::MouseButtonPressed)
			{
				if ((*eventHolder).mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f pos = sf::Vector2f((*eventHolder).mouseButton.x,(*eventHolder).mouseButton.y);
					GetInput(pos);
				}				
			}
			else if ((*eventHolder).type == sf::Event::Closed)
			{
				window->close();				
				return;
			}
			if ((*eventHolder).type == sf::Event::KeyPressed)
			{				
				if (eventHolder->key.code == sf::Keyboard::Escape)
				{
					gui->ChangeScreen(2);
					return;
				}

			}
		}

		window->clear(sf::Color::White); 	

		window->draw(*board); 
		for (int a = 0; a < players->pieces.size(); a++)
		{
			window->draw(*players->pieces[a]);
		}
		for (int a = 0; a < players[1].pieces.size(); a++)
		{
			window->draw(*players[1].pieces[a]);
		}

		for (int a = 0; a < PositionsInRange.size(); a++)
		{
			sf::Color color; 
			if (std::find(MovablePositions_.begin(), MovablePositions_.end(), PositionsInRange[a]) == MovablePositions_.end())
			{
				color = sf::Color::Color(255, 170, 170);
			}
			else
			{
				color = sf::Color::Color(170, 255, 170);
			}
			sf::RectangleShape shape; 
			shape.setSize(sf::Vector2f(100, 100)); 
			shape.setPosition(PositionsInRange[a]->sPos);
			shape.setFillColor(color);
			window->draw(shape,sf::BlendMultiply);		
		}

		if (pieceToBeChanged != nullptr)
		{
			for (int a = 0; a < 4; a++)
			{
				window->draw(SelectionSquares[a]);
			}
		}
		window->display();
		if (gameOver)
		{
			Sleep(1000);
			break;
		}
	}	

	if (gameOver)
	{

		std::ofstream file("save.dat"); 
		file.clear(); 
		file << "_NO_SAVED_DATA" << std::endl;
		file.close();

		static sf::Font font;
		font.loadFromFile(CHESS_ARIAL_FONT_FILE);

		std::string winner_;

		if (winner_player == nullptr)
		{
			gui->GiveScreen(3)->GiveText(1).setString("Draw");
		}

		else if (winner_player->type == PlayerType::BLACK)
		{
			gui->GiveScreen(3)->GiveText(1).setString("Black Won");
		}

		else
		{
			gui->GiveScreen(3)->GiveText(1).setString("White Won");
		}

		gui->ChangeScreen(3);

	}
}

void Engine::Quit()
{
	exit(0);
}

void Engine::ReturnMainMenu()
{
	players->pieces.clear();
	players[1].pieces.clear();
	gameOver = false;
	delete board;
	board = nullptr;
	selectedPlayer = players;
	MovablePositions_.clear(); 
	PositionsInRange.clear();

	std::ifstream file("save.dat");
	std::string line;
	getline(file, line);
	if (line == "_NO_SAVED_DATA")
	{
		gui->GiveScreen(0)->GiveButton(0)->setString("Continue (No Saved Data)"); 
	}
	else
	{
		gui->GiveScreen(0)->GiveButton(0)->setString("Continue");
	}

	gui->ChangeScreen(0);

}

void Engine::GetScreenshot()
{
}

void Engine::SaveGame()
{ 
	std::ofstream save("save.dat"); 
	for (int a = 0; a < players->pieces.size(); a++)
	{
		Piece* currPiece = players->pieces[a];
		sf::Vector2f pos = currPiece->getPosition(); 

		switch (players->pieces[a]->type)
		{
		case Piece::PieceType::PION: 
			save << "White_Pion: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		case Piece::PieceType::KING: 
			save << "White_King: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		case Piece::PieceType::QUEEN: 
			save << "White_Queen: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		case Piece::PieceType::HORSE: 
			save << "White_Horse: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		case Piece::PieceType::ELEPHANT: 
			save << "White_Elephant: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		case Piece::PieceType::CASTLE: 
			save << "White_Castle: " << std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break; 
		}
	}

	for (int a = 0; a < players[1].pieces.size(); a++)
	{
		Piece* currPiece = players[1].pieces[a];
		sf::Vector2f pos = currPiece->getPosition();

		switch (players[1].pieces[a]->type)
		{
		case Piece::PieceType::PION:
			save << "Black_Pion: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;		
		case Piece::PieceType::KING:				
			save << "Black_King: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;									  
		case Piece::PieceType::QUEEN:				  
			save << "Black_Queen: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;									  
		case Piece::PieceType::HORSE:				  
			save << "Black_Horse: "<< std::endl << pos.x / 100 << "x"  << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;
		case Piece::PieceType::ELEPHANT:
			save << "Black_Elephant: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;
		case Piece::PieceType::CASTLE:
			save << "Black_Castle: "<< std::endl << pos.x / 100 << "x" << pos.y / 100 << std::endl << "moved = " << !currPiece->firstmovement << std::endl;
			break;
		}
	}	
	
	std::string choosedPlayer; 
	if (selectedPlayer->type == PlayerType::BLACK)
		choosedPlayer = "black";
	else
		choosedPlayer = "white"; 

	save << "Choosed Player : " << choosedPlayer << std::endl;
}

Engine::Engine()
{		

	SelectionSquaresWhiteTextures[0].loadFromFile(CHESS_WHITE_QUEEN_TEXTURE_FILE);
	SelectionSquaresWhiteTextures[1].loadFromFile(CHESS_WHITE_CASTLE_TEXTURE_FILE);
	SelectionSquaresWhiteTextures[2].loadFromFile(CHESS_WHITE_ELEPHANT_TEXTURE_FILE);
	SelectionSquaresWhiteTextures[3].loadFromFile(CHESS_WHITE_HORSE_TEXTURE_FILE);

	SelectionSquaresBlackTextures[0].loadFromFile(CHESS_BLACK_QUEEN_TEXTURE_FILE);
	SelectionSquaresBlackTextures[1].loadFromFile(CHESS_BLACK_CASTLE_TEXTURE_FILE);
	SelectionSquaresBlackTextures[2].loadFromFile(CHESS_BLACK_ELEPHANT_TEXTURE_FILE);
	SelectionSquaresBlackTextures[3].loadFromFile(CHESS_BLACK_HORSE_TEXTURE_FILE);

	SelectionSquares[0].setSize(sf::Vector2f(75,75));
	SelectionSquares[1].setSize(sf::Vector2f(75,75));
	SelectionSquares[2].setSize(sf::Vector2f(75,75));
	SelectionSquares[3].setSize(sf::Vector2f(75,75)); 

	SelectionSquares[0].setOutlineColor(sf::Color::Red);
	SelectionSquares[1].setOutlineColor(sf::Color::Red);
	SelectionSquares[2].setOutlineColor(sf::Color::Red);
	SelectionSquares[3].setOutlineColor(sf::Color::Red);

	SelectionSquares[0].setOutlineThickness(4);
	SelectionSquares[1].setOutlineThickness(4);
	SelectionSquares[2].setOutlineThickness(4);
	SelectionSquares[3].setOutlineThickness(4);

	FreeConsole();
	//Starting GUI elements : 	

	window = new sf::RenderWindow(sf::VideoMode(800, 800), "Chess");
	eventHolder = new sf::Event;
	window->setFramerateLimit(30);

	gui = new GUI<Engine>(window, eventHolder); 
	sf::Color selected = sf::Color::Color(250,250,250); 
	sf::Color unselected = sf::Color::Color(40,40,40);

	Screen* mainMenu = new Screen(window,eventHolder,sf::Color::Color(15,15,15));
	Button* continueButton = new Button("Continue", selected, unselected, 50, sf::Vector2f(135, 300));
	Button* newgameButton = new Button("New Game", selected, unselected, 50, sf::Vector2f(135, 400));
	Button* clearSave = new Button("Delete Save", selected, unselected, 50, sf::Vector2f(135, 500));
	Button* quitButton = new Button("Quit", selected, unselected, 50, sf::Vector2f(135, 600));
	sf::Text GameName;
	static sf::Font font; 
	font.loadFromFile(CHESS_ARIAL_FONT_FILE);
	GameName.setString("Chess");
	GameName.setPosition(sf::Vector2f(125, 120)); 
	GameName.setCharacterSize(100); 
	GameName.setFillColor(sf::Color::Color(240, 240, 240)); 
	GameName.setFont(font); 

	std::ifstream file("save.dat");
	if (file.is_open() == false)
	{
		file.close(); 
		std::ofstream newFile("save.dat"); 
		newFile << "_NO_SAVED_DATA" << std::endl;
		newFile.close(); 
		file.open("save.dat");
	}
	std::string line; 
	getline(file, line); 

	mainMenu->AddComponent(GameName);
	mainMenu->AddComponent(continueButton);
	mainMenu->AddComponent(newgameButton);
	mainMenu->AddComponent(clearSave);
	mainMenu->AddComponent(quitButton);
	sf::Text CreatorText; 
	CreatorText.setFont(font); 
	CreatorText.setCharacterSize(15); 
	CreatorText.setString("Created by Emirhan Kotan"); 
	CreatorText.setPosition(sf::Vector2f(9, window->getSize().y - 35)); 
	CreatorText.setFillColor(sf::Color::Color(240, 240, 240));
	mainMenu->AddComponent(CreatorText);

	sf::Text LastestRelease;
	LastestRelease.setFont(font);
	LastestRelease.setCharacterSize(15);
	LastestRelease.setString("Release : 12.09.2021");
	LastestRelease.setPosition(sf::Vector2f(9, window->getSize().y - 20));
	LastestRelease.setFillColor(sf::Color::Color(240, 240, 240));
	mainMenu->AddComponent(LastestRelease);

	if (line == "_NO_SAVED_DATA")
	{
		continueButton->setString("Continue (No Saved Data)");
	}

	GameScreen<Engine>* gamescreen = new GameScreen<Engine>(this, &Engine::RunGame);

	Screen* pauseMenu = new Screen(window, eventHolder,sf::Color::Color(15,15,15)); 
	Button* returnButton = new Button("Return Game", selected, unselected, 50, sf::Vector2f(135, 200));
	Button* saveGameButton = new Button("Save", selected, unselected, 50, sf::Vector2f(135, 300));
	Button* returnToMainMenu = new Button("Return main menu", selected, unselected, 50, sf::Vector2f(135, 400));
	pauseMenu->AddComponent(returnButton);
	pauseMenu->AddComponent(saveGameButton);
	pauseMenu->AddComponent(returnToMainMenu);

	Screen* gameOverScreen = new Screen(window, eventHolder, sf::Color::Color(15, 15, 15)); 
	Button* returntomainmenuButton = new Button("Return main menu", selected, unselected, 50, sf::Vector2f(150, 500)); 
	gameOverScreen->AddComponent(returntomainmenuButton); 

	gui->BindObjects(newgameButton, this, &Engine::StartComponents); 
	gui->BindObjects(continueButton, this, &Engine::StartComponentsFromSave);
	gui->BindObjects(quitButton, this, &Engine::Quit);
	gui->BindObjects(returnButton, this, &Engine::ReturnGame);
	gui->BindObjects(returntomainmenuButton, this, &Engine::ReturnMainMenu);
	gui->BindObjects(saveGameButton, this, &Engine::SaveGame);
	gui->BindObjects(clearSave, this, &Engine::ClearSaveFile);
	gui->BindObjects(returnToMainMenu, this, &Engine::ReturnMainMenu);

	gui->AddScreen(mainMenu);	 
	gui->AddScreen(gamescreen);  
	gui->AddScreen(pauseMenu);
	gui->AddScreen(gameOverScreen);

	static sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setPosition(sf::Vector2f(150, 200));
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setCharacterSize(80);

	sf::Text winnerText;

	winnerText.setFont(font);
	winnerText.setPosition(sf::Vector2f(150, 350));
	winnerText.setFillColor(sf::Color::White);
	winnerText.setCharacterSize(80);

	gui->GiveScreen(3)->AddComponent(gameOverText);
	gui->GiveScreen(3)->AddComponent(winnerText);

}

Engine::~Engine()
{
	
}

void Engine::Display()
{
	gui->Display();
}

std::string GiveTime()
{
	char buffer[10];
	GetTimeFormatA(NULL, NULL, NULL, NULL, buffer, 10);
	return std::string(buffer);
}

std::string GiveDate()
{
	char buffer[11]; 
	GetDateFormatA(NULL, NULL, NULL, "dd.MM.yyy", buffer, 11); 
	return std::string(buffer);
}
