#include "Resources.h"

Resources::Resources(float radius)
{
	this->radius = radius;
}

sRectangle Resources::getBoundsCover() const
{
	return sRectangle::createSRectangleCenter(getCenter(), radius, radius);
}
