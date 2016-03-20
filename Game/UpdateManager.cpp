#include "UpdateManager.h"

UpdateManager::UpdateManager() {}

UpdateManager::UpdateManager(GameStruct* game_struct)
{
    setGameStruct(game_struct);
}


void UpdateManager::initialize(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

void UpdateManager::linkRoadGuess(Road * r1, Road * connector)
{
	if (r1->getLast() == NULL)
		linkRoadLast(r1, connector);
	else if (r1->getNext() == NULL)
		linkRoadNext(r1, connector);
	else
		std::cout << "Problème HandleStartDivisions: route connector ou non libre";
}

// ----- SETTER ----- //
void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    this->gameStruct = game_struct;
}
