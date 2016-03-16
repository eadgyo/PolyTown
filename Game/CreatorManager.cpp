#include "CreatorManager.h"



CreatorManager::CreatorManager()
{
	gameStruct = NULL;
}

CreatorManager::~CreatorManager()
{
	gameStruct = NULL;
}

void CreatorManager::initialize(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

void CreatorManager::setGameStruct(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

bool CreatorManager::isMakableRoad(Road * road)
{
	return false;
}

bool CreatorManager::isMakable(QTEntity * qtEntity)
{
	return false;
}


void CreatorManager::remove(QTEntity * qtEntity)
{
}

void CreatorManager::add(QTEntity * qtEntity)
{
}

void CreatorManager::render(Graphics * g, const Vector3D translation)
{
}

LayerNs::LayerEvent CreatorManager::handleEvent(Input & input)
{
	return LayerNs::LayerEvent();
}

void CreatorManager::removeRoad(Road * road)
{
}

void CreatorManager::addRoad(Road * road)
{
}
