#include "CreatorManager.h"

#define DEF_WIDTH_ROAD 10.0f
#define DEF_HEIGHT_ROAD 10.0f
#define LESS_HEIGHT_MID_ROAD 10.0f

#define MIN_HEIGHT_ROAD 5.0f
#define MIN_ANGLE2D 0.25f
// Distance max pour le snapp
#define MIN_DIF_QTEntity 10.0f
// Agrandissement 
#define AGG_FORM 1.2f


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

// Fonction d'ajout ou de suppression � appeler
// Penser � appeler isMakableSnapp avant
void CreatorManager::add(QTEntity * qtEntity)
{
	// Link road + Gen
	gameStruct->QTCollision.insert(qtEntity);
	
	// Link road
	// On r�cup�re les routes en collision
	std::vector<QTEntity*> entities;
	// On agrandit la form d'un certain facteur pour avoir les �l�ments autour
	// On consid�re que le rayon d'action est un peu plus grand

	Form formAgrand = qtEntity->getForm()->clone();
	formAgrand.scaleF(1.2f, formAgrand.getCenter());
	gameStruct->QTRoads.retrieve(formAgrand.getBound(), entities);


	// On a les routes possiblement en collision
	// On cherche les routes en collision
	for (unsigned i = 0; i < entities.size(); i++)
	{
		if (formAgrand.isColliding((*entities[i]->getForm())))
		{
			Road * cast = dynamic_cast<Road*>(entities[i]);
			assert(cast != NULL); // Mauvaise gestion
			// Ajout de la route dans qtEntity
			qtEntity->addRoad(cast);
		}
	}
}

void CreatorManager::addRoad(Road * road)
{
	// Link road, reAdd QTEntity
	gameStruct->QTCollision.insert(road);
	gameStruct->QTRoads.insert(road);

	// On r�cup�re l'ancienne isMakable resultats
	// On traite juste les cas suivants
	// 2 � gauche
	// 3 � droite
	// 4 travers
	int minI = -1;
	bool differentIndex = false;
	std::map<float, Road*> myRoad;
	myRoad[0] = road;
	std::vector<Road*> roads;
	for (unsigned i = 0; i < roadsGood.size(); i++)
	{
		if (roadsGood[i]->getConnexitude() != -1)
		{
			if (roadsGood[i]->getConnexitude() != minI && minI != -1)
			{
				differentIndex = true;
			}
			if (roadsGood[i]->getConnexitude() < minI || minI == -1)
			{
				minI = roadsGood[i]->getConnexitude();
			}
		}
		else
		{
			// Quand m�me bizarre
			differentIndex = true;
		}

		if (side[i] == 2)
		{
			// Il faut determiner avant quel bout de rout est concern�
			// Car suite � la cr�ation de route 
			handleStartRoad(road, roadsGood[i], roads, myRoad);
			replaceRoad(roadsGood[i]);
			// Probl�me 
			Road* r1 = roads[roads.size() - 1];
			Road* r2 = roads[roads.size() - 2];
			Road* r3 = roads[roads.size() - 3];
			
			
		}
		else if (side[i] == 3)
		{
			handleEndRoad(road, roadsGood[i], roads, myRoad);
			Road* r1 = roads[roads.size() - 1];
			Road* r2 = roads[roads.size() - 2];
			Road* r3 = roads[roads.size() - 3];
		}
		else if (side[i] == 4)
		{
			handleCrossingRoad(road, roadsGood[i], roads, myRoad);
			Road* r1 = roads[roads.size() - 1];
			Road* r2 = roads[roads.size() - 2];
			Road* r3 = roads[roads.size() - 3];
		}
		else
		{
			roads.push_back(roadsGood[i]);
		}
	}

	if (minI == -1)
	{
		minI = getConnexitude();
		setConnexitude(myRoad[0], minI);
	}
	else
	{
		if (differentIndex)
		{
			setConnexitude(myRoad[0], minI);
		}
		else
		{
			for (unsigned i = 0; i < myRoad.size(); i++)
				myRoad[i]->setConnexitude(minI);
		}
	}
	
}



bool CreatorManager::isMakableRoadSnapp(Road * road)
{	
	// On sauvegarde ces 2 �l�ments car ils serviront plus tard pour la s�paration de la route
	roadsGood.clear();
	side.clear();
	// On regarde la route est possiblement cr�able (toujours un risque que non)
	if (!preIsMakableRoadSnapp(road, roadsGood, side))
	{
		return false;
	}
	else if (!snappRoad(road, roadsGood, side))
	{
		// A t'on besoin de bouger l'�l�ment
		// Probl�me lors du snapp (Exemple: Multi-Collision)
		// On ne peut pas cr�er la route
		return false;
	}
	// On peut cr�er 
	return true;
}

bool CreatorManager::isMakableSnapp(QTEntity * qtEntity)
{
	float minDif = MIN_DIF_QTEntity;
	std::vector<QTEntity*> entitiesColliding;
	std::vector<Vector3D> pushes;
	std::vector<float> ts;

	// On regarde l'�l�ment est possible cr�able (toujours un risque que non)
	if (!preIsMakableSnapp(qtEntity, minDif, entitiesColliding, pushes, ts))
	{
		return false;
	}
	else if (!snapp(qtEntity, minDif, entitiesColliding, pushes, ts))
	{
		// Le snapp a rencontrer des difficult�s (Exemple multi collision)
		// On ne peut pas cr�er l'�l�ment
		return false;
	}
	// On peut cr�er l'�l�ment
	return true;
}

bool CreatorManager::isMakableRoad(Road* road)
{
	// On sauvegarde ces 2 �l�ments car ils serviront plus tard pour la s�paration de la route
	roadsGood.clear();
	side.clear();
	// On regarde la route est possiblement cr�able (toujours un risque que non)
	if (!preIsMakableRoad(road, roadsGood, side))
	{
		return false;
	}
	return true;
}

bool CreatorManager::isMakable(QTEntity* qtEntity)
{
	// On regarde l'�l�ment est possible cr�able (toujours un risque que non)
	if (!preIsMakable(qtEntity))
	{
		return false;
	}
	// On peut cr�er l'�l�ment
	return true;
}

void CreatorManager::remove(QTEntity * qtEntity)
{
	// Si pollution ...

	this->gameStruct->QTCollision.erase(qtEntity);
	/*
	if(GENEAU)
	this->gameStruct->QTWaterGen.erase(qtEntity); // + RemoveGen...
	else if(EAURES)
	this->gameStruct->QTWaterRes.erase(qtEntity); // + RemoveRes...

	if(GENELEC)
	this->gameStruct->QTWaterGen.erase(qtEntity);
	else if(RESELEC)
	this->gameStruct->QTWaterRes.erase(qtEntity);
	*/
	Road * road = dynamic_cast<Road*>(qtEntity);
	if (road != NULL)
		removeRoad(road);
	/*
	Habitation...
	*/
}

void CreatorManager::replaceRoad(Road * road)
{
}

void CreatorManager::removeRoad(Road * road)
{
	for (unsigned i = 0; i < road->sizeConnected(); i++)
	{
		road->getConnected(i)->removeRoad(road);
	}
	recalculateAfterRemove(road);
}

void CreatorManager::removeRoad(Road* road, const Vector3D& center, float dist)
{

}


// GameStruct
void CreatorManager::setGameStruct(GameStruct * gameStruct)
{
	this->gameStruct = gameStruct;
}

bool CreatorManager::snappRoad(Road * road, std::vector<Road*>& roadsGood, std::vector<int>& side)
{
	return false;
}

bool CreatorManager::snapp(QTEntity * qtEntity, float minDif, std::vector<QTEntity*>& entitiesColliding, std::vector<Vector3D>& pushes, std::vector<float>& ts)
{
	return false;
}

// isPossibleToMake

// Test si une route est constructible
// roadsGood repr�sente les routes en collision qui doivent �tre g�rer
// sides repr�sente le type de collision
bool CreatorManager::preIsMakableRoadSnapp(Road * road, std::vector<Road*>& roadsGood, std::vector<int>& sides)
{
	if (road->getHeight() < MIN_HEIGHT_ROAD)
		return false;

	// Approximation de la direction de la route ici ou avant
	// On regarde si la route est en collision avec un autre �l�ment qu'une route
	
	// 0) TEST COLLISION
	// R�cup�ration des �l�ments possiblement en collision
	// On traitera apr�s les routes des autres �l�ments
	// Les autres �l�ments ne doivent pas �tre en collision avec une route
	std::vector<QTEntity*> entities;

	gameStruct->QTCollision.retrieve(road->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On tente un cast en route, si le pointeur est diff�rent de NULL, c'est une route
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

	// Recup�ration des routes qui sont possiblement en collision
	std::vector<QTEntity*> roadsBefCast;
	std::vector<Road*> roads;
	std::vector<Road*> roadsColliding;

	myRectangle bigRectangle = road->getBigRectangle(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	sRectangle bigBound = bigRectangle.getBound();
	gameStruct->QTCollision.retrieve(bigBound, roadsBefCast);
	// Cast en roads
	for (unsigned i = 0; i < roadsBefCast.size(); i++)
	{
		QTEntity *test = roadsBefCast[i];
		Road *cast = dynamic_cast<Road*>(test);
		assert(cast != NULL); // Qu'est ce que fout cet objet qui n'est pas une route dans ces resultats?
		roads.push_back(cast);
	}

	// 1) TEST DE COLLISION DEBUT FIN
	// -> L'angle entre les deux routes doit �tre au minimum de 45�C
	myRectangle startColl = road->getStartColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	myRectangle endColl = road->getEndColl(DEF_WIDTH_ROAD, DEF_HEIGHT_ROAD);
	Vector3D director = road->getDirectorVec();
	std::vector<myRectangle> midColls = road->getMidColl(LESS_HEIGHT_MID_ROAD);
	for (unsigned i = 0; i < roads.size(); i++)
	{
		// On regarde si l'autre route est en collision avec le bigRectangle
		if (bigRectangle.isColliding((*roads[i]->getForm())))
		{
			// La route est en collision avec le d�but ou la fin?
			bool isStart = startColl.isColliding((*roads[i]->getForm()));
			bool isEnd = endColl.isColliding((*roads[i]->getForm()));
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
					else // La route est bonne, il faudra juste regarder qu'on peut arriver � y faire un snapp == Pas trop de routes 
					{
						roadsGood.push_back(roads[i]);
						if (isStart)
						{
							sides.push_back(0);
						}
						else
						{
							sides.push_back(1);
						}
					}
				}
				else
				{
					roadsColliding.push_back(roads[i]);
				}
			}
			else
			{
				roadsColliding.push_back(roads[i]);
			}
		}
	}

	//2) Pour tous les autres routes en collision
	Vector3D normalDirector = director.getPerpendicular2D();
	float scalarStartR = road->getStart()*normalDirector;
	float scalarEndR = road->getEnd()*normalDirector;

	for (unsigned i = 0; i < roadsColliding.size(); i++)
	{
		// On travaille par projection sur le vecteur normal au vecteur directeur
		float scalarStart = roadsColliding[i]->getStart()*normalDirector;
		float scalarEnd = roadsColliding[i]->getEnd()*normalDirector;

		// On regarde si y en a au moins un entre les deux
		bool isInStart = (scalarStart > scalarStartR && scalarStart < scalarEndR) || (scalarStart > scalarEndR && scalarStart < scalarStartR);
		bool isInEnd = (scalarEnd > scalarStartR && scalarEnd < scalarEndR) || (scalarEnd > scalarEndR && scalarEnd < scalarStartR);
	
		if (isInStart && isInEnd)
		{
			return false;
		}
		roadsGood.push_back(roadsColliding[i]);

		if (isInStart)
		{
			sides.push_back(2); // A gauche
		}
		else if (isInEnd)
		{
			sides.push_back(3); // A droite
		}
		else
		{
			sides.push_back(4); // traversant
		}
	}

	return true;

	// Ce qui change par rapport � l'autre fonction est seulement -> un recangle de collision plus grand
}

// Test si un qtEntity est faisable
// Pushes repr�sente liste de vecteurs de pouss�e normalis�s
// ts le facteur du vecteur pous�e
bool CreatorManager::preIsMakableSnapp(QTEntity * qtEntity, float minDif,  std::vector<QTEntity*>& entitiesNear, std::vector<Vector3D>& pushes, std::vector<float>& ts)
{
	// On r�cup�re juste l'ensemble des entit�s qui peuvent possiblement �tre en collision
	// On test si y a une collision 
	std::vector<QTEntity*> entities;

	gameStruct->QTCollision.retrieve(qtEntity->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getForm() != NULL)
		{
			Vector3D push;
			float t;
			if (qtEntity->getForm()->isColliding(*(entities[i]->getForm()), push, t))
			{
				if (t < minDif)
				{
					return false;
				}
				else
				{
					// En collision mais on peut un peu bouger
					entitiesNear.push_back(entities[i]);
					pushes.push_back(push);
					ts.push_back(t);
				}
			}
		}
	}

	return false;
}

bool CreatorManager::preIsMakableRoad(Road * road, std::vector<Road*>& roadsGood, std::vector<int>& sides)
{
	if (road->getHeight() < MIN_HEIGHT_ROAD)
		return false;

	// Approximation de la direction de la route ici ou avant
	// On regarde si la route est en collision avec un autre �l�ment qu'une route

	// 0) TEST COLLISION
	// R�cup�ration des �l�ments possiblement en collision
	// On traitera apr�s les routes des autres �l�ments
	// Les autres �l�ments ne doivent pas �tre en collision avec une route
	std::vector<QTEntity*> entities;

	gameStruct->QTCollision.retrieve(road->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On tente un cast en route, si le pointeur est diff�rent de NULL, c'est une route
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

	// Recup�ration des routes qui sont possiblement en collision
	std::vector<QTEntity*> roadsBefCast;
	std::vector<Road*> roads;
	std::vector<Road*> roadsColliding;

	myRectangle bigRectangle((*road->castMyRectangle()));
	sRectangle bigBound = bigRectangle.getBound();
	gameStruct->QTCollision.retrieve(bigBound, roadsBefCast);
	// Cast en roads
	for (unsigned i = 0; i < roadsBefCast.size(); i++)
	{
		QTEntity *test = roadsBefCast[i];
		Road *cast = dynamic_cast<Road*>(test);
		assert(cast != NULL); // Qu'est ce que fout cet objet qui n'est pas une route dans ces resultats?
		roads.push_back(cast);
	}

	// 1) TEST DE COLLISION DEBUT FIN
	// -> L'angle entre les deux routes doit �tre au minimum de 45�C
	myRectangle startColl = road->getStartColl(0, 0);
	myRectangle endColl = road->getEndColl(0, 0);
	Vector3D director = road->getDirectorVec();
	std::vector<myRectangle> midColls = road->getMidColl(0);
	for (unsigned i = 0; i < roads.size(); i++)
	{
		// On regarde si l'autre route est en collision avec le bigRectangle
		if (bigRectangle.isColliding((*roads[i]->getForm())))
		{
			// La route est en collision avec le d�but ou la fin?
			bool isStart = startColl.isColliding((*roads[i]->getForm()));
			bool isEnd = endColl.isColliding((*roads[i]->getForm()));
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
					else // La route est bonne, il faudra juste regarder qu'on peut arriver � y faire un snapp == Pas trop de routes 
					{
						roadsGood.push_back(roads[i]);
						if (isStart)
						{
							sides.push_back(0);
						}
						else
						{
							sides.push_back(1);
						}
					}
				}
				else
				{
					roadsColliding.push_back(roads[i]);
				}
			}
			else
			{
				roadsColliding.push_back(roads[i]);
			}
		}
	}

	//2) Pour tous les autres routes en collision
	Vector3D normalDirector = director.getPerpendicular2D();
	float scalarStartR = road->getStart()*normalDirector;
	float scalarEndR = road->getEnd()*normalDirector;

	for (unsigned i = 0; i < roadsColliding.size(); i++)
	{
		// On travaille par projection sur le vecteur normal au vecteur directeur
		float scalarStart = roadsColliding[i]->getStart()*normalDirector;
		float scalarEnd = roadsColliding[i]->getEnd()*normalDirector;

		// On regarde si y en a au moins un entre les deux
		bool isInStart = (scalarStart > scalarStartR && scalarStart < scalarEndR) || (scalarStart > scalarEndR && scalarStart < scalarStartR);
		bool isInEnd = (scalarEnd > scalarStartR && scalarEnd < scalarEndR) || (scalarEnd > scalarEndR && scalarEnd < scalarStartR);

		if (isInStart && isInEnd)
		{
			return false;
		}
		roadsGood.push_back(roadsColliding[i]);
		if (isInStart)
		{
			
			sides.push_back(2); // � gauche
		}
		else if (isInEnd)
		{
			sides.push_back(3); // � droite
		}
		else
		{
			sides.push_back(4); // traverse
		}
	}

	return true;
}

bool CreatorManager::preIsMakable(QTEntity * qtEntity)
{
	// On r�cup�re juste l'ensemble des entit�s qui peuvent possiblement �tre en collision
	// On test si y a une collision 
	std::vector<QTEntity*> entities;

	gameStruct->QTCollision.retrieve(qtEntity->getBounds(), entities);
	for (unsigned i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getForm() != NULL)
		{
			if (qtEntity->getForm()->isColliding(*(entities[i]->getForm())))
			{
				return false;
			}
		}
	}

	return false;
}


void CreatorManager::addGameStruct(QTEntity * qtEntity)
{
	// Ajout d'une entit� avec ses besoins
	// Si Ressource Elec ?? Eau ??
	// Si Habitation??
	gameStruct->QTCollision.insert(qtEntity);
}

void CreatorManager::addRoadGameStruct(Road * road)
{
	// Ajout d'une route
	gameStruct->QTCollision.insert(road);
	gameStruct->QTRoads.insert(road);
}

void CreatorManager::handleStartRoad(Road * road, Road * roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad)
{
	// Il faut r�cup�rer les 4 positions des �l�ments
	// Pour le moment c'est un rectangle
	// On verra apr�s si on passe en form

	// R�cup�ration du premier vecteur directeur
	Vector3D director1 = road->getDirectorVec();
	Vector3D director2 = roadSnapp->getDirectorVec();

	// On a d�j� la premi�re taille
	Vector3D roadSnappStart = roadSnapp->getStart();
	Vector3D roadSnappEnd = roadSnapp->getEnd();
	float widthRoadSnapp = roadSnapp->getWidth();
	float scalarStart1 = director1*roadSnappStart;
	float scalarEnd1 = director1*roadSnappEnd;

	// Pour avoir la l'autre taille
	Vector3D roadStart = road->getStart();
	Vector3D roadEnd = road->getEnd();
	float widthRoad = road->getWidth();
	float scalarStart2 = director2*roadStart;
	float scalarEnd2 = director2*roadEnd;

	Vector3D pEnd2 = director2*scalarStart2;
	Vector3D pStart2 = director2*scalarEnd2;


	Vector3D center = (pEnd2 + pStart2)*0.5f;

	float width = (float)abs(scalarStart1 - scalarEnd1);
	float height = (float)abs(scalarStart2 - scalarEnd2);
	// Pour le moment rectangle on verra apr�s pour la suite
	Road *connector = new Road(center, width, height, road->getAngle2D());

	Road *road2 = new Road();
	Road *road3 = new Road();
	Road *road4 = new Road();

	// On ajoute un par un chaque route
	// On remplace le start
	if (roadSnappStart < roadSnappEnd)
	{
		Vector3D pStart1 = director1*((float) max(scalarStart1, scalarEnd1));
		road2->set2points(pStart1, roadSnappEnd, widthRoadSnapp);
	}
	else
	{
		Vector3D pStart1 = director1*((float)min(scalarStart1, scalarEnd1));
		road2->set2points(pStart1, roadSnappEnd, widthRoadSnapp);
	}
	

	road3->set2points(roadStart, pEnd2, widthRoad);
	road4->set2points(pStart2, roadEnd, widthRoad);

	roads.push_back(connector);
	roads.push_back(road2);
	roads.push_back(road3);
	roads.push_back(road4);
}

void CreatorManager::handleEndRoad(Road * road, Road * roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad)
{
	// Il faut r�cup�rer les 4 positions des �l�ments
	// Pour le moment c'est un rectangle
	// On verra apr�s si on passe en form

	// R�cup�ration du premier vecteur directeur
	Vector3D director1 = road->getDirectorVec();
	Vector3D director2 = roadSnapp->getDirectorVec();

	// On a d�j� la premi�re taille
	Vector3D roadSnappStart = roadSnapp->getStart();
	Vector3D roadSnappEnd = roadSnapp->getEnd();
	float widthRoadSnapp = roadSnapp->getWidth();
	float scalarStart1 = director1*roadSnappStart;
	float scalarEnd1 = director1*roadSnappEnd;

	// Pour avoir la l'autre taille
	Vector3D roadStart = road->getStart();
	Vector3D roadEnd = road->getEnd();
	float widthRoad = road->getWidth();
	float scalarStart2 = director2*roadStart;
	float scalarEnd2 = director2*roadEnd;

	Vector3D pEnd2 = director2*scalarStart2;
	Vector3D pStart2 = director2*scalarEnd2;


	Vector3D center = (pEnd2 + pStart2)*0.5f;

	float width = (float)abs(scalarStart1 - scalarEnd1);
	float height = (float)abs(scalarStart2 - scalarEnd2);
	// Pour le moment rectangle on verra apr�s pour la suite
	Road *connector = new Road(center, width, height, road->getAngle2D());

	Road *road2 = new Road();
	Road *road3 = new Road();
	Road *road4 = new Road();

	// On ajoute un par un chaque route
	// On remplace le end
	if (roadSnappEnd < roadSnappStart) // Attention au sens
	{
		Vector3D pStart1 = director1*((float)max(scalarStart1, scalarEnd1));
		road2->set2points(pStart1, roadSnappEnd, widthRoadSnapp);
	}
	else
	{
		Vector3D pStart1 = director1*((float)min(scalarStart1, scalarEnd1));
		road2->set2points(pStart1, roadSnappEnd, widthRoadSnapp);
	}


	road3->set2points(roadStart, pEnd2, widthRoad);
	road4->set2points(pStart2, roadEnd, widthRoad);

	roads.push_back(connector);
	roads.push_back(road2);
	roads.push_back(road3);
	roads.push_back(road4);
}

void CreatorManager::handleCrossingRoad(Road * road, Road * roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad)
{
	// Il faut r�cup�rer les 4 positions des �l�ments
	// Pour le moment c'est un rectangle
	// On verra apr�s si on passe en form
	
	// R�cup�ration du premier vecteur directeur
	Vector3D director1 = road->getDirectorVec();
	Vector3D director2 = roadSnapp->getDirectorVec();

	// On a d�j� la premi�re taille
	Vector3D roadSnappStart = roadSnapp->getStart();
	Vector3D roadSnappEnd = roadSnapp->getEnd();
	float widthRoadSnapp = roadSnapp->getWidth();
	float scalarStart1 = director1*roadSnappStart;
	float scalarEnd1 = director1*roadSnappEnd;
	
	// Pour avoir la l'autre taille
	Vector3D roadStart = road->getStart();
	Vector3D roadEnd = road->getEnd();
	float widthRoad = road->getWidth();
	float scalarStart2 = director2*roadStart;
	float scalarEnd2 = director2*roadEnd;
	
	Vector3D pEnd1 = director1*scalarStart1;
	Vector3D pStart1 = director1*scalarEnd1;
	Vector3D pEnd2 = director2*scalarStart2;
	Vector3D pStart2 = director2*scalarEnd2;


	Vector3D center = (pEnd1 + pStart1)*0.5f;

	float width = (float)abs(scalarStart1 - scalarEnd1);
	float height = (float)abs(scalarStart2 - scalarEnd2);
	// Pour le moment rectangle on verra apr�s pour la suite
	Road *connector = new Road(center, width, height, road->getAngle2D());
	Road *road1 = new Road();
	Road *road2 = new Road();
	Road *road3 = new Road();
	Road *road4 = new Road();

	// On ajoute un par un chaque route
	road1->set2points(roadSnappStart, pEnd1, widthRoadSnapp);
	road2->set2points(pStart1, roadSnappEnd, widthRoadSnapp);

	road3->set2points(roadStart, pEnd2, widthRoad);
	road4->set2points(pStart2, roadEnd, widthRoad);

	roads.push_back(connector);
	roads.push_back(road1);
	roads.push_back(road2);
	roads.push_back(road3);
	roads.push_back(road4);
}





void CreatorManager::render(Graphics * g, const Vector3D translation)
{
}

LayerNs::LayerEvent CreatorManager::handleEvent(Input & input)
{
	assert(gameStruct != NULL);

	return LayerNs::LayerEvent();
}

void CreatorManager::recalculateAfterRemove(Road* road)
{
	// On commence par copier l'ensemble des roads connected
	std::deque<Road*> roads;
	
	if(road->sizeConnected() == 0)
		freeConnexitude(road.getConnexitude());
	
	for (unsigned i = 0; road->sizeConnected(); i++)
	{
		roads.push_back(road->getConnected(i));
	}

	// Au d�part on cr�e autant de groupe qu'
	for (unsigned i = 0; i < road->sizeConnected(); i++)
	{
		for (unsigned j = i + 1; j < road->sizeConnected(); j++)
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

	if (roads.size() < 2) // La suppression n'a rien chang�, ou plus de route
		return;

	// On laisse la topConnexitude au premier groupe d'�l�ment
	for (unsigned i = 0; i < roads.size(); i++)
	{
		setConnexitude(roads[i], getConnexitude());
	}

	// Il reste encore � checker si les g�n�rateurs connect�s sont connecter � des �l�ments avec un autre id
}

void CreatorManager::removeGameStruct(QTEntity * qtEntity)
{
}

void CreatorManager::removeRoadGameStruct(Road * road)
{
}


// Connexitude
// R�cup�ration de l'id connex le plus haut
int CreatorManager::getConnexitude()
{
	if (gameStruct->fConnexitudes.size() > 0)
	{
		int fConnex = gameStruct->fConnexitudes[gameStruct->fConnexitudes.size() - 1];
		gameStruct->fConnexitudes.pop_back();
		return fConnex;
	}

	return gameStruct->topConnexitude++;
}

// Lib�ration d'un id connexe
void CreatorManager::freeConnexitude(int n)
{
	gameStruct->fConnexitudes.push_back(n);
}

// Change l'id d'un groupe de routes � partir de son d�part
void CreatorManager::setConnexitude(Road* start, int connex)
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
		// On ajoute les �l�ments encore � faire
		for (unsigned i = 0; i < current->sizeConnected(); i++)
		{
			if (alreadyDone.find(current->getConnected(i)) != alreadyDone.end())
			{
				alreadyDone.insert(current->getConnected(i));
				toDo.insert(current->getConnected(i));
			}
		}
	}
}

bool CreatorManager::stillConnected(Road* start, Road* end)
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
		// On ajoute dans l'openList les �l�ments li�s � cette road
		// On commence par regarder si c'est un connecteur ou seulement une route
		
		// On r�cup�re celui avec la plus faible valeur
		Road* current = (openList.begin()->second);
		openList.erase(openList.begin());

		for (unsigned i = 0; i < current->sizeConnected(); i++)
		{
			Road* adding = current->getConnected(i);
			if (adding != end)
			{
				// Si pas d�j� dans d�j� trait�e ou d�j� pr�vu (openListBst)
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
	return isFound;
}



// Bien penser � tous les ajouts GenRes... + PollutionMaker