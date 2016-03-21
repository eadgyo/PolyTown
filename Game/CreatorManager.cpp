#include "CreatorManager.h"

//--- A faire
//--> Gestion ajout Connector lors du Add
//--> Gestion snapp sur un Connector


CreatorManager::CreatorManager()
{
	gameStruct = NULL;
}

CreatorManager::~CreatorManager()
{
}

void CreatorManager::initialize(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

void CreatorManager::addRoad(Road * road)
{
	CRoadStruct cRoadStruct;
	if (!isMakableSnappRoad(road, cRoadStruct))
		return;

	std::map<float, Road*> myRoad;
	myRoad[FLT_MAX] = road;
	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	Vector3D director = end - start;
	float width = road->getWidth();
	float theta = road->getAngle2D();

	handleAllMid(cRoadStruct, myRoad, start, director, width, theta);
	
	// On lie tous les bouts de routes
	linkMapRoad(myRoad);

	handleAllStart(cRoadStruct, myRoad.begin()->second);
	handleAllEnd(cRoadStruct, (--myRoad.end())->second);

	// On recherche le plus petit index
	int minIndex = updateManager.computeRoadIndex(myRoad);
	if (minIndex == -1)
	{
		minIndex = updateManager.getConnexitude();
	}

	// Nous pourrions utilisé un modèle optimisé
	updateManager.setConnexitude(myRoad.begin()->second, minIndex);
}

void CreatorManager::handleAllStart(CRoadStruct& cRoadStruct, Road* startR)
{
	for (unsigned i = 0; i < cRoadStruct.startRoads0.size(); i++)
	{
		std::map<float, Road*> l_road;
		Road* actualRoad = startR;
		Road* road = cRoadStruct.startRoads0[i];
		Vector3D l_start = road->getStart();
		Vector3D l_end = road->getEnd();
		float theta = road->getAngle2D();
		float width = road->getWidth();
		Vector3D l_director = l_end - l_start;
		l_road[FLT_MAX] = road;

		Road* actualRoad;
		Road* connector = createConnectorFromMap(actualRoad, startR, l_road, l_start, l_director, width, theta);
		handleDoubleDivision(road, startR, connector);

		// On copie les anciens liens
		updateManager.linkRoadCopyLast(road, l_road.begin()->second);
		updateManager.linkRoadCopyNext(road, (--l_road.end())->second);
		updateManager.removeRoad(road);

		linkMapRoad(l_road);
	}

	// Pour le moment pas de gestion de collision avec d'autres connecteurs
	for (unsigned i = 0; i < cRoadStruct.startRoads1.size(); i++)
	{
		// Connexion debut/début
		updateManager.linkRoadLastLast(startR, cRoadStruct.startRoads1[i]);
	}

	for (unsigned i = 0; i < cRoadStruct.startRoads2.size(); i++)
	{
		// Connexion debut/fin
		updateManager.linkRoadLastNext(startR, cRoadStruct.startRoads2[i]);
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
		Vector3D director = l_end - l_start;
		l_road[FLT_MAX] = road;

		Road* actualRoad;
		Road* connector = createConnectorFromMap(actualRoad, endR, l_road, l_start, director, width, theta);
		handleDoubleDivision(actualRoad, endR, connector);

		// On copie les anciens liens
		updateManager.linkRoadCopyLast(road, l_road.begin()->second);
		updateManager.linkRoadCopyNext(road, (--(l_road.end()))->second);
		updateManager.removeRoad(road);

		linkMapRoad(l_road);
	}

	// Pour le moment pas de gestion de collision avec d'autres connecteurs
	for (unsigned i = 0; i < cRoadStruct.endRoads1.size(); i++)
	{
		// Connexion fin/début
		updateManager.linkRoadNextLast(endR, cRoadStruct.endRoads1[i]);
	}

	for (unsigned i = 0; i < cRoadStruct.endRoads2.size(); i++)
	{
		// Connexion fin/fin
		updateManager.linkRoadNextNext(endR, cRoadStruct.endRoads2[i]);
	}

}

void CreatorManager::handleAllMid(CRoadStruct& cRoadStruct, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director, float width, float theta)
{
	for (unsigned i = 0; i < cRoadStruct.midRoads0.size(); i++)
	{
		Road* actualRoad;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads0[i], myRoad, start, director, width, theta);
		handleDoubleDivision(actualRoad, cRoadStruct.midRoads0[i], connector);
	}
	for (unsigned i = 0; i < cRoadStruct.midRoads1.size(); i++)
	{
		Road* actualRoad;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads1[i], myRoad, start, director, width, theta);
		handleEndDivision(actualRoad, cRoadStruct.midRoads1[i], connector);
	}
	for (unsigned i = 0; i < cRoadStruct.midRoads2.size(); i++)
	{
		Road* actualRoad;
		Road* connector = createConnectorFromMap(actualRoad, cRoadStruct.midRoads2[i], myRoad, start, director, width, theta);
		handleStartDivision(actualRoad, cRoadStruct.midRoads2[i], connector);
	}
}

Road* CreatorManager::createConnectorFromMap(Road* actualRoad, Road* roadi, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director, float width, float theta)
{
	Vector3D vec = roadi->getCenter() - start;
	float scalar = vec*director;

	// Récupération de actualRoad
	std::map<float, Road*>::iterator iter = myRoad.lower_bound(scalar);
	
	// Probleme la route a été mal crée
	assert(iter != myRoad.end());
	Road* actualRoad = iter->second;
	Road* connector = divide(actualRoad, myRoad, scalar, start, director, width, roadi->getWidth(), theta);
	myRoad.erase(iter);
	return connector;
}

void CreatorManager::linkMapRoad(std::map<float, Road*> myRoad)
{
	std::map<float, Road*>::iterator it, next;
	it = myRoad.begin();
	next = it;
	next++;
	updateManager.addRoad(it->second);
	while (next != myRoad.end())
	{
		// On linke toutes les routes crées
		if (!(it->second->getIsConnector()))
			updateManager.linkRoadNext(it->second, next->second);
		else
			updateManager.linkRoadLast(next->second, it->second);
		updateManager.addRoad(next->second); // Ajout de la route
		it++;
		next++;
	}
}

void CreatorManager::add(QTEntity* qtEntity)
{
	if (isMakableSnapp(qtEntity))
	{
		updateManager.add(qtEntity);
	}
}




bool CreatorManager::isMakable(QTEntity* qtEntity)
{
	// Il ne faut aucune collision
	// Vu qu'on a pas le droit de bouger l'élément
	std::vector<QTEntity*> collidings;
	getColliding(qtEntity, collidings);
	return (collidings.size() == 0);
}

bool CreatorManager::isMakableSnappRoad(Road * road)
{
	CRoadStruct cRoadStrcut;
	return isMakableSnappRoad(road, cRoadStrcut);
}

bool CreatorManager::isMakableSnappRoad(Road * road, CRoadStruct& cRoadStrcut)
{
	// Clear
	cRoadStrcut.clear();

	// Save
	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	
	Vector3D director = road->getDirectorVec();
	float width = road->getWidth();

	CRoadStruct cRoadStrcut1, cRoadStrcut2;
	
	// On commencer par regarder si c'est faisable
	// Ensuite on tente de bouger
	// Si le mouvement marche pas on revient en arrière
	if (!isCorrect(road, cRoadStrcut1))
		return false;

	// Sauvegarde de cRoadStruct1 -> si on doit revenir en arrière
	cRoadStrcut.set(cRoadStrcut1);
	if (!moveStart(road, director, width, end, cRoadStrcut1) || !isCorrect(road, cRoadStrcut2))
	{
		// On revient en arrière, snapp pas possible
		road->set2points(start, end, width);
	}
	else
	{
		// Sauvegarde du nouveau start
		cRoadStrcut.set(cRoadStrcut2);
		start = road->getStart();
	}

	// Copie
	cRoadStrcut1.set(cRoadStrcut);
	if (!moveEnd(road, director, width, start, cRoadStrcut1) || !isCorrect(road, cRoadStrcut2))
	{
		// On revient en arrière, snapp pas possible
		road->set2points(start, end, width);
	}
	else
	{
		// Sauvegarde de l'état
		cRoadStrcut.set(cRoadStrcut2);
		start = road->getStart();
	}

	// Snapp ou pas, on peut poser la route
	return true;
}



bool CreatorManager::isMakableSnapp(QTEntity* qtEntity)
{
	// Mauvaise initialisation de qtEntity
	assert(qtEntity->getForm() != NULL);
	Vector3D pos = qtEntity->getCenter();
	std::vector<QTEntity*> colliding;

	// On récupère les éléments dans le cercle comprenant tous les points
	// Le cercle est transformé en rectangle pour supporter le QuadTree
	// Pourquoi un cercle et pas un simple rectangle getBound ?
	// On va faire des rotations, donc il faut être sur qu'on a tous les objets possiblement en collision
	gameStruct->QTCollision.retrieve(qtEntity->getBoundsMax(), colliding);

	if (colliding.size() == 1)
	{
		// On tente une rotation puis une translation
		qtEntity->setRadians(qtEntity->getAngle2D());
		Vector3D l_push;
		float l_t;

		// On calcule le vecteur de poussée
		colliding[0]->isColliding((*qtEntity->getForm()), l_push, l_t);
		qtEntity->translate(l_push*l_t);

		// On reteste la collision
		colliding.clear();
		getColliding(qtEntity, colliding);
		if (colliding.size() != 0)
		{
			// La rotation + translation a crée au moins une autre collision
			// On revient en arrière
			qtEntity->setRadians(0);
			qtEntity->setCenter(pos);
		}
	}
	int numberOfTry = 0;
	Vector3D push;
	colliding.clear();
	getColliding(qtEntity, colliding, push);
	while (colliding.size() != 0 && numberOfTry < MAX_TRY_SNAPP_QTENTITY)
	{
		qtEntity->translate(push);
	}
	if (colliding.size() != 0 || (qtEntity->getCenter() - pos).getMagnitude() > DISTANCE_MAX_SNAPP)
	{
		qtEntity->setCenter(pos);
		return false;
	}
	return true;
}

void CreatorManager::getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding)
{
	// Mauvaise initialisation de qtEntity
	assert(qtEntity->getForm() != NULL);
	std::vector<QTEntity*> possibleCollisions;
	gameStruct->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);

	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		if (qtEntity->getForm()->isColliding(*(possibleCollisions[i]->getForm())))
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
	gameStruct->QTCollision.retrieve(qtEntity->getBounds(), possibleCollisions);
	for (unsigned i = 0; i < possibleCollisions.size(); i++)
	{
		Vector3D l_push(0,0,0,false);
		float t = 0;
		if (qtEntity->getForm()->isColliding(*(possibleCollisions[i]->getForm()), l_push, t))
		{
			// Collision directe entre les deux formes
			colliding.push_back(possibleCollisions[i]);

			// On ajoute le vecteur de poussé au vecteur globale
			push += l_push*t;
		}
	}
}


// Add road functions
void CreatorManager::handleStartDivision(Road* actualRoad, Road* colliding, Road* connector)
{
	Vector3D director = -colliding->getDirectorVec();
	Vector3D center = colliding->getCenter();

	float min = getMaxOfMin(center, director, *(actualRoad->getForm()));

	Vector3D start = director*min;
	Vector3D end = director*min;
	float width = colliding->getWidth();

	colliding->set2points(start, end, width);

	updateManager.linkRoadGuess(colliding, connector);
	
}

void CreatorManager::handleEndDivision(Road* actualRoad, Road* colliding, Road* connector)
{
	Vector3D director = colliding->getDirectorVec();
	Vector3D center = colliding->getCenter();

	float min = getMaxOfMin(center, director, *(actualRoad->getForm()));

	Vector3D start = colliding->getStart();
	Vector3D end = director*min;
	float width = colliding->getWidth();

	colliding->set2points(start, end, width);

	updateManager.linkRoadGuess(colliding, connector);
}

void CreatorManager::handleDoubleDivision(Road* actualRoad, Road* colliding, Road* connector)
{
	Vector3D director = colliding->getDirectorVec();
	Vector3D start = colliding->getStart();
	Vector3D end = colliding->getEnd();
	Vector3D center = colliding->getCenter();
	float width = colliding->getWidth();

	float maxStart = getMaxOfMin(center, director, *(actualRoad->getForm()));
	float minEnd = getMinOfMax(center, director, *(actualRoad->getForm()));

	Vector3D end1 = start + director*maxStart;
	Vector3D start2 = start + director*minEnd;

	Road* road1 = Road::create2pointsP(start, end1, width);
	Road* road2 = Road::create2pointsP(start2, end, width);

	// Ne fonctionne uniquement avec les routes différents que les connecteurs
	Road* last = colliding->getLast();
	Road* next = colliding->getNext();
	
	// A verifier que c'est le bon sens

	///-----------------------------------------------------------------
	/// --- BUG possible, peut être un échange de routes ---------------
	/// ----------------------------------------------------------------
	if (last != NULL)
	{
		updateManager.linkRoadNextLast(last, road1);
	}
		updateManager.linkRoadNext(road1, connector);
		updateManager.linkRoadLast(road2, connector);
	
	if (next != NULL)
	{
		updateManager.linkRoadLastNext(next, road2);
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
	Road* r1 = Road::create2pointsP(p1, p2, width);
	Road* connector = new Connector(p2, width, width2, theta);
	Road* r2 = Road::create2pointsP(p2, p3, width);
	
	myRoad[scalar] = r1;
	myRoad[scalar + MIN_DIFF_CONNECTOR] = r1;
	myRoad[scalar] = r1;
	return connector;
}

bool CreatorManager::moveStart(Road * road, const Vector3D& director, float width, Vector3D end, CRoadStruct & cRoadStruct)
{
	if(cRoadStruct.startRoads1.size() + cRoadStruct.startRoads2.size() == 1)
	{
		if (cRoadStruct.startRoads1.size() == 1)
		{
			// On snapp simplement le start sur l'autre start
			Vector3D l_start = cRoadStruct.startRoads1[0]->getStart();
			road->set2points(l_start, end, width);
		}
		else if (cRoadStruct.startRoads2.size() == 1)
		{
			// On snapp simplement le start sur l'autre end
			Vector3D l_start = cRoadStruct.startRoads1[0]->getEnd();
			road->set2points(l_start, end, width);
		}
	}
	else if (cRoadStruct.startRoads1.size() + cRoadStruct.startRoads2.size() == 0)
	{
		if (cRoadStruct.startRoads0.size() != 0)
		{
			float maxStart = FLT_MIN;
			float add = -1;
			for (unsigned i = 0; i < cRoadStruct.startRoads0.size(); i++)
			{
				float max = getMinOfMax(road->getForm()->getCenter(), director, *(cRoadStruct.startRoads0[i]->getForm()));
				if (max > maxStart)
				{
					maxStart = max;
					add = i;
				}
			}
			Vector3D l_start = director*maxStart + road->getForm()->getCenter();
			road->set2points(l_start, end, width);
			Road* tmp = cRoadStruct.startRoads0[add];
			cRoadStruct.startRoads0.clear();
			cRoadStruct.startRoads0.push_back(tmp);
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool CreatorManager::moveEnd(Road * road, const Vector3D& director, float width, Vector3D start, CRoadStruct & cRoadStruct)
{
	if (cRoadStruct.endRoads1.size() + cRoadStruct.endRoads2.size() == 1)
	{
		if (cRoadStruct.endRoads1.size() == 1)
		{
			// On snapp simplement le end sur l'autre start
			Vector3D l_end = cRoadStruct.endRoads1[0]->getStart();
			road->set2points(start, l_end, width);
		}
		else if (cRoadStruct.startRoads2.size() == 1)
		{
			// On snapp simplement le end sur l'autre end
			Vector3D l_end = cRoadStruct.endRoads1[0]->getEnd();
			road->set2points(start, l_end, width);
		}
	}
	else if (cRoadStruct.endRoads1.size() + cRoadStruct.endRoads2.size() == 0)
	{
		if (cRoadStruct.endRoads0.size() != 0)
		{
			float minEnd = FLT_MAX;
			float add = -1;
			for (unsigned i = 0; i < cRoadStruct.endRoads0.size(); i++)
			{
				float min = getMaxOfMin(road->getForm()->getCenter(), director, *(cRoadStruct.endRoads0[i]->getForm()));
				if (min < minEnd)
				{
					minEnd = min;
					add = i;
				}
			}
			Vector3D l_end = director*minEnd + road->getForm()->getCenter();
			road->set2points(start, l_end, width);
			Road* tmp = cRoadStruct.endRoads0[add];
			cRoadStruct.endRoads0.clear();
			cRoadStruct.endRoads0.push_back(tmp);
		}
	}
	else
	{
		return false;
	}

	return true;
}


// IsMakableRoadSnapp function
bool CreatorManager::isCorrect(Road* road, CRoadStruct cRoadStruct)
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
		if (director.getAngle2D(director1) < MIN_ANGLE2D*PI)
		{
			// Est ce que la route est en collision avec tous les midColls
			bool isColliding = true;
			unsigned j = 0;
			while (j < midColls.size() && isColliding);
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
	

	if (isLinkingStart1 && isLinkingStart2)
	{
		// On prend le point le plus proche
		float distStart = (l_startColl.getCenter() - coll.getCenter()).getMagnitude();
		float distEnd = (l_endColl.getCenter() - coll.getCenter()).getMagnitude();

		if (distStart < distEnd)
		{
			// ----
			// Pour le moment
			// ----
			if (roadi->getIsConnector() || roadi->getLast() != NULL)
				return false;

			cRoadStruct.startRoads1.push_back(roadi);
		}
		else
		{
			if (roadi->getIsConnector() || roadi->getNext() != NULL)
				return false;

			cRoadStruct.startRoads2.push_back(roadi);
		}
	}
	else if (isLinkingStart1)
	{
		if (roadi->getIsConnector() || roadi->getLast() != NULL)
			return false;

		cRoadStruct.startRoads1.push_back(roadi);	
	}
	else if (isLinkingStart2)
	{
		if (roadi->getIsConnector() || roadi->getNext() != NULL)
			return false;

		cRoadStruct.startRoads2.push_back(roadi);
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
			if (roadi->getIsConnector() || roadi->getLast() != NULL)
				return false;

			cRoadStruct.endRoads1.push_back(roadi);
		}
		else
		{
			if (roadi->getIsConnector() || roadi->getNext() != NULL)
				return false;

			cRoadStruct.endRoads2.push_back(roadi);
		}
	}
	else if (isLinkingEnd1)
	{
		if (roadi->getIsConnector() || roadi->getLast() != NULL)
			return false;

		cRoadStruct.endRoads1.push_back(roadi);
	}
	else if (isLinkingEnd2)
	{
		if (roadi->getIsConnector() || roadi->getNext() != NULL)
			return false;

		cRoadStruct.endRoads2.push_back(roadi);
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
		cRoadStruct.midRoads1.push_back(roadi);
	}
	else if (isInEnd)
	{
		cRoadStruct.midRoads2.push_back(roadi);
	}
	else
	{
		cRoadStruct.midRoads0.push_back(roadi);
	}
	return true;
}


bool CreatorManager::getRoadColliding(Form form, std::vector<Road*>& roads)
{
	std::vector<QTEntity*> entities;
	gameStruct->QTRoads.retrieve(form.getBound(), entities);

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

	gameStruct->QTCollision.retrieve(road->getBounds(), entities);

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
	float max1 = FLT_MIN;
	float max2 = FLT_MIN;

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

	if (max2 == FLT_MIN)
	{
		max2 = max1;
	}

	return min(max1, max2);
}