#include "QTEntityBuild.h"

QTEntityBuild::QTEntityBuild(std::string name, const Form& form) : QTEntity(form)
{
	this->name = name;
}
QTEntityBuild::QTEntityBuild(const Form& form)
{
	this->form = new Form(form);
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, const Vector3D& length)
{
	form = NULL;
	initRectangle(center, length);
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, const Vector3D& length, float theta)
{
	form = NULL;
	initRectangle(center, length, theta);
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, float radius)
{
	form = NULL;
	initCircle(center, radius);
}

QTEntityBuild::QTEntityBuild(const myRectangle& rectangle)
{
	form = NULL;
	form = new myRectangle(rectangle);
}
QTEntityBuild::QTEntityBuild(const Circle& circle)
{
	form = NULL;
	form = new Circle(circle);
}


unsigned QTEntityBuild::sizeConnected() const
{
	return connected.size();
}

Road * QTEntityBuild::getConnected(unsigned n) const
{
	return connected[n];
}

void QTEntityBuild::addRoad(Road * road)
{
	connected.push_back(road);
}

void QTEntityBuild::removeRoad(unsigned i)
{
	connected.erase(connected.begin() + i);
}

bool QTEntityBuild::removeRoad(Road* road)
{
	unsigned i = 0;
	while (i < connected.size() && road != connected[i])
	{
		i++;
	}
	if (i < connected.size())
	{
		connected.erase(connected.begin() + i);
		return true;
	}
	return false;
}