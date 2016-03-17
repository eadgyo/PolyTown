#include "CreatorManager.h"

#define DEF_WIDTH_ROAD 10.0f
#define DEF_HEIGHT_ROAD 10.0f
#define LESS_HEIGHT_MID_ROAD 10.0f

#define MIN_HEIGHT_ROAD 5.0f
#define MIN_ANGLE2D 0.25f

CreatorManager::CreatorManager()
{
	gameStruct = NULL;
	topConnexitude = 0;
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

// Test si une route est constructible
// roadsGood représente les routes en collision qui doivent être gérer
// sides représente le type de collision
bool CreatorManager::isMakableRoad(Road * road, std::vector<Road*> roadsGood, std::vector<int> sides)
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
					else // La route est bonne, il faudra juste regarder qu'on peut arriver à y faire un snapp == Pas trop de routes 
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
		if (isInStart)
		{
			roadsGood.push_back(roadsColliding[i]);
			sides.push_back(2);
		}
		else if (isInEnd)
		{
			roadsGood.push_back(roadsColliding[i]);
			sides.push_back(3);
		}
		else
		{
			roadsGood.push_back(roadsColliding[i]);
			sides.push_back(4);
		}
	}

	return true;
}

// Test si un qtEntity est faisable
// Pushes représente liste de vecteurs de poussée normalisés
// ts le facteur du vecteur pousée
bool CreatorManager::isMakable(QTEntity * qtEntity, float minDif,  std::vector<QTEntity*> entitiesNear, std::vector<Vector3D> pushes, std::vector<float> ts)
{
	// On récupère juste l'ensemble des entités qui peuvent possiblement être en collision
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
	// On commence par copier l'ensemble des roads connected
	std::deque<Road*> roads;

	for (unsigned i = 0; road->sizeConnected(); i++)
	{
		roads.push_back(road->getConnected(i));
	}

	// Au départ on crée autant de groupe qu'
	for (unsigned i = 0; i < road->sizeConnected(); i++)
	{
		for (unsigned j = i+1; j < road->sizeConnected(); j++)
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

// Récupération de l'id connex le plus haut
int CreatorManager::getConnexitude()
{
	if (fConnexitudes.size() > 0)
	{
		int fConnex = fConnexitudes[fConnexitudes.size() - 1];
		fConnexitudes.pop_back();
		return fConnex;
	}

	return topConnexitude++;
}

// Libération d'un id connexe
void CreatorManager::freeConnexitude(int n)
{
	fConnexitudes.push_back(n);
}

// Change l'id d'un groupe de routes à partir de son départ
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
		// On ajoute les éléments encore à faire
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
		// On ajoute dans l'openList les éléments liés à cette road
		// On commence par regarder si c'est un connecteur ou seulement une route
		
		// On récupère celui avec la plus faible valeur
		Road* current = (openList.begin()->second);
		openList.erase(openList.begin());

		for (unsigned i = 0; i < current->sizeConnected(); i++)
		{
			Road* adding = current->getConnected(i);
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
	return isFound;
}


void CreatorManager::addRoad(Road * road)
{
	// Ajout entités en collision avec une boite de collision
}


// Bien penser à tous les ajouts GenRes... + PollutionMaker