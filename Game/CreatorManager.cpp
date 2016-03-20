#include "CreatorManager.h"

void CreatorManager::add(QTEntity* qtEntity)
{
	if (isMakableSnapp(qtEntity))
	{
		updateManager.add(qtEntity);
	}
}

void CreatorManager::addRoad(Road* road)
{
	std::map<float, Road*> myRoad;
	myRoad[FLT_MAX] = road;
	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	Vector3D director = end - start;
	float width = road->getWidth();
	float theta = road->getAngle2D();
	
	for (unsigned i = 0; i < roadsGood.size(); i++)
	{
		Vector3D vec = roadsGood[i]->getCenter() - start;
		float scalar = vec*director;
		std::map<float, Road*>::iterator iter = myRoad.lower_bound(scalar);
		// Problème lors du preIsMakable
		assert(iter != myRoad.end());
		Road* actualRoad = iter->second;
		Road* connector = divide(actualRoad, myRoad, scalar, start, director, width, roadsGood[i]->getWidth(), theta);
		myRoad.erase(iter);
		if (states[i] == 2)
		{
			handleStartDivision(actualRoad, roadsGood[i], connector);
		}
		else if (states[i] == 3)
		{
			handleEndDivision(actualRoad, roadsGood[i], connector);
		}
		else if (states[i] == 4)
		{
			// La route traverse
			handleDoubleDivision(actualRoad, roadsGood[i], connector);
		}
	}

	// Liaison de chaque bout de route
	std::map<float, Road*>::iterator it, next;
	it = myRoad.begin();
	next = it;
	next++;
	updateManager.addRoad(it->second);
	while (next != myRoad.end())
	{
		// On linke toutes les routes crées
		if (!(it->second->isConnector))
			updateManager.linkRoadNext(it->second, next->second);
		else
			updateManager.linkRoadPrec(next->second, it->second);
		updateManager.addRoad(next->second);
		it++;
		next++;
	}

	for (unsigned i = 0; i < roadsGood.size(); i++)
	{
		if (roadsGood[i]->isConnector)
		{
			if (states[i] == 0 || states[i] == 5 || states[i] == 6)
			{
				Road* actualRoad = (--myRoad.end())->second;
				updateManager.linkRoadPrec(actualRoad, roadsGood[i]);
			}
			else if (states[i] == 1 || states[i] == 8 || states[i] == 8)
			{
				Road* actualRoad = (myRoad.begin())->second;
				updateManager.linkRoadNext(actualRoad, roadsGood[i]);
			}
		}
		else if (states[i] == 0)
		{
			// Une division à faire
			std::map<float, Road*> l_road;
			Vector3D l_start = roadsGood[i]->getStart();
			Vector3D l_end = roadsGood[i]->getEnd();
			Road* actualRoad = (--myRoad.end())->second;
			Vector3D vec = actualRoad->getCenter() - start;
			Vector3D l_director = l_end - l_start;
			float scalar = vec*l_director;
			float l_theta = roadsGood[i]->getAngle2D();

			Road* connector = divide(actualRoad, l_road, scalar, start, l_director, roadsGood[i]->getWidth(), width, l_theta);
			handleStartDivision(roadsGood[i], actualRoad, connector);

			updateManager.linkRoadPrec(l_road.begin()->second, roadsGood[i]);
			updateManager.removeRoad(roadsGood[i]);


			// Liaison de chaque bout de route
			std::map<float, Road*>::iterator it, next;
			it = l_road.begin();
			next = it;
			next++;
			updateManager.addRoad(it->second);
			while (next != l_road.end())
			{
				// On linke toutes les routes crées
				if (!(it->second->isConnector))
					updateManager.linkRoadNext(it->second, next->second);
				else
					updateManager.linkRoadPrec(next->second, it->second);
				updateManager.addRoad(next->second);
				it++;
				next++;
			}
		}
		else if(states[i] == 1)
		{
			// Une division à faire
			std::map<float, Road*> l_road;
			Vector3D l_start = roadsGood[i]->getStart();
			Vector3D l_end = roadsGood[i]->getEnd();
			Road* actualRoad = (myRoad.begin())->second;
			Vector3D vec = actualRoad->getCenter() - start;
			Vector3D l_director = l_end - l_start;
			float scalar = vec*l_director;
			float l_theta = roadsGood[i]->getAngle2D();

			Road* connector = divide(actualRoad, l_road, scalar, start, l_director, roadsGood[i]->getWidth(), width, l_theta);
			handleStartDivision(roadsGood[i], actualRoad, connector);

			updateManager.linkRoadPrec(l_road.begin()->second, roadsGood[i]);
			updateManager.removeRoad(roadsGood[i]);


			// Liaison de chaque bout de route
			std::map<float, Road*>::iterator it, next;
			it = l_road.begin();
			next = it;
			next++;
			updateManager.addRoad(it->second);
			while (next != l_road.end())
			{
				// On linke toutes les routes crées
				if (!(it->second->isConnector))
					updateManager.linkRoadNext(it->second, next->second);
				else
					updateManager.linkRoadPrec(next->second, it->second);
				updateManager.addRoad(next->second);
				it++;
				next++;
			}
		}
		else if (states[i] == 5)
		{
			Road* actualRoad = (--myRoad.end())->second;
			if (actualRoad->prec == NULL && roadsGood[i]->prec == NULL)
				updateManager.linkRoadPrecNext(actualRoad, roadsGood[i]);
		}
		else if (states[i] == 6)
		{
			Road* actualRoad = (--myRoad.end())->second;
			if (actualRoad->prec == NULL && roadsGood[i]->next == NULL)
				updateManager.linkRoadPrecNext(actualRoad, roadsGood[i]);
		}
		else if (states[i] == 7)
		{
			Road* actualRoad = (myRoad.begin())->second;
			if (actualRoad->next == NULL && roadsGood[i]->prec == NULL)
				updateManager.linkRoadNextPrec(actualRoad, roadsGood[i]);
		}
		else if (states[i] == 8)
		{
			Road* actualRoad = (myRoad.begin())->second;
			if (actualRoad->next == NULL && roadsGood[i]->next == NULL)
				updateManager.linkRoadNextNext(actualRoad, roadsGood[i]);
		}
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

bool CreatorManager::isMakableRoadSnapp(Road* road)
{
	std::vector<Road*> nearRoad;
	std::vector<int> states;
	if (!preIsMakableRoadSnapp(road, nearRoad, states))
		return false;

	Vector3D start = road->getStart();
	Vector3D end = road->getEnd();
	Vector3D director = end - start;

	float width = road->getWidth();
	
	bool isThere0 = false; // Debut avec division
	bool isThere1 = false; // Fin avec division
	int numberOf56 = 0; // Nombre de collision debut avec le début ou la fin d'une autre route
	int numberOf78 = 0; // Nombre de collision fin avec le début ou la fin d'une autre route
	for (unsigned i = 0; i < nearRoad.size(); i++)
	{
		switch (states[i])
		{
		case 0:
			isThere0 = true;
			break;
		case 1:
			isThere1 = true;
			break;
		case 5:
			numberOf56++;
			break;
		case 6:
			numberOf56++;
			break;
		case 7:
			numberOf78++;
			break;
		case 8:
			numberOf78++;
			break;
		}
	}
	if (!isThere0)
	{
		// Gestion d'une collision debutFin au début
		// Pour le moment un seul
		// Si on veut passer à plusieurs, il faudra gérer l'ajout de connecteurs
		if (numberOf56 == 1)
		{
			float minDist = FLT_MAX;
			Vector3D vec;
			int add;
			for (unsigned i = 0; i < nearRoad.size(); i++)
			{

				// On récupère la position des points les plus proches
				// On snapp l'élément sur le prochain
				if (states[i] == 5)
				{
					Vector3D pos = nearRoad[i]->getStart();
					float dist = (pos - start).getMagnitude();
					if (dist < minDist)
					{
						minDist = dist;
						vec.set(pos);
						add = i;
					}
				}
				else if (states[i] == 6)
				{
					Vector3D pos = nearRoad[i]->getEnd();
					float dist = (pos - start).getMagnitude();
					if (dist < minDist)
					{
						minDist = dist;
						vec.set(pos);
						add = i;
					}
				}
			}
			road->set2points(vec, end, width);
			start.set(vec);
			director = end - start;
			roadsGood.push_back(nearRoad[add]);
			this->states.push_back(states[add]);
		}
		else
		{
			roadsGood.clear();
			this->states.clear();
			return false;
		}
		
	}
	else
	{
		// Normalement on devrait en avoir un seul
		// On calcule le minimum des routes au dessus
		float maxStart = FLT_MIN;
		int add;
		for (unsigned i = 0; i < nearRoad.size(); i++)
		{
			float max = getMaxOfMin(road->getForm()->getCenter(), director, *(nearRoad[i]->getForm()));
			if (max > maxStart)
			{
				maxStart = max;
				add = i;
			}
		}
		Vector3D l_start = director*maxStart + road->getForm()->getCenter();
		road->setStart(l_start);
		roadsGood.push_back(nearRoad[add]);
		this->states.push_back(states[add]);
	}

	if (!isThere1)
	{
		// Meme chose que pour le start
		// Gestion d'une collision debutFin au début
		// Pour le moment un seul
		// Si on veut passer à plusieurs, il faudra gérer l'ajout de connecteurs
		if (numberOf78 == 1)
		{
			float minDist = FLT_MAX;
			Vector3D vec;
			int add;
			for (unsigned i = 0; i < nearRoad.size(); i++)
			{

				// On récupère la position des points les plus proches
				// On snapp l'élément sur le prochain
				if (states[i] == 7)
				{
					Vector3D pos = nearRoad[i]->getStart();
					float dist = (pos - end).getMagnitude();
					if (dist < minDist)
					{
						minDist = dist;
						vec.set(pos);
						add = i;
					}
				}
				else if (states[i] == 8)
				{
					Vector3D pos = nearRoad[i]->getEnd();
					float dist = (pos - end).getMagnitude();
					if (dist < minDist)
					{
						minDist = dist;
						vec.set(pos);
						add = i;
					}
				}
			}
			road->set2points(start, vec, width);
			end.set(vec);
			director = end - start;
			roadsGood.push_back(nearRoad[add]);
			this->states.push_back(states[add]);
		}
		else
		{
			roadsGood.clear();
			this->states.clear();
			return false;
		}
	}
	else
	{
		// Normalement on devrait en avoir un seul
		// On calcule le minimum des routes au dessus
		float minEnd = FLT_MAX;
		int add;
		for (unsigned i = 0; i < nearRoad.size(); i++)
		{
			float min = getMinOfMax(road->getForm()->getCenter(), director, *(nearRoad[i]->getForm()));
			if (min < minEnd)
			{
				minEnd = min;
				add = i;
			}
		}
		Vector3D l_end = director*minEnd + road->getForm()->getCenter();
		road->setStart(l_end);
		roadsGood.push_back(nearRoad[add]);
		this->states.push_back(states[add]);
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

}
void CreatorManager::handleEndDivision(Road* actualRoad, Road* colliding, Road* connector)
{

}
void CreatorManager::handleDoubleDivision(Road* actualRoad, Road* colliding, Road* connector)
{

}
Road* CreatorManager::divide(Road* actual, std::map<float, Road*>& myRoad, float scalar,
	const Vector3D& start, const Vector3D& director, float width, float width2, float thetat)
{
	// isConnector = true;
}

// IsMakableRoadSnapp function
bool CreatorManager::preIsMakableRoadSnapp(Road* road, std::vector<Road*>& roadsColliding, std::vector<int>& sides)
{
	if (road->getHeight() < MIN_HEIGHT_ROAD)
		return false;

	// Approximation de la direction de la route ici ou avant
	// On regarde si la route est en collision avec un autre élément qu'une route

	// 0) TEST COLLISION
	// Récupération des éléments possiblement en collision
	// On traitera après les routes des autres éléments
	// Les autres éléments ne doivent pas être en collision avec une route
	std::vector<QTEntity*> entities;

	gameStruct->QTCollision.retrieve(road->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On tente un cast en route, si le pointeur est différent de NULL, c'est une route
		QTEntity* test = entities[i];
		Road * cast = dynamic_cast<Road*>(test);
		if (cast == NULL)
		{
			if (entities[i]->getForm() != NULL && road->getForm()->isColliding(*(entities[i]->getForm())))
			{
				return false; // Y a une collision
			}
		}
	}

	// Recupération des routes qui sont possiblement en collision
	std::vector<QTEntity*> roadsBefCast;
	std::vector<Road*> roads;
	//std::vector<Road*> roadsColliding;

	myRectangle bigRectangle = road->getBigRectangle(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	sRectangle bigBound = bigRectangle.getBound();
	gameStruct->QTRoads.retrieve(bigBound, roadsBefCast);
	// Cast en roads
	for (unsigned i = 0; i < roadsBefCast.size(); i++)
	{
		QTEntity *test = roadsBefCast[i];
		Road *cast = dynamic_cast<Road*>(test);
		assert(cast != NULL); // Qu'est ce que fout cet objet qui n'est pas une route dans ces resultats?
		roads.push_back(cast);
	}

	// 1) TEST DE COLLISION DEBUT FIN
	// -> L'angle entre les deux routes doit être au minimum de 45°C
	myRectangle startColl = road->getStartColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	myRectangle endColl = road->getEndColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	Vector3D director = road->getDirectorVec();
	std::vector<myRectangle> midColls = road->getMidColl(LESS_HEIGHT_MID_ROAD);
	for (unsigned i = 0; i < roads.size(); i++)
	{
		// On regarde si l'autre route est en collision avec le bigRectangle
		if (bigRectangle.isColliding((*roads[i]->getForm())))
		{
			// La route est en collision avec le début ou la fin?
			bool isStart = startColl.isColliding((*roads[i]->getForm()));
			bool isEnd = endColl.isColliding((*roads[i]->getForm()));
			if (isStart && isEnd)
				return false;

			if (isStart || isEnd)
			{
				// L'angle est il trop faible?
				Vector3D director1 = roads[i]->getDirectorVec();
				if (director.getAngle2D(director1) < MIN_ANGLE2D*PI)
				{
					// Est ce que la route est en collision avec tous les midColls?
					bool isColliding = true;
					unsigned j = 0;
					while (j < midColls.size() && isColliding)
					{
						isColliding = midColls[j].isColliding((*roads[i]->getForm()));
						j++;
					}

					// Angle trop faible et mauvaise position
					if (isColliding)
						return false;
				}
				roadsGood.push_back(roads[i]);
				Vector3D startG = roads[i]->getStart();
				Vector3D endG = roads[i]->getEnd();
				myRectangle recStartG(startG, 0.5f, 0.5f);
				myRectangle recEndG(endG, 0.5f, 0.5f);
				bool isLinkingStart = startColl.isColliding(recStartG);
				bool isLinkingEnd = startColl.isColliding(recEndG);
				if (!isLinkingStart && !isLinkingEnd)
				{
					if (isStart)
					{
						sides.push_back(0);
					}
					else
					{
						sides.push_back(1);
					}
				}
				else if (isLinkingStart && isLinkingEnd)
				{
					if (isStart)
					{
						float distStart = (startG - startColl.getCenter()).getMagnitude();
						float distEnd = (endG - startColl.getCenter()).getMagnitude();

						if (distStart < distEnd)
						{
							sides.push_back(5);
						}
						else
						{
							sides.push_back(6);
						}
					}
					else
					{
						float distStart = (startG - startColl.getCenter()).getMagnitude();
						float distEnd = (endG - startColl.getCenter()).getMagnitude();

						if (distStart < distEnd)
						{
							sides.push_back(7);
						}
						else
						{
							sides.push_back(8);
						}
					}
				}
				else if (isLinkingStart)
				{
					if (isStart)
					{
						sides.push_back(5);
					}
					else
					{
						sides.push_back(6);
					}
				}
				else
				{
					if (isStart)
					{
						sides.push_back(7);
					}
					else
					{
						sides.push_back(8);
					}
				}

			}
			else
			{
				roadsColliding.push_back(roads[i]);
			}
		}
	}
	return true;
}

float CreatorManager::getMaxOfMin(const Vector3D& center, const Vector3D& director, Form form)
{

}
float CreatorManager::getMinOfMax(const Vector3D& center, const Vector3D& director, Form form)
{

}