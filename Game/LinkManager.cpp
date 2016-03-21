#include "LinkManager.h"

LinkManager::LinkManager() {}

LinkManager::LinkManager(GameStruct* game_struct)
{
    initialize(game_struct);
}


void LinkManager::initialize(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

void LinkManager::linkRoadGuess(Road * r1, Road * connector)
{
	if (r1->getLast() == NULL)
		linkRoadLast(r1, connector);
	else if (r1->getNext() == NULL)
		linkRoadNext(r1, connector);
	else
		std::cout << "Problème HandleStartDivisions: route connector ou non libre";
}

void LinkManager::linkRoadNext(Road * r1, Road * connector)
{
	r1->setNext(connector);
	Connector* cast = dynamic_cast<Connector*>(connector);
	assert(cast != NULL);
	cast->addConnectedRoad(r1);
}

void LinkManager::linkRoadLast(Road * r1, Road * connector)
{
	r1->setLast(connector);
	Connector* cast = dynamic_cast<Connector*>(connector);
	assert(cast != NULL);
	cast->addConnectedRoad(r1);
}

void LinkManager::linkRoadNextLast(Road * r1, Road * r2)
{
	r1->setNext(r2);
	r2->setLast(r1);
}

void LinkManager::linkRoadLastLast(Road * r1, Road * r2)
{
	r1->setLast(r2);
	r2->setLast(r1);
}

void LinkManager::linkRoadNextNext(Road * r1, Road * r2)
{
	r1->setNext(r2);
	r2->setNext(r1);
}

void LinkManager::linkRoadLastNext(Road * r1, Road * r2)
{
	r1->setLast(r2);
	r2->setNext(r1);
}

void LinkManager::linkRoadCopyNext(Road * source, Road * dest)
{
	dest->setNext(source->getNext());
}

void LinkManager::linkRoadCopyLast(Road * source, Road * dest)
{
	dest->setLast(source->getLast());
}

// ----- SETTER ----- //
void LinkManager::setGameStruct(GameStruct* game_struct)
{
    this->gameStruct = game_struct;
}

void LinkManager::add(QTEntityBuild * qtEntity)
{
	gameStruct->QTCollision.insert(qtEntity);
}

void LinkManager::addRoad(QTEntity * qtEntity)
{
	gameStruct->QTCollision.insert(qtEntity);
	gameStruct->QTRoads.insert(qtEntity);
}

int LinkManager::computeRoadIndex(std::map<float, Road*> myRoad)
{
	int minIndex = -1;

	std::map<float, Road*>::iterator it = myRoad.begin();
	// On récupère si possible en premier lieu l'élément de la route juste avant
	if (it->second->getLast() != NULL)
	{
		minIndex = it->second->getLast()->getConnexitude();
	}

	// On récupère l'élémént le plus bas
	while (it != myRoad.end())
	{
		
		Connector* cast = dynamic_cast<Connector*>(it->second);
		if (cast != NULL)
		{
			for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
			{
				Road* current = cast->getConnectedRoad(i);
				if (current->getConnexitude() != -1 && (current->getConnexitude() < minIndex || minIndex == -1))
				{
					minIndex = current->getConnexitude();
				}
			}
		}
		else
		{
			if (it->second->getNext() != NULL)
			{
				if (it->second->getNext()->getConnexitude() != -1 && (it->second->getNext()->getConnexitude() < minIndex || minIndex == -1))
				{
					minIndex = it->second->getNext()->getConnexitude();
				}
			}
		}
	}

	return minIndex;
}
/*
void UpdateManager::setConnexitudeOptimized(std::map<float, Road*> myRoad, int connex)
{
	//bst
	std::set<Road*> alreadyDone;
	std::set<Road*> toDo;

	std::map<float, Road*>::iterator it = myRoad.begin();
	alreadyDone.insert(it->second);
	toDo.insert(it->second);

	if (it->second->getLast() != NULL && alreadyDone.find(it->second->getLast()) != alreadyDone.end())
	{
		set()
	}

	while (toDo.size() != 0)
	{
		Road* current = (*toDo.begin());
		toDo.erase(toDo.begin());

		current->setConnexitude(connex);
		// On ajoute les éléments encore à faire

		Connector* cast = dynamic_cast<Connector*>(current);
		if (cast != NULL)
		{
			for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
			{
				if (alreadyDone.find(cast->getConnectedRoad(i)) != alreadyDone.end())
				{
					alreadyDone.insert(cast->getConnectedRoad(i));
					toDo.insert(cast->getConnectedRoad(i));
				}
			}
		}
		else
		{


			if (current->getNext() != NULL && alreadyDone.find(current->getNext()) != alreadyDone.end())
			{
				alreadyDone.insert(current->getNext());
				toDo.insert(current->getNext());
			}
		}
	}

}*/

void LinkManager::remove(QTEntityBuild * qtEntity)
{
	gameStruct->QTCollision.erase(qtEntity);

	// On supprime aussi les avec les routes

	for (unsigned i = 0; i < qtEntity->sizeConnected(); i++)
	{
		qtEntity->getConnected(i)->erase(qtEntity);
	}

	// Après ...
}

void LinkManager::removeRoad(Road * road)
{
	gameStruct->QTCollision.erase(road);
	gameStruct->QTRoads.erase(road);

}


// Connexitude
// Récupération de l'id connex le plus haut
int LinkManager::getConnexitude()
{
	if (gameStruct->fConnexitudes.size() > 0)
	{
		int fConnex = gameStruct->fConnexitudes[gameStruct->fConnexitudes.size() - 1];
		gameStruct->fConnexitudes.pop_back();
		return fConnex;
	}

	return gameStruct->topConnexitude++;
}

void LinkManager::freeConnexitude(int n)
{
	gameStruct->fConnexitudes.push_back(n);
}

void LinkManager::recalculateAfterRemove(Road * road)
{
	// On commence par copier l'ensemble des roads connected
	std::deque<Road*> roads;

	if (road->getLast() == NULL && road->getNext() == NULL)
		freeConnexitude(road->getConnexitude());

	Connector* cast = dynamic_cast<Connector*>(road);
	if (cast != NULL)
	{
		for (unsigned i = 0; cast->sizeConnectedRoad(); i++)
		{
			roads.push_back(cast->getConnectedRoad(i));
		}
	}
	else
	{
		if (road->getLast() != NULL)
		{
			roads.push_back(road->getLast());
		}
		if (road->getNext() != NULL)
		{
			roads.push_back(road->getNext());
		}
	}

	// Au départ on crée autant de groupe qu'
	for (unsigned i = 0; i < roads.size(); i++)
	{
		for (unsigned j = i + 1; j < roads.size(); j++)
		{
			// Si on a une connection entre les 2 routes, il suffit d'enlever l'une des deux
			// On sait que lorsqu'on changera l'id connex de la premiere route on retombera sur la deuxieme
			if (stillConnected(roads[i], roads[j]))
			{
				// Suppression de la seconde route
				roads.erase(roads.begin() + j);
				j--;
			}
		}
	}

	if (roads.size() < 2) // La suppression n'a rien changé, ou plus de route
		return;

	// On laisse la topConnexitude au premier groupe d'élément
	for (unsigned i = 0; i < roads.size(); i++)
	{
		setConnexitude(roads[i], getConnexitude());
	}

	// Il reste encore à checker si les générateurs connectés sont connecter à des éléments avec un autre id
}

void LinkManager::setConnexitude(Road * start, int connex)
{

	//bst
	std::set<Road*> alreadyDone;
	std::set<Road*> toDo;

	alreadyDone.insert(start);
	toDo.insert(start);

	while (toDo.size() != 0)
	{
		Road* current = (*toDo.begin());
		toDo.erase(toDo.begin());

		current->setConnexitude(connex);
		// On ajoute les éléments encore à faire

		Connector* cast = dynamic_cast<Connector*>(current);
		if (cast != NULL)
		{
			for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
			{
				if (alreadyDone.find(cast->getConnectedRoad(i)) != alreadyDone.end())
				{
					alreadyDone.insert(cast->getConnectedRoad(i));
					toDo.insert(cast->getConnectedRoad(i));
				}
			}
		}
		else
		{
			if (current->getLast() != NULL && alreadyDone.find(current->getLast()) != alreadyDone.end())
			{
				alreadyDone.insert(current->getLast());
				toDo.insert(current->getLast());
			}

			if (current->getNext() != NULL && alreadyDone.find(current->getNext()) != alreadyDone.end())
			{
				alreadyDone.insert(current->getNext());
				toDo.insert(current->getNext());
			}
		}
	}
}

bool LinkManager::stillConnected(Road * start, Road * end)
{
	//std::set<Road*> closedList;
	std::set<Road*> openListBst;
	std::map<float, Road*> openList;
	// Initilisation
	float dist = (end->getCenter() - start->getCenter()).getMagnitude();
	openList[dist] = start;
	openListBst.insert(start);

	bool isFound = false;
	while (openList.size() != 0 && !isFound)
	{
		// On ajoute dans l'openList les éléments liés à cette road
		// On commence par regarder si c'est un connecteur ou seulement une route

		// On récupère celui avec la plus faible valeur
		Road* current = (openList.begin()->second);
		openList.erase(openList.begin());

		Connector* cast = dynamic_cast<Connector*>(current);
		if (cast != NULL)
		{
			for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
			{
				Road* adding = cast->getConnectedRoad(i);
				if (adding != end)
				{
					// Si pas déjà dans déjà traitée ou déjà prévu (openListBst)
					if (openListBst.find(adding) != openListBst.end())
					{
						dist = (end->getCenter() - adding->getCenter()).getMagnitude();
						openList[dist] = adding;
						openListBst.insert(adding);
					}
				}
				else
				{
					isFound = true;
					break;
				}
			}
		}
		else
		{
			if (current->getLast() != NULL)
			{
				Road* adding = current->getLast();
				if (adding != end)
				{
					// Si pas déjà dans déjà traitée ou déjà prévu (openListBst)
					if (openListBst.find(adding) != openListBst.end())
					{
						dist = (end->getCenter() - adding->getCenter()).getMagnitude();
						openList[dist] = adding;
						openListBst.insert(adding);
					}
				}
				else
				{
					isFound = true;
					break;
				}
			}
			if (current->getNext() != NULL)
			{
				Road* adding = current->getNext();
				if (adding != end)
				{
					// Si pas déjà dans déjà traitée ou déjà prévu (openListBst)
					if (openListBst.find(adding) != openListBst.end())
					{
						dist = (end->getCenter() - adding->getCenter()).getMagnitude();
						openList[dist] = adding;
						openListBst.insert(adding);
					}
				}
				else
				{
					isFound = true;
					break;
				}
			}
		}
	}
	return isFound;
}
