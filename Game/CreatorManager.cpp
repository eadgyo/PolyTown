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
	// Approximation de la direction de la route ici ou avant
	// On regarde si la route est en collision avec un autre élément qu'une route
	
	// Récupération des éléments possiblement en collision
	std::vector<QTEntity*> entities;
	std::vector<Road*> roadColliding;
	gameStruct->QTCollision.retrieve(road->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		road->getRect().isColliding()
	}


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
	assert(gameStruct != NULL);

	return LayerNs::LayerEvent();
}

void CreatorManager::removeRoad(Road * road)
{
}

void CreatorManager::addRoad(Road * road)
{
}
