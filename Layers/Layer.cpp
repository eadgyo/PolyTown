#include "Layer.h"

void Layer::initialize(int x, int y, int width, int height)
{
	rec.setLeft((float)x, (float)y, (float)width, (float)height);
}

bool Layer::isColliding(const Vector3D& mousePos)
{
	return rec.isColliding(mousePos);
}
