#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <thread>
#include <string> 
#include <vector>
#include <fstream> 
#include "GameBoard.h"
#include "Player.h"
#include "GUI.h"
#include <windows.h>

class Engine
{
	GUI<Engine> *gui;

private :

	sf::RenderWindow* window = nullptr;
	sf::Event* eventHolder = nullptr;
	GameBoard* board = nullptr;
	Player players[2];	
	/*
	* Players[0] is the player on the above = WHITE
	* Players[1] is the player on the top = BLACK
	*/

	Player* selectedPlayer = players; 
	void GetInput(sf::Vector2f pos);
	Player* UnchoosedPlayer();	
	std::vector<Square*> FindPieceRange(Piece*piece,Player*ownerPlayer);
	std::vector<Square*> FindMovablePositions(Piece* piece, Player* ownerPlayer);
	
	//Game Over situation properties : 

	bool gameOver = false;
	Player* winner_player = nullptr;

	//Change Piece Status Properties : 

	Piece* pieceToBeChanged = nullptr; 
	Player* ownerPlayerofPiece = nullptr; 

	sf::RectangleShape SelectionSquares[4]; 
	sf::Texture SelectionSquaresWhiteTextures[4]; 
	sf::Texture SelectionSquaresBlackTextures[4];

	/*
	* index 0 = Queen,
	* index 1 = Castle,
	* index 2 = Elephant,
	* index 3 = Horse,
	*/

	std::vector<Square*> PositionsInRange;
	std::vector<Square*> MovablePositions_;

	//Game Functions : 

	void StartComponents();
	void StartComponentsFromSave();
	void RunGame();	

	//GUI Functions : 

	void ReturnGame() { gui->ChangeScreen(1); };
	void SaveGame();
	void Quit();
	void ReturnMainMenu();
	void ClearSaveFile() { std::ofstream save("save.dat"); save << "_NO_SAVED_DATA"; save.close(); gui->GiveScreen(0)->GiveButton(0)->setString("Continue (No Saved Data)"); };
	void GetScreenshot();

public : 
	Engine();
	~Engine();
	void Display();
};

std::string GiveTime(); 
std::string GiveDate();
 