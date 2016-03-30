#include "Resources.h"

Resources::Resources(p_uint production, float radius) :
    m_production(production), m_consumption(0)
{
	this->radius = radius;
}

// ----- GETTER ----- //
sRectangle Resources::getBoundsCover() const
{
	return sRectangle::createSRectangleCenter(getCenter(), radius, radius);
}

float Resources::getRadius() const
{
    return radius;
}

unsigned Resources::sizeConnectedCons()
{
	return m_connected.size();
}

QTEntity * Resources::getConnectedCons(unsigned i)
{
	return m_connected[i];
}

// ----- SETTER ----- //
bool Resources::addConsumer(QTEntity* entity, p_uint consumption)
{
    if (consumption + m_consumption > m_production) {
        return false;
    } else {
        m_connected.push_back(entity);
        m_consumption += consumption;
        return true;
    }
}

QTEntity * Resources::eraseCons(unsigned i)
{
	QTEntity* save = m_connected[i];
	m_connected.erase(m_connected.begin() + i);
	return save;
}

bool Resources::eraseCons(QTEntity * qtEntity)
{
	unsigned i = 0;
	while (i < m_connected.size() && qtEntity != m_connected[i])
	{
		i++;
	}
	if (i < m_connected.size())
	{
		m_connected.erase(m_connected.begin() + i);
		return true;
	}
	std::cout << "Road not found in connector";
	return false;
}