#include "Road.h"

Road::Road()
{
	connex = -1;
	initRectangle();
}

Road::Road(const Vector3D& center, float width, float height)
{
	connex = -1;
	initRectangle(center, width, height);
}

Road::Road(const Vector3D& center, float width, float height, float theta)
{
	connex = -1;
	initRectangle(center, width, height, theta);
}

Road Road::create2points(const Vector3D& A, const Vector3D& B, float width)
{
	Road road;
	float height = (A - B).getMagnitude();
	road.set2points(A, B, width, height);
	return road;
}

Road* Road::create2pointsP(const Vector3D& A, const Vector3D& B, float width)
{
	Road *road = new Road;
	float height = (A - B).getMagnitude();
	road->set2points(A, B, width, height);
	return road;
}

Road Road::createLeft(const Vector3D& left, float width, float height)
{
	Vector3D center = Vector3D(left.x() + width*0.5f, left.x() + height*0.5f);
	center.setW(1.0f);
	return Road(center, width, height, 0);
}

Vector3D Road::getStart() const
{
	return (get(0) + get(3))*0.5f;
}

Vector3D Road::getEnd() const
{
	return (get(1) + get(2))*0.5f;
}

Vector3D Road::get(unsigned n) const
{
	return form->get(n);
}

Vector3D Road::getDirectorVec() const
{
	// On retourne juste la distance entre 2 points Start End
	Vector3D director = (get(0) - get(1)).getNormalize();
	return director;
}

Vector3D Road::getLeftCenter() const
{
	return (get(0) + get(1))*0.5f;
}


Vector3D Road::getRightCenter() const
{
	return (get(2) + get(3))*0.5f;
}

float Road::getAngle2D() const
{
	Vector3D director = getDirectorVec();
	return director.getAngle2D(Vector3D(1, 0, 0, false));
}
float Road::getWidth() const
{
	float width, height;
	getLength(width, height);
	return width;
}
float Road::getHeight() const
{
	float width, height;
	getLength(width, height);
	return height;
}
Vector3D Road::getLength() const
{
	Vector3D vec(true);
	getLength(vec[0], vec[1]);
	return vec;
}

void Road::getLength(float& width, float& height) const
{
	const myRectangle *rec = castMyRectangleConst();
	width = rec->getWidth();
	height = rec->getHeight();
}

Vector3D Road::getCenter() const
{
	return form->getCenter();
}

myRectangle Road::getStartColl(float addWidth, float defHeight) const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL); // La forme n'existe pas

	// Création d'un rectangle englobant le début
	float width, height;
	getLength(width, height);

	Vector3D start = getStart();
	return myRectangle(start, addWidth + width, defHeight, getAngle2D());
}

myRectangle Road::getEndColl(float addWidth, float defHeight) const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL); // La forme n'existe pas

	// Création d'un rectangle englobant la fin
	float width, height;
	getLength(width, height);

	Vector3D end = getEnd();
	return myRectangle(end, addWidth + width, defHeight, getAngle2D());
}

myRectangle Road::getRect() const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL);
	return (*rec);
}

myRectangle Road::getBigRectangle(float defWidth, float defHeight) const
{
	float width = getWidth() + defWidth;
	float height = defHeight;
	return myRectangle(getCenter(), width, height, getAngle2D());
}



std::vector<myRectangle> Road::getMidColl(float defHeight) const
{
	std::vector<myRectangle> midColl;
	float width = getWidth();
	float height = getHeight();
	assert(height > defHeight);


	if (height < 3 * defHeight)
	{
		// On a 2 rectangles
		Vector3D center = getCenter();
		Vector3D director = getDirectorVec();

		// Un premier rectangle avec le center
		float theta = getAngle2D();
		midColl.push_back(myRectangle(center - director*defHeight, width, height-defHeight, theta));
		midColl.push_back(myRectangle(center + director*defHeight, width, height-defHeight, theta));
	}
	else
	{
		// On a juste à raccourcir le rectangle en enlevant 2 fois defHeight
		Vector3D center = getCenter();
		midColl.push_back(myRectangle(center, width, height-defHeight*2, getAngle2D()));
	}
	return midColl;
}

std::set<QTEntity*> Road::getEntConnected() const
{
	return entConnected;
}



std::vector<QTEntity*> Road::getEntConnectedVec() const
{
	// Deprecated
	std::set<QTEntity*>::iterator it = entConnected.begin();
	std::vector<QTEntity*> entities;
	while (it != entConnected.end())
	{
		entities.push_back((*it));
		std::advance(it, 1);
	}

	return entities;
}
QTEntity* Road::getEnt(unsigned n) const
{ 
	std::set<QTEntity*>::iterator it = entConnected.begin();
	std::advance(it, n);
	return *it;
}





// Setter
void Road::setStart(const Vector3D& start, float minHeight)
{
	// il faut vérifier que c'est possible
	// On vérifie que le start est dans le bon sens
	// Et que la longueur est supérieure à longueur min
	Vector3D director = getDirectorVec();
	Vector3D end = getEnd();
	Vector3D newDirector = end - start;
	float scalar = newDirector*director;
	if (scalar > minHeight) // sens > 0 && scalar > minHeight
	{
		// On peut bouger
		myRectangle* rec = castMyRectangle();
		assert(rec != NULL); // Pas de form
		set2points(start, end, getWidth());
	}
}

// Setter
void Road::setStart(const Vector3D& start)
{
	setStart(start, MIN_HEIGHT);
}

void Road::setEnd(const Vector3D& end, float minHeight)
{
	// il faut vérifier que c'est possible
	// On vérifie que le start est dans le bon sens
	// Et que la longueur est supérieure à longueur min
	Vector3D director = getDirectorVec();
	Vector3D start = getStart();
	Vector3D newDirector = end - start;
	float scalar = newDirector*director;
	if (scalar > minHeight) // sens > 0 && scalar > minHeight
	{
		// On peut bouger
		myRectangle* rec = castMyRectangle();
		assert(rec != NULL); // Pas de form
		set2points(start, end, getWidth());
	}
}
void Road::setEnd(const Vector3D& end)
{
	setEnd(end, MIN_HEIGHT);
}

void Road::setStartMove(const Vector3D& start)
{
	Vector3D translate = start - getStart();
	form->translate(translate);
}

void Road::setEndMove(const Vector3D& end)
{
	Vector3D translate = end - getEnd();
	form->translate(translate);
}

void Road::erase(QTEntity* entity)
{
	std::set<QTEntity*>::iterator it = entConnected.find(entity);
	if (it != entConnected.end())
	{
		entConnected.erase(it);
	}
}

void Road::erase(unsigned i)
{
	std::set<QTEntity*>::iterator it = entConnected.begin();
	std::advance(it, i);
	if (it != entConnected.end())
	{
		entConnected.erase(it);
	}
}

void Road::addEntity(QTEntity* entity)
{
	entConnected.insert(entity);
}

void Road::addAllEntities(std::vector<QTEntity*> entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		addEntity(entities[i]);
	}
}

bool Road::removeConnectedRoad(Road* road)
{
	if (last == road)
	{
		last = NULL;
		return true;
	}
	if (next == road)
	{
		next = NULL;
		return false;
	}
	// Probleme ?
	std::cout << "No road found";
}