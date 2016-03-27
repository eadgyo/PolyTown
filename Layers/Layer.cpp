#include "Layer.h"

void Layer::initialize(int x, int y, int width, int height, GameStruct* gs)
{
	rec.setLeft((float)x, (float)y, (float)width, (float)height);
	this->gs = gs;
}

bool Layer::isColliding(const Vector3D& mousePos)
{
	return rec.isColliding(mousePos);
}
