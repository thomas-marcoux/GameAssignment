#include <iostream>
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
	//Load Resources
	//========================================
	game->Reset();
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

	//========================================
	//Start Game
	//========================================
	std::vector<std::string>	levels;
	levels.push_back("./Assets/Config/bomberman_level_3.map");
	levels.push_back("./Assets/Config/bomberman_level_2.map");
	levels.push_back("./Assets/Config/bomberman_level_1.map");

	game->Start(levels);
	
	//========================================
	// Clean-up
	//========================================
	if(game)
	{
		game = nullptr;
	}
	return 0;

}