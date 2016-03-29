#include "Resources.h"

Resources::Resources(p_uint production, float radius) :
    m_production(production)
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