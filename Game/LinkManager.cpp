#include "LinkManager.h"

LinkManager::LinkManager() {}

LinkManager::LinkManager(GameStruct* game_struct)
{
	initialize(game_struct);
}


void LinkManager::initialize(GameStruct * gs)
{
	this->gs = gs;
}

void LinkManager::linkRoad(Road * r1, Road * r2, bool isLastR1, bool isLastR2)
{
	if (isLastR1 && isLastR2)
	{
		linkRoadLastLast(r1, r2);
	}
	else if (isLastR1 && !isLastR2)
	{
		linkRoadLastNext(r1, r2);
	}
	else if (!isLastR1 && isLastR2)
	{
		linkRoadNextLast(r1, r2);
	}
	else
	{
		linkRoadNextNext(r1, r2);
	}
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

void LinkManager::linkRoadNextLastOr(Road * r1, Road * r2, Road * removing)
{
	Connector* cast = dynamic_cast<Connector*>(r2);
	if (cast != NULL)
	{
		r1->setNext(r2);
		cast->removeConnectedRoad(removing);
	}
	else
	{
		linkRoadNextLast(r1, r2);
	}
}

void LinkManager::linkRoadLastLastOr(Road * r1, Road * r2, Road * removing)
{
	Connector* cast = dynamic_cast<Connector*>(r2);
	if (cast != NULL)
	{
		r1->setLast(r2);
		cast->removeConnectedRoad(removing);
	}
	else
	{
		linkRoadLastLast(r1, r2);
	}
}

void LinkManager::linkRoadNextNextOr(Road * r1, Road * r2, Road * removing)
{
	Connector* cast = dynamic_cast<Connector*>(r2);
	if (cast != NULL)
	{
		r1->setNext(r2);
		cast->removeConnectedRoad(removing);
	}
	else
	{
		linkRoadNextNext(r1, r2);
	}
}

void LinkManager::linkRoadLastNextOr(Road * r1, Road * r2, Road * removing)
{
	Connector* cast = dynamic_cast<Connector*>(r2);
	if (cast != NULL)
	{
		r1->setLast(r2);
		cast->removeConnectedRoad(removing);
	}
	else
	{
		linkRoadLastNext(r1, r2);
	}
}

void LinkManager::linkMapRoad(std::map<float, Road*> myRoad)
{
	std::map<float, Road*>::iterator it, next;
	it = myRoad.begin();
	next = it;
	next++;
	addRoad(it->second);
	while (next != myRoad.end())
	{
		// On linke toutes les routes crées
		if (!(it->second->getIsConnector()))
			linkRoadNext(it->second, next->second);
		else
			linkRoadLast(next->second, it->second);
		addRoad(next->second); // Ajout de la route
		it++;
		next++;
	}
}


void LinkManager::linkRoadCopyNext(Road * source, Road * dest)
{
	dest->setNext(source->getNext());
}

void LinkManager::linkRoadCopyLast(Road * source, Road * dest)
{
	dest->setLast(source->getLast());
}

void LinkManager::unlinkWCleaning(Road * road, Road * connected)
{
	std::set<Road*> alreadyDone;
	alreadyDone.insert(road);
	cleanNearConnector(alreadyDone, connected);
}

// Nettoyage des connecteurs inutiles
void LinkManager::cleanNearConnector(std::set<Road*>& alreadyDone, Road * connected)
{
	if (alreadyDone.find(connected) != alreadyDone.end())
		return;
	else
		alreadyDone.insert(connected);

	// On regarde le type de la route connectée
	Connector* cast = dynamic_cast<Connector*>(connected);
	if (cast != NULL)
	{
		if (cast->sizeConnectedRoad() < 3)
		{
			// On doit supprimer le connecteur
			// Car après la deletion de l'autre route
			// On aura:
			// soit deux routes co
			// soit une seule route co
			// soit aucune co

			std::vector<Road*> copy = cast->copyConnectedRoads();
			for (unsigned i = 0; i < copy.size(); i++)
			{
				// On nettoye les autres branches
				cleanNearConnector(alreadyDone, copy[i]);
			}
		
			if (cast->sizeConnectedRoad() == 2)
			{
				
				Road* r1 = cast->getConnectedRoad(0);
				Road* r2 = cast->getConnectedRoad(1);
				assert(r1 != r2);

				Connector* cast1 = dynamic_cast<Connector*>(r1);
				Connector* cast2 = dynamic_cast<Connector*>(r2);
				if (cast1 != NULL || cast2 != NULL)
				{
					// On libère juste les deux routes
					unlinkRoad(cast, r1);
					unlinkRoad(cast, r2);
				}
				else
				{
					// On bouge les deux routes
					moveAfterCleaning(r1, cast);
					moveAfterCleaning(r2, cast);

					// On libère les deux routes en récupérant les liens
					bool isLastR1 = unlinkRoad1(r1, cast);
					bool isLastR2 = unlinkRoad1(r1, cast);

					// On lie les 2 routes en fonction des liens précédents
					linkRoad(r1, r2, isLastR1, isLastR2);
				}
			}
			else if (cast->sizeConnectedRoad() == 1)
			{
				// On doit juste supprimer le lien
				Road* r1 = cast->getConnectedRoad(0);
				unlinkRoad(cast, r1);
			}

			removeRoadLight(cast);
		}
	}
}

void LinkManager::moveAfterCleaning(Road * road, Road * removed)
{
	// On projete juste le centre de la route enlevée
	// On cherche le bon coté
	if (road->getLast() == removed)
	{
		Vector3D director = -road->getDirectorVec();
		float l_scalar = director*(removed->getCenter() - road->getStart());
		Vector3D l_start = road->getStart() + director*l_scalar;
		road->setStart(l_start);
	}
	else
	{
		Vector3D director = road->getDirectorVec();
		float l_scalar = director*(removed->getCenter() - road->getEnd());
		Vector3D l_end = road->getEnd() + director*l_scalar;
		road->setEnd(l_end);
	}
	
}

void LinkManager::unlinkRoad(Road * r1, Road * r2)
{
	r1->removeConnectedRoad(r2);
	r2->removeConnectedRoad(r1);
}

bool LinkManager::unlinkRoad1(Road * r1, Road * r2)
{
	r2->removeConnectedRoad(r1);
	return r1->removeConnectedRoad(r2);
}

// ----- SETTER ----- //
void LinkManager::setGameStruct(GameStruct* game_struct)
{
    this->gs = game_struct;
}

void LinkManager::add(QTEntityBuild * qtEntity)
{
	// Lien de la route à une habitation
	addConnectedRoad(qtEntity);
	addConsumer(qtEntity);
	addGenerator(qtEntity);

	gs->QTCollision.insert(qtEntity);
    Housing* housing = dynamic_cast<Housing*>(qtEntity);
	SocialBuilding* social = dynamic_cast<SocialBuilding*>(qtEntity);
	Factory* factory = dynamic_cast<Factory*>(qtEntity);
    if (housing)
	{
		gs->housing.push_back(housing);
    }
	else if (social)
	{
		gs->social.push_back(social);
	}
	else if (factory)
	{
        gs->factory.push_back(factory);
    }
}



void LinkManager::addRoad(Road * qtEntity)
{
	gs->QTCollision.insert(qtEntity);
	gs->QTRoads.insert(qtEntity);
	
	addConnectedEntity(qtEntity);
}

void LinkManager::addConnectedRoad(QTEntityBuild * qtEntity)
{
	// On crée un rectangle gonflé
	myRectangle rec = qtEntity->getBigRectangle(ADD_RECTANGLE);
	
	// On récupère les éléments en collision
	std::vector<QTEntity*> entities = getEntityColliding(rec, gs->QTRoads);

	// On a juste à connecter, l'élément avec toutes les routes,
	// Un jeu d'enfant
	for (unsigned i = 0; i < entities.size(); i++)
	{
		Road* cast = dynamic_cast<Road*>(entities[i]);
		cast->addEntity(qtEntity);
		qtEntity->addRoad(cast);
	}
}

void LinkManager::addConnectedEntity(Road * road)
{
	// On crée un rectangle gonflé
	myRectangle rec = road->getBigRectangle(ADD_RECTANGLE);

	// On récupère les éléments en collision
	std::vector<QTEntity*> entities = getEntityColliding(rec, gs->QTCollision);

	// On a juste à connecter, l'élément avec toutes les routes,
	// Un jeu d'enfant
	for (unsigned i = 0; i < entities.size(); i++)
	{
		QTEntityBuild* qtEntity = dynamic_cast<QTEntityBuild*>(entities[i]);
		if (qtEntity != NULL)
		{
			qtEntity->addRoad(road);
			road->addEntity(qtEntity);
		}
	}

}

void LinkManager::removeConnectedRoad(QTEntityBuild * qtEntity)
{
	// On enlève les liens
	while (qtEntity->sizeConnected() != 0)
	{
		Road* qt = qtEntity->removeRoad((unsigned) 0);
		qt->erase(qtEntity);
	}
}

void LinkManager::removeConnectedEntity(Road * road)
{
	// On enlève les liens
	while (road->sizeEnt() != 0)
	{
		QTEntity* qt = road->erase((unsigned)0);
		QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(qt);
		if (cast != NULL)
		{
			removeConsumer(cast); // Temporaire
			removeGenerator(cast);
			cast->removeRoad(road);
			addConsumer(cast); // Temporaire
			addGenerator(cast);
		}
		else
		{
			std::cout << "Un non QTEntityBuild";
			assert(false);
		}
	}
}

void LinkManager::addGenerator(QTEntityBuild * gen)
{
	// On doit déterminer si c'est un générateur eau ou elec
	PowerPlant* powerPlant = dynamic_cast<PowerPlant*>(gen);
	WaterTower* waterTower = dynamic_cast<WaterTower*>(gen);

	if (powerPlant != NULL)
	{
		addGeneratorPower(powerPlant);
	}
	else if (waterTower != NULL)
	{
		addGeneratorWater(waterTower);
	}
}

void LinkManager::addGeneratorPower(PowerPlant * gen)
{
	// On récupère les éléments qui n'ont pas d'éléctricité
	std::vector<QTEntity*> needPower = getEntityColliding(gen, gs->QTElecRes);
	
	// On essaye de les ajouter au générateur
	for (unsigned i = 0; i < needPower.size(); i++)
	{
		Energy* energy = dynamic_cast<Energy*>(needPower[i]);
		QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(needPower[i]);
		if (gen->isConnected(cast) && gen->addConsumer(needPower[i]))
		{
			gs->QTElecRes.erase(needPower[i]);
		}
	}

	// On finit par ajouter ce générateur au QT
	gs->QTElecGen.insert(gen);
}

void LinkManager::addGeneratorWater(WaterTower * gen)
{
	// On récupère les éléments qui n'ont pas d'eau
	std::vector<QTEntity*> needWater = getEntityColliding(gen, gs->QTWaterRes);

	// On essaye de les ajouter au générateur
	for (unsigned i = 0; i < needWater.size(); i++)
	{
		Water* water = dynamic_cast<Water*>(needWater[i]);
		QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(needWater[i]);
		if (gen->isConnected(cast) && gen->addConsumer(needWater[i]))
		{
			gs->QTWaterRes.erase(needWater[i]);
		}
	}

	// On finit par ajouter ce générateur au QT
	gs->QTWaterGen.insert(gen);
}

void LinkManager::addConsumer(QTEntityBuild * cons)
{
	addConsumerPower(cons);
	addConsumerWater(cons);
}


void LinkManager::addConsumerPower(QTEntityBuild * cons)
{
	Energy * cast = dynamic_cast<Energy*>(cons);
	if (cast != NULL)
	{
		// On commence par récupérer les générateurs d'électricité
		std::vector<Resources*> genPower = getGenColliding(cons, gs->QTElecGen);

		unsigned i = 0;
		while (i < genPower.size() && !cast->hasEnergy())
		{
			// Essayer de s'ajouter au générateur
			if (genPower[i]->isConnected(cons))
			{
				genPower[i]->addConsumer(cons);
			}
			i++;
		}

		// On a pas trouvé de générateur, il faut donc l'ajouter dans le bon QT
		if (!cast->hasEnergy())
		{
			gs->QTElecRes.insert(cons);
		}
	}
}

void LinkManager::addConsumerWater(QTEntityBuild * cons)
{
	Water * cast = dynamic_cast<Water*>(cons);
	if (cast != NULL)
	{
		// On commence par récupérer les générateurs d'électricité
		std::vector<Resources*> genWater = getGenColliding(cons, gs->QTWaterGen);

		unsigned i = 0;
		while (i < genWater.size() && !cast->hasWater())
		{
			// Essayer de s'ajouter au générateur
			if (genWater[i]->isConnected(cons))
			{
				genWater[i]->addConsumer(cons);
			}
			i++;
		}

		// On a pas trouvé de générateur, il faut donc l'ajouter dans le bon QT
		if (!cast->hasWater())
		{
			gs->QTWaterRes.insert(cons);
		}
	}
}

void LinkManager::removeConsumer(QTEntityBuild * cons)
{
	Energy * energy = dynamic_cast<Energy*>(cons);
	Water* water = dynamic_cast<Water*>(cons);

	if (energy != NULL)
	{
		if (!energy->hasEnergy())
		{
			gs->QTElecRes.erase(cons);
		}
		else
		{
			energy->getPowerPlant()->eraseCons(cons);
		}
	}

	if (water != NULL)
	{
		if (!water->hasWater())
		{
			gs->QTElecRes.erase(cons);
		}
		else
		{
			water->getWaterTower()->eraseCons(cons);
		}
	}
}

void LinkManager::removeGenerator(QTEntityBuild * gen)
{
	// On doit déterminer si c'est un générateur eau ou elec
	PowerPlant* powerPlant = dynamic_cast<PowerPlant*>(gen);
	WaterTower* waterTower = dynamic_cast<WaterTower*>(gen);

	if (powerPlant != NULL)
	{
		gs->QTElecGen.erase(powerPlant);
		while(powerPlant->sizeConnectedCons() != 0)
		{
			Energy* energy = dynamic_cast<Energy*>(powerPlant->getConnectedCons(0));
			energy->setPowerPlant(NULL);
			addConsumerPower(dynamic_cast<QTEntityBuild*>(powerPlant->getConnectedCons(0)));
			powerPlant->eraseCons((unsigned) 0);
		}
	}
	if (waterTower != NULL)
	{
		gs->QTWaterGen.erase(waterTower);
		while (waterTower->sizeConnectedCons() != 0)
		{
			Water* water = dynamic_cast<Water*>(waterTower->getConnectedCons(0));
			water->setWaterTower(NULL);
			addConsumerPower(dynamic_cast<QTEntityBuild*>(waterTower->getConnectedCons(0)));
			waterTower->eraseCons((unsigned)0);
		}
	}
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

		it++;
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
	gs->QTCollision.erase(qtEntity);

	// On supprime aussi les avec les routes
	removeConnectedRoad(qtEntity);

	removeConsumer(qtEntity);
	removeGenerator(qtEntity);

	Housing* housing = dynamic_cast<Housing*>(qtEntity);
	SocialBuilding* social = dynamic_cast<SocialBuilding*>(qtEntity);
	Factory* factory = dynamic_cast<Factory*>(qtEntity);
	if (housing)
	{
		unsigned i = 0;
		while (i < gs->housing.size() && gs->housing[i] != housing)
		{
			i++;
		}
		if(i < gs->housing.size())
			gs->housing.erase(gs->housing.begin() + i);
	}
	else if (social)
	{
		unsigned i = 0;
		while (i < gs->social.size() && gs->social[i] != social)
		{
			i++;
		}
		if (i < gs->social.size())
			gs->social.erase(gs->social.begin() + i);
	}
	else if (factory)
	{
		unsigned i = 0;
		while (i < gs->factory.size() && gs->factory[i] != factory)
		{
			i++;
		}
		if (i < gs->factory.size())
			gs->factory.erase(gs->factory.begin() + i);
	}
}

void LinkManager::removeRoad(Road * road)
{
	
	
	// Enlève les liens
	Connector* cast = dynamic_cast<Connector*>(road);
	if (cast == NULL)
	{
		// C'est juste une route
		if (road->getLast() != NULL)
		{
			unlinkWCleaning(road, road->getLast());
			unlinkRoad(road, road->getLast());
		}
		if (road->getNext() != NULL)
		{
			unlinkWCleaning(road, road->getNext());
			unlinkRoad(road, road->getNext());
		}
	}
	else
	{
		for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
		{
			unlinkWCleaning(cast, cast->getConnectedRoad(i));
			unlinkRoad(cast, cast->getConnectedRoad(i));
		}
	}

	removeRoadLight(road);
}

void LinkManager::removeRoadLight(Road * road)
{
	// Suppression dans GameStruct
	gs->QTCollision.erase(road);
	gs->QTRoads.erase(road);

	removeConnectedEntity(road);
}




// Connexitude
// Récupération de l'id connex le plus haut
int LinkManager::getConnexitude()
{
	if (gs->fConnexitudes.size() > 0)
	{
		int fConnex = gs->fConnexitudes[gs->fConnexitudes.size() - 1];
		gs->fConnexitudes.pop_back();
		return fConnex;
	}

	return gs->topConnexitude++;
}

void LinkManager::freeConnexitude(int n)
{
	gs->fConnexitudes.push_back(n);
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

	//Temp
	std::set<QTEntity*> add;

	alreadyDone.insert(start);
	toDo.insert(start);

	while (toDo.size() != 0)
	{
		Road* current = (*toDo.begin());
		toDo.erase(toDo.begin());
		current->fillEntConnected(add);
		current->setConnexitude(connex);
		// On ajoute les éléments encore à faire

		Connector* cast = dynamic_cast<Connector*>(current);
		if (cast != NULL)
		{
			for (unsigned i = 0; i < cast->sizeConnectedRoad(); i++)
			{
				if (alreadyDone.find(cast->getConnectedRoad(i)) == alreadyDone.end())
				{
					alreadyDone.insert(cast->getConnectedRoad(i));
					toDo.insert(cast->getConnectedRoad(i));
				}
			}
		}
		else
		{
			if (current->getLast() != NULL && alreadyDone.find(current->getLast()) == alreadyDone.end())
			{
				alreadyDone.insert(current->getLast());
				toDo.insert(current->getLast());
			}

			if (current->getNext() != NULL && alreadyDone.find(current->getNext()) == alreadyDone.end())
			{
				alreadyDone.insert(current->getNext());
				toDo.insert(current->getNext());
			}
		}
	}

	// temp
	std::set<QTEntity*>::iterator it = add.begin();
	while (it != add.end())
	{
		QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(*it);
		removeConsumer(cast);
		removeGenerator(cast);
		addConsumer(cast);
		addGenerator(cast);
		it++;
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


std::vector<QTEntity*> LinkManager::getEntityColliding(Resources* res, QuadTree& quadTree)
{
	std::vector<QTEntity*> entities;
	std::vector<QTEntity*> colliding;
	quadTree.retrieve(res->getBoundsCover(), entities);
	// On verifie si l'élément est pas trop loin
	// Le plus simple est de faire la différence avec le centre
	for (unsigned i = 0; i < entities.size(); i++)
	{
		if ((entities[i]->getCenter() - res->getCenter()).getMagnitude() < res->getRadius())
		{
			colliding.push_back(entities[i]);
		}
	}
	return colliding;
}

std::vector<QTEntity*> LinkManager::getEntityColliding(Form& form, QuadTree& quadTree)
{
	std::vector<QTEntity*> entities;
	std::vector<QTEntity*> colliding;
	quadTree.retrieve(form.getBound(), entities);

	for (unsigned i = 0; i < entities.size(); i++)
	{
		if (form.isColliding(*(entities[i]->getForm())))
		{
			colliding.push_back(entities[i]);
		}
	}
	return colliding;
}

std::vector<Resources*> LinkManager::getGenColliding(QTEntity* qtEntity, QuadTreeSpecial & quadTree)
{
	std::vector<Resources*> entities;
	std::vector<Resources*> colliding;
	quadTree.retrieve(qtEntity->getBounds(), entities);

	for (unsigned i = 0; i < entities.size(); i++)
	{
		if ((entities[i]->getCenter() - qtEntity->getCenter()).getMagnitude() < entities[i]->getRadius())
		{
			colliding.push_back(entities[i]);
		}
	}
	return colliding;
}
