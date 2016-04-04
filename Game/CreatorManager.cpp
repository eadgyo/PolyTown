#include "CreatorManager.h"

//--- A faire
//--> Gestion ajout Connector lors du Add
//--> Gestion snapp sur un Connector


CreatorManager::CreatorManager()
{
	gs = NULL;
}

CreatorManager::~CreatorManager()
{
}

void CreatorManager::initialize(GameStruct * gs, LinkManager* linkManager)
{
	this->gs = gs;
	this->linkManager = linkManager;
}


bool CreatorManager::addRoad(Road * road)
{
	CRoadStruct cRoadStruct;
	if (!isMakableSnappRoad(road, cRoadStruct))
		return false;

	std::map<float, Road*> myRoad;
	myRoad[FLT_MAX] = road;
	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	Vector3D director = (end - start).getNormalize();
	float width = road->getWidth();
	float theta = road->getAngle2D();

	handleAllMid(cRoadStruct, myRoad, start, director, width, theta);
	
	// On lie tous les bouts de routes
	linkManager->linkMapRoad(myRoad);
	
	handleAllStart(cRoadStruct, myRoad.begin()->second);
	handleAllEnd(cRoadStruct, (--myRoad.end())->second);

	// On recherche le plus petit index
	int minIndex = linkManager->computeRoadIndex(myRoad);
	if (minIndex == -1)
	{
		minIndex = linkManager->getConnexitude();
	}

	// Nous pourrions utiliser un modèle optimisé
	linkManager->setConnexitude(myRoad.begin()->second, minIndex);
	return true;
}

bool CreatorManager::add(QTEntityBuild* qtEntity)
{
	if (isMakableSnapp(qtEntity))
	{
		linkManager->add(qtEntity);
		return true;
	}
	return false;
}

bool CreatorManager::isMakable(QTEntity* qtEntity)
{
	if (!isInside(qtEntity))
		return false;

	// Il ne faut aucune collision
	// Vu qu'on a pas le droit de bouger l'élément
	std::vector<QTEntity*> collidings;
	getColliding(qtEntity, collidings);
	return (collidings.size() == 0);
}

void CreatorManager::removeRoad(Road * road)
{
	linkManager->removeRoad(road);
}

void CreatorManager::remove(QTEntityBuild * qtEntity)
{
	linkManager->remove(qtEntity);
}

bool CreatorManager::isMakableSnappRoad(Road * road)
{
	CRoadStruct cRoadStrcut;
	return isMakableSnappRoad(road, cRoadStrcut);
}

bool CreatorManager::isMakableSnappRoad(Road * road, CRoadStruct& cRoadStrcut)
{
	if (!isInside(road))
		return false;

	// Si y un élément non route en collision -> échec
	std::vector<QTEntity*> entities;
	getColliding(road, entities);
	
	if (entities.size() == 0)
		return true;

	for (unsigned i = 0; i < entities.size(); i++)
	{
		Road* cast = dynamic_cast<Road*>(entities[i]);
		if (cast == NULL)
			return false;
	}

	// Clear
	cRoadStrcut.clear();

	// Save
	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	
	CRoadStruct cRoadStruct1;

	Vector3D director = road->getDirectorVec();
	float width = road->getWidth();
	
	// On commencer par regarder si c'est faisable
	// Ensuite on tante de bouger
	// Si le mouvement marche pas on revient en arrière
	if (!isCorrect(road, cRoadStrcut))
		return false;

	// Sauvegarde de cRoadStruct1 -> si on doit revenir en arrière
	if (!moveStart(road, -director, width, end, cRoadStrcut) || !isCorrect(road, cRoadStruct1) || !verifyAfterCorrection(road, cRoadStrcut.getAll()))
	{
		// On revient en arrière, snapp pas possible
		road->set2points(start, end, width);
	}
	else
	{
		// Sauvegarde du nouveau start
		cRoadStrcut.set(cRoadStruct1);
		start = road->getStart();
	}
	cRoadStruct1.clear();

	// Copie
	if (!moveEnd(road, director, width, start, cRoadStrcut) || !isCorrect(road, cRoadStruct1) || !verifyAfterCorrection(road, cRoadStrcut.getAll()))
	{
		// On revient en arrière, snapp pas possible
		road->set2points(start, end, width);
	}
	else
	{
		// Sauvegarde de l'état
		cRoadStrcut.set(cRoadStruct1);
		start = road->getStart();
	}
	cRoadStruct1.clear();

	// Snapp ou pas, on peut poser la route
	return true;
}

bool CreatorManager::isMakableSnapp(QTEntity* qtEntity)
{
	if (!isInside(qtEntity))
		return false;

	// Mauvaise initialisation de qtEntity
	assert(qtEntity->getForm() != NULL);
	Vector3D pos = qtEntity->getCenter();
	float thetaSave = qtEntity->getAngle2D();
	std::vector<QTEntity*> colliding;
	Vector3D push;
	float t;

	// On récupère les éléments dans le cercle comprenant tous les points
	// Le cercle est transformé en rectangle pour supporter le QuadTree
	// Pourquoi un cercle et pas un simple rectangle getBound ?
	// On va faire des rotations, donc il faut être sur qu'on a tous les objets possiblement en collision
	//gs->QTCollision.retrieve(qtEntity->getBoundsMax(), colliding);

	// Parmis tous les objets en collision, on cherche l'élément qui est le plus en collision
	colliding.clear();
	QTEntity* nearEntity = getCollidingPushMax(qtEntity, colliding, push, t);
	// On tante une rotation puis une translation
	if(nearEntity != NULL)
	{
		float theta = nearEntity->getAngle2D();
		if ((abs(theta - PI/2) > 0.001f) && (abs(theta + PI/2) > 0.001f))
		{
			qtEntity->setRadians(theta);
			
			
			Vector3D l_push;
			float l_t;
			std::vector<QTEntity*> l_colliding;
			// On calcule le vecteur de poussée avec la nouvelle rotation
			
			getCollidingPushMax(qtEntity, l_colliding, l_push, l_t);
			unsigned i = 0;
			while (l_colliding.size() != 0 && i < MAX_TRY_SNAPP_QTENTITY)
			{
				qtEntity->translate(l_push*1.01f);

				l_colliding.clear();
				getCollidingStop(qtEntity, l_colliding, l_push);
				
				i++;
			}

			// On reteste la collision
			if (l_colliding.size() != 0)
			{
				// La rotation + translation a crée au moins une autre collision
				// On revient en arrière
				qtEntity->setRadians(thetaSave);
				qtEntity->setCenter(pos);
			}
			else
			{
				colliding.clear();
			}
		}

		unsigned numberOfTry = 0;
		while (colliding.size() != 0 && numberOfTry < MAX_TRY_SNAPP_QTENTITY)
		{
			qtEntity->translate(push*1.01f);

			colliding.clear();
			getCollidingStop(qtEntity, colliding, push);
			
			numberOfTry++;
		}
		
		colliding.clear();
		getColliding(qtEntity, colliding, push);
		
		if (colliding.size() != 0 || !(gs->QTCollision.isValid(qtEntity->getBounds())) || (qtEntity->getCenter() - pos).getMagnitude() > DISTANCE_MAX_SNAPP)
		{
			// Si pas satisfait, on revient à la pos de départ
			qtEntity->setRadians(thetaSave);
			qtEntity->setCenter(pos);
			return false;
		}

		return true;
	}

	return true;
	
	
}


void CreatorManager::getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding)
{
	// Mauvaise initialisation de qtEntity
	assert(qtEntity->getForm() != NULL);
	std::vector<QTEntity*> possibleCollisions;
	gs->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);

	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		if (qtEntity->isColliding(*(possibleCollisions[i])))
		{
			// Collision directe entre les deux formes
			colliding.push_back(possibleCollisions[i]);
		}
	}
}

void CreatorManager::getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push)
{
	push.set(0, 0, 0, 0);
	assert(qtEntity->getForm() != NULL);
	std::vector<QTEntity*> possibleCollisions;
	gs->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);
	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		Vector3D l_push(0,0,0,false);
		float t = 0;

		if (qtEntity->isColliding(*(possibleCollisions[i]), l_push, t))
		{
			// Collision directe entre les deux formes
			colliding.push_back(possibleCollisions[i]);

			// On ajoute le vecteur de poussé au vecteur globale
			push += l_push*t;
		}
	}
}

void CreatorManager::getCollidingStop(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push)
{
	push.set(0, 0, 0, 0);
	assert(qtEntity->getForm() != NULL);
	std::vector<QTEntity*> possibleCollisions;
	gs->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);
	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		Vector3D l_push(0, 0, 0, false);
		float t = 0;

		if (qtEntity->isColliding(*(possibleCollisions[i]), l_push, t))
		{
			// Collision directe entre les deux formes
			colliding.push_back(possibleCollisions[i]);

			// On ajoute le vecteur de poussé au vecteur globale
			push = l_push*t;
			return;
		}
	}
}

QTEntity* CreatorManager::getCollidingPushMax(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push, float& t_max)
{
	push.set(0, 0, 0, 0);
	assert(qtEntity->getForm() != NULL);
	std::vector<QTEntity*> possibleCollisions;
	gs->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);
	
	QTEntity* maxColliding = NULL;
	t_max = FLT_MIN;
	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		Vector3D l_push(0, 0, 0, false);
		float t = 0;
		if (qtEntity->isColliding(*(possibleCollisions[i]), l_push, t))
		{
			// Collision directe entre les deux formes
			colliding.push_back(possibleCollisions[i]);

			// On cherche l'entité avec la force de poussée max
			if (abs(t) > abs(t_max))
			{
				t_max = t;
				maxColliding = possibleCollisions[i];
				push = l_push*t;
			}
		}
	}

	return maxColliding;
}

// Handle pour l'ajouts
void CreatorManager::handleAllStart(CRoadStruct& cRoadStruct, Road* startR)
{
	for (unsigned i = 0; i < cRoadStruct.startRoads0.size(); i++)
	{
		std::map<float, Road*> l_road;
		Road* road = cRoadStruct.startRoads0[i];
		Vector3D l_start = road->getStart();
		Vector3D l_end = road->getEnd();
		float theta = road->getAngle2D();
		float width = road->getWidth();
		Vector3D l_director = road->getDirectorVec();
		l_road[FLT_MAX] = road;
		linkManager->removeRoadLight(road);

		Road* actualRoad = NULL;
		Road* connector = createConnectorFromMap(actualRoad, startR, l_road, l_start, -l_director, width, theta);
		handleStartDivision(startR, actualRoad, connector, false);

		// On copie les anciens liens
		linkManager->linkRoadReplaceLast(road, l_road.begin()->second);
		linkManager->linkRoadReplaceNext(road, (--l_road.end())->second);
		
		linkManager->linkMapRoad(l_road);

		linkManager->linkRoadLast(startR, connector);
	}

	// Pour le moment pas de gestion de collision avec d'autres connecteurs
	for (unsigned i = 0; i < cRoadStruct.startRoads1.size(); i++)
	{
		// Connexion debut/début
		if (cRoadStruct.startRoads1[i]->getLast() != NULL)
		{
			// Déjà connectée
			// Creation d'un connecteur
			Connector* connector = createConnector(cRoadStruct.startRoads1[i], true);
			// Puis connexion
			linkManager->linkRoadLast(startR, connector);

			Vector3D director1 = startR->getDirectorVec()*1.0f;
			Vector3D start1 = startR->getEnd();
			float scalar1 = scalarColl(start1, director1, connector);
			Vector3D l_p1 = director1*(scalar1 - connector->getWidth()*0.5f) + start1;
			//startR->setStart(l_p1);
		}
		else
		{
			linkManager->linkRoadLastLast(startR, cRoadStruct.startRoads1[i]);
		}
	}

	for (unsigned i = 0; i < cRoadStruct.startRoads2.size(); i++)
	{
		// Connexion debut/fin
		if (cRoadStruct.startRoads2[i]->getNext() != NULL)
		{
			// Déjà connectée
			// Creation d'un connecteur
			Connector* connector = createConnector(cRoadStruct.startRoads2[i], false);
			// Puis connexion
			linkManager->linkRoadLast(startR, connector);

			Vector3D director1 = startR->getDirectorVec()*1.0f;
			Vector3D start1 = startR->getEnd();
			float scalar1 = scalarColl(start1, director1, connector);
			Vector3D l_p1 = director1*(scalar1 - connector->getWidth()*0.5f) + start1;
			//startR->setStart(l_p1);
		}
		else
		{
			linkManager->linkRoadLastNext(startR, cRoadStruct.startRoads2[i]);
		}
	}

	for (unsigned i = 0; i < cRoadStruct.startConnector.size(); i++)
	{
		// Connexion debut
		linkManager->linkRoadLast(startR, cRoadStruct.startConnector[i]);
	}
}

void CreatorManager::handleAllEnd(CRoadStruct& cRoadStruct, Road* endR)
{
	for (unsigned i = 0; i < cRoadStruct.endRoads0.size(); i++)
	{
		std::map<float, Road*> l_road;
		Road* road = cRoadStruct.endRoads0[i];
		Vector3D l_start = road->getStart();
		Vector3D l_end = road->getEnd();
		float theta = road->getAngle2D();
		float width = road->getWidth();
		Vector3D director = road->getDirectorVec();
		l_road[FLT_MAX] = road;

		linkManager->removeRoadLight(road);

		Road* actualRoad = NULL;
		Road* connector = createConnectorFromMap(actualRoad, endR, l_road, l_start, -director, width, theta);
		handleEndDivision(endR, actualRoad, connector, false);

		// On copie les anciens liens		
		linkManager->linkMapRoad(l_road);
		linkManager->linkRoadNext(endR, connector);

		linkManager->linkRoadReplaceLast(road, l_road.begin()->second);
		linkManager->linkRoadReplaceNext(road, (--(l_road.end()))->second);
	}

	// Pour le moment pas de gestion de collision avec d'autres connecteurs
	for (unsigned i = 0; i < cRoadStruct.endRoads1.size(); i++)
	{
		// Connexion fin/début
		if (cRoadStruct.endRoads1[i]->getLast() != NULL)
		{
			// Déjà connectée
			// Creation d'un connecteur
			Connector* connector = createConnector(cRoadStruct.endRoads1[i], true);
			// Puis connexion
			linkManager->linkRoadNext(endR, connector);

			Vector3D director1 = endR->getDirectorVec()*-1.0f;
			Vector3D start1 = endR->getStart();
			float scalar1 = scalarColl(start1, director1, connector);
			Vector3D l_p1 = director1*(scalar1 - connector->getWidth()*0.5f) + start1;
			//endR->setEnd(l_p1);
		}
		else
		{
			linkManager->linkRoadNextLast(endR, cRoadStruct.endRoads1[i]);
		}
	}

	for (unsigned i = 0; i < cRoadStruct.endRoads2.size(); i++)
	{
		// Connexion fin/fin
		if (cRoadStruct.endRoads2[i]->getNext() != NULL)
		{
			// Déjà connectée
			// Creation d'un connecteur
			Connector* connector = createConnector(cRoadStruct.endRoads2[i], false);
			// Puis connexion
			linkManager->linkRoadNext(endR, connector);

			Vector3D director1 = endR->getDirectorVec()*-1.0f;
			Vector3D start1 = endR->getStart();
			float scalar1 = scalarColl(start1, director1, connector);
			Vector3D l_p1 = director1*(scalar1 - connector->getWidth()*0.5f) + start1;
			//endR->setEnd(l_p1);
		}
		else
		{
			linkManager->linkRoadNextNext(endR, cRoadStruct.endRoads2[i]);
		}
	}

	for (unsigned i = 0; i < cRoadStruct.endConnector.size(); i++)
	{
		// Connexion debut
		linkManager->linkRoadNext(endR, cRoadStruct.endConnector[i]);
	}
}



void CreatorManager::handleAllMid(CRoadStruct& cRoadStruct, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director, float width, float theta)
{
	for (unsigned i = 0; i < cRoadStruct.midRoads0.size(); i++)
	{
		Road* actualRoad = NULL;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads0[i], myRoad, start, director, width, theta);
		handleDoubleDivision(actualRoad, cRoadStruct.midRoads0[i], connector, true);
		//linkManager->removeRoadLight(actualRoad);
	}
	for (unsigned i = 0; i < cRoadStruct.midRoads1.size(); i++)
	{
		Road* actualRoad = NULL;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads1[i], myRoad, start, director, width, theta);
		handleEndDivision(actualRoad, cRoadStruct.midRoads1[i], connector, true);
	}
	for (unsigned i = 0; i < cRoadStruct.midRoads2.size(); i++)
	{
		Road* actualRoad = NULL;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads2[i], myRoad, start, director, width, theta);
		handleStartDivision(actualRoad, cRoadStruct.midRoads2[i], connector, true);
	}
}

Road* CreatorManager::createConnectorFromMap(Road*& actualRoad, Road* roadi, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director,
	float width, float theta)
{
	float scalar = scalarColl(start, director, roadi);

	// Récupération de actualRoad
	std::map<float, Road*>::iterator iter = myRoad.lower_bound(scalar);

	// Probleme la route a été mal crée
	assert(iter != myRoad.end());
	actualRoad = iter->second;
	Road* connector = divide(actualRoad, myRoad, scalar, start, director, width, roadi->getWidth(), theta);
	myRoad.erase(iter);
	return connector;
}

bool CreatorManager::verifyAfterCorrection(Road* road, std::set<Road*> roadsConnected)
{
	std::vector<QTEntity*> colliding;
	getColliding(road, colliding);

	for (unsigned i = 0; i < colliding.size(); i++)
	{
		Road* cast = dynamic_cast<Road*>(colliding[i]);
		if (cast == NULL || roadsConnected.find(cast) == roadsConnected.end())
		{
			return false;
		}
	}
	return true;
}

Connector* CreatorManager::createConnector(Road* r1, bool isLast)
{
	Road* r2;
	if (isLast)
		r2 = r1->getLast();
	else
		r2 = r1->getNext();

	// On regarde si r2 n'est pas déjà un connecteur
	Connector* cast = dynamic_cast<Connector*>(r2);
	
	if (cast != NULL)
		return cast;
	
	bool isLastR2 = (r2->getLast() == r1);
	
	Vector3D v1 = (isLast ? r1->getStart() : r1->getEnd());
	Vector3D v2 = (isLastR2 ? r2->getStart() : r2->getEnd());

	Vector3D center = (v1 + v2)*0.5f;
	
	float width = max(r1->getWidth(), r2->getWidth());
	Connector* connector = new Connector(center, width, width);

	// On raccourcit les deux routes
	Vector3D director1 = r1->getDirectorVec() * (isLast ? 1.0f : -1.0f);
	Vector3D director2 = r2->getDirectorVec() * (isLastR2 ? 1.0f : -1.0f);
	Vector3D start1 = (!isLast ? r1->getStart() : r1->getEnd());
	Vector3D start2 = (!isLastR2 ? r2->getStart() : r2->getEnd());
	float scalar1 = scalarColl(start1, director1, connector);
	float scalar2 = scalarColl(start2, director2, connector);
	Vector3D l_p1 = director1*(scalar1 - width*0.5f) + start1;
	Vector3D l_p2 = director2*(scalar2 - width*0.5f) + start2;

	// Et on déconnecte puis connecte avec le connecteur
	linkManager->unlinkRoad(r1, r2);
	if (isLast)
	{
		r1->setStart(l_p1);
		linkManager->linkRoadLast(r1, connector);
	}
	else
	{
		r1->setEnd(l_p1);
		linkManager->linkRoadNext(r1, connector);
	}

	if (isLastR2)
	{
		r2->setStart(l_p2);
		linkManager->linkRoadLast(r2, connector);
	}
	else
	{
		r2->setEnd(l_p2);
		linkManager->linkRoadNext(r2, connector);
	}

	// On ajoute le connecteur
	connector->setConnexitude(r1->getConnexitude());
	linkManager->addRoad(connector);

	return connector;
}

// Add road functions
void CreatorManager::handleStartDivision(Road* actualRoad, Road* colliding, Road* connector, bool link)
{
	Vector3D director = -colliding->getDirectorVec();
	Vector3D l_start = colliding->getCenter();

	float min = scalarColl(l_start, director, actualRoad);

	Vector3D start = director*min;
	Vector3D end = colliding->getEnd();
	float width = colliding->getWidth();

	colliding->set2points(start, end, width);

	if (link)
		linkManager->linkRoadGuess(colliding, connector);
}

void CreatorManager::handleEndDivision(Road* actualRoad, Road* colliding, Road* connector, bool link)
{
	Vector3D director = colliding->getDirectorVec();
	Vector3D l_end = colliding->getCenter();

	float min = scalarColl(l_end, director, actualRoad);

	Vector3D start = colliding->getStart();
	Vector3D end = director*min;
	float width = colliding->getWidth();

	colliding->set2points(start, end, width);

	if (link)
		linkManager->linkRoadGuess(colliding, connector);
}

void CreatorManager::handleDoubleDivision(Road* actualRoad, Road* colliding, Road* connector, bool removeAdd)
{
	Vector3D director = colliding->getDirectorVec();
	Vector3D start = colliding->getStart();
	Vector3D end = colliding->getEnd();
	Vector3D center = colliding->getCenter();
	float width = colliding->getWidth();

	float scalarCollision = scalarColl(start, director, actualRoad);
	float maxStart = scalarCollision + width*0.5f;
	float minEnd = scalarCollision - width*0.5f;

	Vector3D end1 = start + director*maxStart;
	Vector3D start2 = start + director*minEnd;

	Road* road1 = Road::create2pointsP(start, end1, width);
	Road* road2 = Road::create2pointsP(start2, end, width);

	road1->setConnexitude(colliding->getConnexitude());
	road2->setConnexitude(colliding->getConnexitude());

	Vector3D test0 = road1->getStart();
	Vector3D test1 = road1->getEnd();

	// Ne fonctionne uniquement avec les routes différents que les connecteurs
	Road* last = colliding->getLast();
	Road* next = colliding->getNext();
	
	// A verifier que c'est le bon sens

	///-----------------------------------------------------------------
	/// --- BUG possible, peut être un échange de routes ---------------
	/// ----------------------------------------------------------------

	if (removeAdd)
	{
		linkManager->removeRoadLight(colliding);
		linkManager->addRoad(road1);
		linkManager->addRoad(road2);
	}

	if (last != NULL)
	{
		linkManager->linkRoadLastNextOr(road1, last, colliding);
	}
	linkManager->linkRoadNext(road1, connector);
	linkManager->linkRoadLast(road2, connector);
	
	if (next != NULL)
	{
		linkManager->linkRoadNextLastOr(road2, next, colliding);
	}
}

Road* CreatorManager::divide(Road* actual, std::map<float, Road*>& myRoad, float scalar,
	const Vector3D& start, const Vector3D& director, float width, float width2, float theta)
{
	// Création des points pour la route
	Vector3D p1 = actual->getStart();
	Vector3D p2 = director*scalar + start;
	Vector3D p3 = actual->getEnd();

	// Division de la route
	Road* r1 = Road::create2pointsP(p1, p2 - director*0.5f*width2, width);
	Road* connector = new Connector(p2, width, width2, theta);
	Road* r2 = Road::create2pointsP(p2 + director*0.5f*width2, p3 , width);
	
	myRoad[scalar + width2*0.5f] = r1;
	myRoad[scalar + width2*0.5f + MIN_DIFF_CONNECTOR] = connector;
	myRoad[scalar + width2 + r2->getHeight()] = r2;
	return connector;
}

bool CreatorManager::moveStart(Road * road, const Vector3D& director, float width, const Vector3D& end, CRoadStruct & cRoadStruct)
{
	// On enlève les routs liées aux connecteurs
	cleanListsConnector(cRoadStruct.startConnector, cRoadStruct.startRoads1, cRoadStruct.startRoads2);
	
	Vector3D l_start;
	if (cleanAndGetBest(road, director, end, cRoadStruct.startConnector, cRoadStruct.startRoads0, cRoadStruct.startRoads1,
		cRoadStruct.startRoads2, l_start))
	{
		road->set2points(l_start, end, width);
		return true;
	}
	return true;
}

bool CreatorManager::moveEnd(Road* road, const Vector3D& director, float width, const Vector3D& start, CRoadStruct& cRoadStruct)
{
	// On enlève les routs liées aux connecteurs
	cleanListsConnector(cRoadStruct.endConnector, cRoadStruct.endRoads1, cRoadStruct.endRoads2);

	Vector3D l_end;
	if (cleanAndGetBest(road, director, start, cRoadStruct.endConnector, cRoadStruct.endRoads0, cRoadStruct.endRoads1,
		cRoadStruct.endRoads2, l_end))
	{
		road->set2points(start, l_end, width);
		return true;
	}
	return true;
}

bool CreatorManager::cleanAndGetBest(Road * road, const Vector3D& director, const Vector3D& otherSideP, std::vector<Connector*>& connectors,
	std::vector<Road*>& roads0, std::vector<Road*>& roads1, std::vector<Road*>& roads2, Vector3D& pToModified)
{
	// On cherche juste le point qui serait le plus proche du point de l'autre coté
	int list = -1;
	Road* l_road = NULL;
	Connector* l_connector = NULL;
	float dist = FLT_MAX;
	
	// Pour les connecteurs
	for (unsigned i = 0; i < connectors.size(); i++)
	{
		// On cherche le point du connecteur le plus proche de l'autre point
		float l_dist = 0;
		Vector3D l_p = connectors[i]->getNearestSideP(otherSideP, l_dist);

		if (l_dist < dist)
		{
			list = 3;
			pToModified.set(l_p);
			l_connector = connectors[i];
		}
	}

	// Pour les starts
	for (unsigned i = 0; i < roads1.size(); i++)
	{
		// On prend le start
		Vector3D l_p = roads1[i]->getStart();
		float l_dist = (l_p - otherSideP).getMagnitude();

		if (l_dist < dist)
		{
			list = 1;
			pToModified.set(l_p);
			l_road = roads1[i];
		}
	}

	// Pour les ends
	for (unsigned i = 0; i < roads2.size(); i++)
	{
		// On cherche le end
		Vector3D l_p = roads2[i]->getEnd();
		float l_dist = (l_p - otherSideP).getMagnitude();

		if (l_dist < dist)
		{
			list = 2;
			pToModified.set(l_p);
			l_road = roads2[i];
		}
	}

	// Pour les crossing
	for (unsigned i = 0; i < roads0.size(); i++)
	{
		// On cherche le point du connecteur le plus proche de l'autre point
		
		float l_dist = scalarColl(otherSideP, director, roads0[i]) + roads0[i]->getWidth()*0.5f;

		if (l_dist < dist)
		{
			Vector3D l_p = director*l_dist + otherSideP;

			list = 0;
			pToModified.set(l_p);
			l_road = roads0[i];
		}
	}

	// On clear le reste
	// Puis on ajoute le seul élément retenu
	connectors.clear();
	roads1.clear();
	roads2.clear();
	roads0.clear();
	switch (list)
	{
	case 0:
		roads0.push_back(l_road);
		break;
	case 1:
		roads1.push_back(l_road);
		break;
	case 2:
		roads2.push_back(l_road);
		break;
	case 3:
		connectors.push_back(l_connector);
		break;
	default:
		return false;
	}

	return true;
}


void CreatorManager::cleanListsConnector(std::vector<Connector*>& connectors, std::vector<Road*>& roadsStart, std::vector<Road*>& roadsEnd)
{
	// On nettoie les resultats de la recherche
	// Pour cela on prend celui qui donne le point le plus proche
	
	// On commence par enlever tous les routes liés à des connecteurs
	for (unsigned i = 0; i < connectors.size(); i++)
	{
		alreadyInAndDelete(connectors[i], roadsStart);
		alreadyInAndDelete(connectors[i], roadsEnd);
		
		// On traite pas le cas 1 ou la route traverse
		// C'est un cas un peu bizarre, mais ca sera traitée lorsqu'on prendra le plus proche
	}
}


// IsMakableRoadSnapp function
bool CreatorManager::isCorrect(Road* road, CRoadStruct& cRoadStruct)
{
	// On récupère les routes en collision
	std::vector<Road*> roads;
	myRectangle bigRectangle = road->getBigRectangle(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	getRoadColliding(bigRectangle, roads);

	// On regarde le cas suivant
	// Si touche début et fin ou un angle trop faible et au milieu -> echec

	// On récupère les rectangles en debut et fin de la route
	myRectangle startColl = road->getStartColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	myRectangle endColl = road->getEndColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	std::vector<myRectangle> midColls = road->getMidColl(LESS_HEIGHT_MID_ROAD);

	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	Vector3D director = road->getDirectorVec();
	
	Vector3D normalDirector = director.getPerpendicular2D();
	float scalarStartNormal = start*normalDirector;
	float scalarEndNormal = end*normalDirector;
	if (scalarStartNormal > scalarEndNormal)
	{
		float tmp = scalarStartNormal;
		scalarStartNormal = scalarEndNormal;
		scalarEndNormal = tmp;
	}

	for (unsigned i = 0; i < roads.size(); i++)
	{
		if (!analyseType(startColl, endColl, midColls, roads[i],  director, normalDirector, scalarStartNormal, scalarEndNormal, cRoadStruct))
			return false;
	}
	return true;
}

bool CreatorManager::analyseType(myRectangle& startColl, myRectangle& endColl, std::vector<myRectangle> midColls,
	Road* roadi, const Vector3D& director, const Vector3D& normalDirector, float scalarStartNormal, float scalarEndNormal, CRoadStruct& cRoadStruct)
{
	// On regarde avec lequel des rectangles l'autre route est en collision
	bool isStartColliding = startColl.isColliding(*(roadi->getForm()));
	bool isEndColliding = endColl.isColliding(*(roadi->getForm()));
	Vector3D director1 = roadi->getDirectorVec();
	if (isStartColliding && isEndColliding)
		return false;

	if (isStartColliding || isEndColliding)
	{
		// L'angle est il trop faible?
		if (abs(director.getAngle2D(director1)) < MIN_ANGLE2D*PI ||
			abs(director.getAngle2D(director1) + 2*PI) < MIN_ANGLE2D*PI ||
			abs(director.getAngle2D(director1) + PI) < MIN_ANGLE2D*PI ||
			abs(director.getAngle2D(director1) - 2*PI) < MIN_ANGLE2D*PI ||
			abs(director.getAngle2D(director1) - PI) < MIN_ANGLE2D*PI)
		{
			// Est ce que la route est en collision avec tous les midColls
			bool isColliding = true;
			unsigned j = 0;
			while (j < midColls.size() && isColliding)
			{
				isColliding = midColls[j].isColliding(*(roadi->getForm()));
				j++;
			}

			if (isColliding)
				return false;
		}

		// On détermine le type cette route
		if (isStartColliding)
		{
			if (!setTypeStartColliding(roadi, startColl, cRoadStruct))
				return false;
		}
		else
		{
			if (!setTypeEndColliding(roadi, endColl, cRoadStruct))
				return false;
		}
	}
	else
	{
		if (!setTypeMidColliding(roadi, scalarStartNormal, scalarEndNormal, normalDirector, cRoadStruct))
			return false;
	}
	return true;
}

bool CreatorManager::setTypeStartColliding(Road* roadi, myRectangle& coll, CRoadStruct& cRoadStruct)
{
	myRectangle l_startColl = roadi->getStartColl(0, 1);
	myRectangle l_endColl = roadi->getEndColl(0, 1);
	
	bool isLinkingStart1 = l_startColl.isColliding(coll);
	bool isLinkingStart2 = l_endColl.isColliding(coll);
	
	Connector* cast = dynamic_cast<Connector*>(roadi);

	if (isLinkingStart1 && isLinkingStart2)
	{
		// On prend le point le plus proche
		float distStart = (l_startColl.getCenter() - coll.getCenter()).getMagnitude();
		float distEnd = (l_endColl.getCenter() - coll.getCenter()).getMagnitude();

		
		if (distStart < distEnd)
		{
			if (cast != NULL)
			{
				cRoadStruct.startConnector.push_back(cast);
			}
			else
			{
				cRoadStruct.startRoads1.push_back(roadi);
			}
		}
		else
		{
			/*if (roadi->getIsConnector() || roadi->getNext() != NULL)
				return false;*/

			if (cast != NULL)
			{
				cRoadStruct.startConnector.push_back(cast);
			}
			else
			{
				cRoadStruct.startRoads2.push_back(roadi);
			}
		}
	}
	else if (isLinkingStart1)
	{
		/*if (roadi->getIsConnector() || roadi->getLast() != NULL)
			return false;*/

		if (cast != NULL)
		{
			cRoadStruct.startConnector.push_back(cast);
		}
		else
		{
			cRoadStruct.startRoads1.push_back(roadi);
		}
	}
	else if (isLinkingStart2)
	{
		/*if (roadi->getIsConnector() || roadi->getNext() != NULL)
			return false;*/

		if (cast != NULL)
		{
			cRoadStruct.startConnector.push_back(cast);
		}
		else
		{
			cRoadStruct.startRoads2.push_back(roadi);
		}
	}
	else
	{
		cRoadStruct.startRoads0.push_back(roadi);
	}
	return true;
}

bool CreatorManager::setTypeEndColliding(Road* roadi, myRectangle& coll, CRoadStruct& cRoadStruct)
{
	myRectangle l_startColl = roadi->getStartColl(0, 1);
	myRectangle l_endColl = roadi->getEndColl(0, 1);

	bool isLinkingEnd1 = l_startColl.isColliding(coll);
	bool isLinkingEnd2 = l_endColl.isColliding(coll);

	Connector* cast = dynamic_cast<Connector*>(roadi);

	if (isLinkingEnd1 && isLinkingEnd2)
	{
		// On prend le point le plus proche
		float distStart = (l_startColl.getCenter() - coll.getCenter()).getMagnitude();
		float distEnd = (l_endColl.getCenter() - coll.getCenter()).getMagnitude();

		if (distStart < distEnd)
		{
			// ----
			// Pour le moment
			// ----
			/*if (roadi->getIsConnector() || roadi->getLast() != NULL)
				return false;*/

			if (cast != NULL)
			{
				cRoadStruct.endConnector.push_back(cast);
			}
			else
			{
				cRoadStruct.endRoads1.push_back(roadi);
			}

			//cRoadStruct.endRoads1.push_back(roadi);
		}
		else
		{
			/*if (roadi->getIsConnector() || roadi->getNext() != NULL)
				return false;*/

			if (cast != NULL)
			{
				cRoadStruct.endConnector.push_back(cast);
			}
			else
			{
				cRoadStruct.endRoads2.push_back(roadi);
			}

			//cRoadStruct.endRoads2.push_back(roadi);
		}
	}
	else if (isLinkingEnd1)
	{
		/*if (roadi->getIsConnector() || roadi->getLast() != NULL)
			return false;*/

		if (cast != NULL)
		{
			cRoadStruct.endConnector.push_back(cast);
		}
		else
		{
			cRoadStruct.endRoads1.push_back(roadi);
		}

		//cRoadStruct.endRoads1.push_back(roadi);
	}
	else if (isLinkingEnd2)
	{
		/*if (roadi->getIsConnector() || roadi->getNext() != NULL)
			return false;*/

		if (cast != NULL)
		{
			cRoadStruct.endConnector.push_back(cast);
		}
		else
		{
			cRoadStruct.endRoads2.push_back(roadi);
		}

		//cRoadStruct.endRoads2.push_back(roadi);
	}
	else
	{
		cRoadStruct.endRoads0.push_back(roadi);
	}
	return true;
}

bool CreatorManager::setTypeMidColliding(Road* roadi, float scalarStartR, float scalarEndR, const Vector3D normalDirector, CRoadStruct& cRoadStruct)
{
	// Pas de gestion des connecteurs
	if (roadi->getIsConnector())
		return false;

	// Pour les routes en collision au milieu
	float scalarStart = roadi->getStart()*normalDirector;
	float scalarEnd = roadi->getEnd()*normalDirector;

	bool isInStart = (scalarStart > scalarStartR && scalarStart < scalarEndR);
	bool isInEnd = (scalarEnd > scalarStartR && scalarEnd < scalarEndR);

	if (isInStart && isInEnd )
	{
		// Pour le moment on sait pas gérer l'absorption
		return false;
	}

	if (isInStart )
	{
		if (roadi->getIsConnector() || roadi->getLast() != NULL)
			return false;

		cRoadStruct.midRoads1.push_back(roadi);
	}
	else if (isInEnd)
	{
		if (roadi->getIsConnector() || roadi->getNext() != NULL)
			return false;

		cRoadStruct.midRoads2.push_back(roadi);
	}
	else
	{
		// Doit on gérer la division d'un connecteur
		// Pour le moment non
		if (roadi->getIsConnector())
			return false;

		cRoadStruct.midRoads0.push_back(roadi);
	}
	return true;
}


int CreatorManager::alreadyIn(Road * road, std::vector<Road*>& roads)
{
	for (unsigned i = 0; i < roads.size(); i++)
	{
		if (road == roads[i])
			return i;
	}
	return -1;
}

bool CreatorManager::alreadyInCo(Connector * connector, std::vector<Road*>& roads)
{
	for (unsigned i1 = 0; i1 < connector->sizeConnectedRoad(); i1++)
	{
		for (unsigned i2 = 0; i2 < roads.size(); i2++)
		{
			if (connector->getConnectedRoad(i1) == roads[i2])
			{
				return true;
			}
		}
	}
	return false;
}

void CreatorManager::alreadyInAndDelete(Connector * connector, std::vector<Road*>& roads)
{
	// C'est un connecteur
	// On verifie juste qu'un autre n'est pas présent
	for (unsigned i1 = 0; i1 < connector->sizeConnectedRoad(); i1++)
	{
		for (unsigned i2 = 0; i2 < roads.size(); i2++)
		{
			if (connector->getConnectedRoad(i1) == roads[i2])
			{
				roads.erase(roads.begin() + i2);
				i2--;
			}
		}
	}
}

bool CreatorManager::getRoadColliding(Form form, std::vector<Road*>& roads)
{
	std::vector<QTEntity*> entities;
	gs->QTRoads.retrieve(form.getBound(), entities);

	// On convertit les entités en Road

	for (unsigned i = 0; i < entities.size(); i++)
	{
		Road* cast = dynamic_cast<Road*>(entities[i]);
		// On ajoute suelepment si la routes est en collision avec la forme
		if (form.isColliding((*cast->getForm())))
		{
			roads.push_back(cast);
		}
	}
	return entities.size() != 0;
}

bool CreatorManager::getIsCollidingEntity(Road* road)
{
	if (road->getHeight() < MIN_HEIGHT_ROAD)
		return false;
	std::vector<QTEntity*> entities;

	gs->QTCollision.retrieve(road->getBounds(), entities);

	for (unsigned i = 0; i < entities.size(); i++)
	{
		Road* cast = dynamic_cast<Road*>(entities[i]);
		if (cast == NULL)
		{
			if (road->getForm()->isColliding(*(entities[i]->getForm())))
			{
				// Collision directe entre les deux formes
				return true;
			}
		}
	}
	return false;
}
/*
// IsMakableRoadSnapp function
float CreatorManager::getMaxOfMin(const Vector3D& center, const Vector3D& director, const Form& form)
{
	float min1 = FLT_MAX;
	float min2 = FLT_MAX;

	// Forme non reconnue, peut être un cercle?
	assert(form.size() != 0);

	for (unsigned i = 0; i < form.size(); i++)
	{
		Vector3D vec = form.get(i) - center;
		float scalar = vec * director;
		if (scalar < min1)
		{
			min1 = scalar;
		}
		else if (scalar < min2)
		{
			min2 = scalar;
		}
	}

	if (min2 == FLT_MAX)
	{
		min2 = min1;
	}

	return max(min1, min2);
}

float CreatorManager::getMinOfMax(const Vector3D& center, const Vector3D& director, const Form& form)
{
	float max1 = -FLT_MAX;
	float max2 = -FLT_MAX;

	// Forme non reconnue, peut être un cercle?
	assert(form.size() != 0);

	for (unsigned i = 0; i < form.size(); i++)
	{
		Vector3D vec = form.get(i) - center;
		float scalar = vec * director;
		if (scalar > max1)
		{
			max1 = scalar;
		}
		else if (scalar > max2)
		{
			max2 = scalar;
		}
	}

	if (max2 == -FLT_MAX)
	{
		max2 = max1;
	}

	return min(max1, max2);
}*/

// Le start et le director appartiennent à la route ou determiner la collision (scalair par rapport au début)
float CreatorManager::scalarColl(const Vector3D& start, const Vector3D& director, Road* roadi)
{
	// Projection des deux sur le vecteur normal pour trouver la collision
	Vector3D directorNormal = roadi->getDirectorVec().getPerpendicular2D();
	Vector3D vec = roadi->getStart() - start;
	// La valeur sur la normale
	float scalarPerp = vec*directorNormal;

	// On reprojette pour avoir le facteur de "projection"
	float factor = directorNormal*director;

	// Le scalair c'est "simplement":
	float scalar = scalarPerp / factor;

	return scalar;
}

bool CreatorManager::isInside(QTEntity * qtEntity)
{
	return gs->QTCollision.isValid(qtEntity->getBounds());
}
