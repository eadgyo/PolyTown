#include "QTEntityBuild.h"

QTEntityBuild::QTEntityBuild(std::string name, const Form& form) : QTEntity(form)
{
	this->m_name = name;
}
QTEntityBuild::QTEntityBuild(const Form& form)
{
	this->form = new Form(form);
	this->m_name = "";
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, float width, float height)
{
	form = NULL;
	initRectangle(center, width, height);
	this->m_name = "";
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, float width, float height, float theta)
{
	form = NULL;
	initRectangle(center, width, height, theta);
	this->m_name = "";
}
QTEntityBuild::QTEntityBuild(const Vector3D& center, float radius)
{
	form = NULL;
	initCircle(center, radius);
	this->m_name = "";
}

QTEntityBuild::QTEntityBuild(const myRectangle& rectangle)
{
	form = NULL;
	form = new myRectangle(rectangle);
	this->m_name = "";
}
QTEntityBuild::QTEntityBuild(const Circle& circle)
{
	form = NULL;
	form = new Circle(circle);
	this->m_name = "";
}


unsigned QTEntityBuild::sizeConnected() const
{
	return connected.size();
}

Road * QTEntityBuild::getConnected(unsigned n) const
{
	return connected[n];
}

int QTEntityBuild::getMinConnex()
{
	int connex = -1;
	for (unsigned i = 0; i < connected.size(); i++)
	{
		if (connex == -1 || connected[i]->getConnexitude() < connex)
		{
			connex = connected[i]->getConnexitude();
		}
	}
	return connex;
}

std::set<int> QTEntityBuild::getConnexes()
{
	std::set<int> connexes;
	for (unsigned i = 0; i < connected.size(); i++)
	{
		if (connected[i]->getConnexitude() != -1 && connexes.find(connected[i]->getConnexitude()) == connexes.end())
		{
			connexes.insert(connected[i]->getConnexitude());
		}
	}
	return connexes;
}

bool QTEntityBuild::isConnected(QTEntityBuild * qtEntity)
{
	std::set<int> connexes = qtEntity->getConnexes();
	for (unsigned i = 0; i < connected.size(); i++)
	{
		if (connected[i]->getConnexitude() != -1 &&
			connexes.find(connected[i]->getConnexitude()) != connexes.end())
		{
			return true;
		}
	}
	return false;
}

void QTEntityBuild::addRoad(Road * road)
{
	connected.push_back(road);
}

Road* QTEntityBuild::removeRoad(unsigned i)
{
	Road* save = connected[i];
	connected.erase(connected.begin() + i);
	return save;
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