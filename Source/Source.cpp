/*
* Author:	Sean Orme
*			UALR
* 
* Date:		February 2, 2016	
*
* File:		Source.cpp
*
* Purpose:	This programming task examines the following concepts
*				- Abstraction of game devices (Graphics, Input) from SDL Library
*               - AssetManagement using Libraries
*               - Object Factory Design Pattern
*               - XML Construction of 2-D game system
*               - Main Game Loop
*/

#include <iostream>
#include <random>
#include <memory>

#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	//========================================
	//Construct Game
	//========================================
	std::unique_ptr<Game> game(std::make_unique<Game>());
	if(!game->Initialize())
	{
		printf( "Game could not Initialize!");
		exit(1);
	}

	//========================================
	//Load Level
	//========================================
	game->Reset();
	std::string levelConfigFile = "./Assets/Config/bomberman_level_1.map";
	std::string spritesConfigFile = "./Assets/Config/sprites.xml";
	std::string objectConfigFile = "./Assets/Config/objects.xml";
	std::string physicsConfigFile = "./Assets/Config/Physics.xml";
	std::string soundConfigFile = "./Assets/Config/sounds.xml";
	std::string musicConfigFile = "./Assets/Config/music.xml";

	if (!game->LoadResources(objectConfigFile, physicsConfigFile, spritesConfigFile, soundConfigFile, musicConfigFile))
	{
		printf("Game could not load resources");
		system("pause");
		exit(1);
	}
		if (!game->LoadLevel(levelConfigFile))
	{
		printf( "Game could not load level %s: ", levelConfigFile.c_str());
		system("pause");
		exit(1);
	}

	//========================================
	//Main Game Loop
	//========================================
	bool quit = false;

	//While the user hasn't quit
	while(!game->Run()){	}

	//========================================
	// Clean-up
	//========================================
	if(game)
	{
		game = nullptr;
	}


	return 0;

}