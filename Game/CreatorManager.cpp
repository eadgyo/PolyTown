#include "CreatorManager.h"

#define DEF_WIDTH_ROAD 10.0f
#define DEF_HEIGHT_ROAD 10.0f
#define LESS_HEIGHT_MID_ROAD 10.0f

#define MIN_HEIGHT_ROAD 5.0f
#define MIN_ANGLE2D 0.25f

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
			if (entities[i]->getForm() != NULL && road->getRect().isColliding(*(entities[i]->getForm())))
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
