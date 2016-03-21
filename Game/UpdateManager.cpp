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

void UpdateManager::linkRoadNext(Road * r1, Road * connector)
{
	r1->setNext(connector);
	Connector* cast = dynamic_cast<Connector*>(connector);
	assert(cast != NULL);
	cast->addConnectedRoad(r1);
}

void UpdateManager::linkRoadLast(Road * r1, Road * connector)
{
	r1->setLast(connector);
	Connector* cast = dynamic_cast<Connector*>(connector);
	assert(cast != NULL);
	cast->addConnectedRoad(r1);
}

void UpdateManager::linkRoadNextLast(Road * r1, Road * r2)
{
	r1->setNext(r2);
	r2->setLast(r1);
}

void UpdateManager::linkRoadLastLast(Road * r1, Road * r2)
{
	r1->setLast(r2);
	r2->setLast(r1);
}

void UpdateManager::linkRoadNextNext(Road * r1, Road * r2)
{
	r1->setNext(r2);
	r2->setNext(r1);
}

void UpdateManager::linkRoadLastNext(Road * r1, Road * r2)
{
	r1->setLast(r2);
	r2->setNext(r1);
}

void UpdateManager::linkRoadCopyNext(Road * source, Road * dest)
{
	dest->setNext(source->getNext());
}

void UpdateManager::linkRoadCopyLast(Road * source, Road * dest)
{
	dest->setLast(source->getLast());
}

// ----- SETTER ----- //
void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    this->gameStruct = game_struct;
}

void UpdateManager::add(QTEntity * qtEntity)
{
	gameStruct->QTCollision.insert(qtEntity);
}

void UpdateManager::addRoad(QTEntity * qtEntity)
{
	gameStruct->QTCollision.insert(qtEntity);
	gameStruct->QTRoads.insert(qtEntity);
}

void UpdateManager::remove(QTEntity * qtEntity)
{
	gameStruct->QTCollision.erase(qtEntity);

	// On supprime aussi les avec les routes
	for (unsigned i = 0; i < qtEntity->sizeConnected(); i++)
	{
		qtEntity->getConnected(i)->erase(qtEntity);
	}

	// Après ...
}

void UpdateManager::removeRoad(Road * road)
{
	gameStruct->QTCollision.erase(road);
	gameStruct->QTRoads.erase(road);

}
