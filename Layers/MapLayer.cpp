#include "MapLayer.h"

MapLayer::MapLayer(Graphics* g) : Layer(g)
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::initialize(int x, int y, int width, int height, GameStruct* gs)
{
	Layer::initialize(x, y, width, height, gs);

}

void MapLayer::update(float dt)
{
}

void MapLayer::render(Graphics * g)
{
	g->setColor(myColor(0.2f, 0.6f, 0.2f, 0.3f));
	g->render(rec);

	g->translate(rec.getLeft());
	
	// Rendu des images

	g->translate(-rec.getLeft());
}


LayerNs::LayerEvent MapLayer::handleEvent(Input & input, const Vector3D& translation)
{
	Vector3D trans = rec.getLeft() + translation;
	if (input.getMouseDown(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= trans;


	}

	return LayerNs::NOCOLLISION;
}
