#include "Road.h"

Road::Road()
{
	initRectangle();
}

Road::Road(const Vector3D& center, const Vector3D& length)
{
	initRectangle(center, length);
}

Road::Road(const Vector3D& center, const Vector3D& length, float theta)
{
	initRectangle(center, length, theta);
}

Road Road::create2points(const Vector3D& A, const Vector3D& B, float width)
{
	Road road;
	float height = (A - B).getMagnitude();
	road.set2points(A, B, Vector3D(width, height));
	return road;
}

Road Road::createLeft(const Vector3D& left, const Vector3D& length)
{
	Vector3D center = left + length*0.5f;
	center.setW(1.0f);
	return Road(center, length, 0);
}

Vector3D Road::getStart() const
{
	// On prend le coté dont la taille est la plus petite
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();
	if (side0 < side1)
	{
		return (get(0) + get(1))*0.5f;
	}
	else
	{
		return (get(3) + get(0))*0.5f;
	}
}

Vector3D Road::getEnd() const
{
	// On prend le coté dont la taille est la plus petite
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();
	if (side0 < side1)
	{
		return (get(2) + get(3))*0.5f;
	}
	else
	{
		return (get(1) + get(2))*0.5f;
	}
}

Vector3D Road::get(unsigned n) const
{
	return form->get(n);
}

Vector3D Road::getDirectorVec() const
{
	// On retourne juste la distance entre 2 points Start End
	Vector3D director = getEnd() - getStart();
	director.normalize();
	return director;
}

Vector3D Road::getLeftCenter() const
{
	// On prend le coté dont la taille est la plus grande
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();
	if (side0 > side1)
	{
		return (get(0) + get(1))*0.5f;
	}
	else
	{
		return (get(3) + get(0))*0.5f;
	}
}


Vector3D Road::getRightCenter() const
{
	// On prend le coté dont la taille est la plus grande
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();
	if (side0 > side1)
	{
		return (get(2) + get(3))*0.5f;
	}
	else
	{
		return (get(1) + get(2))*0.5f;
	}
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
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();

	// Width est la largeur
	// Height est la longueur
	if (side0 < side1)
	{
		width = side0;
		height = side1;
	}
	else
	{
		width = side1;
		height = side0;
	}
}

Vector3D Road::getCenter() const
{
	return form->getCenter();
}

myRectangle Road::getStartColl(float defWidth, float defHeight) const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL); // La forme n'existe pas

	// Création d'un rectangle englobant le début
	float width, height;
	getLength(width, height);

	Vector3D start = getStart();
	return myRectangle(start, defWidth, defHeight, getAngle2D());
}

myRectangle Road::getEndColl(float defWidth, float defHeight) const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL); // La forme n'existe pas

	// Création d'un rectangle englobant la fin
	float width, height;
	getLength(width, height);

	Vector3D end = getEnd();
	return myRectangle(end, defWidth, defHeight, getAngle2D());
}

myRectangle Road::getRect() const
{
	const myRectangle* rec = castMyRectangleConst();
	assert(rec != NULL);
	return (*rec);
}

std::vector<myRectangle> Road::getMidColl(float defHeight) const
{
	std::vector<myRectangle> midColl;
	float width, height;
	float side0 = (get(0) - get(1)).getMagnitude();
	float side1 = (get(1) - get(2)).getMagnitude();
	bool inf = side0 < side1;
	if (inf)
	{
		width = side0;
		height = side1;
	}
	else
	{
		width = side1;
		height = side0;
	}
	assert(height > defHeight);


	if (height < 3 * defHeight)
	{
		// On a 2 rectangles
		Vector3D center = getCenter();
		
		if (inf)
		{
			side1 -= defHeight;
		}
		else
		{
			side0 -= defHeight;
		}
		Vector3D director = getDirectorVec();
		Vector3D length(side0, side1);
		// Un premier rectangle avec le center
		float theta = getAngle2D();
		midColl.push_back(myRectangle(center - director*defHeight, length, theta));
		midColl.push_back(myRectangle(center + director*defHeight, length, theta));
	}
	else
	{
		// Un seul rectangle
		Vector3D center = getCenter();
		// On a juste à raccourcir le rectangle en enlevant 2 fois defHeight
		if (inf)
		{
			side1 -= defHeight * 2;
		}
		else
		{
			side0 -= defHeight * 2;
		}
		Vector3D length(side0, side1);
		midColl.push_back(myRectangle(center, length, getAngle2D()));
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


bool Road::isColliding(Form& form)
{
	return form.collisionSat(*(this->form));
}

bool Road::isColliding(Form& form, Vector3D& push, float& t)
{
	return form.collisionSat(*(this->form), Vector3D(false), Vector3D(false), push, t);
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