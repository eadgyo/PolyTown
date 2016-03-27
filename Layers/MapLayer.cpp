#include "MapLayer.h"

MapLayer::MapLayer(Graphics* g) : Layer(g), mapRecLayer(g)
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::initialize(int x, int y, int width, int height, int widthScreen, int heightScreen, int sizeMapX, int sizeMapY)
{
	Layer::initialize(x, y, width, height);
	mapRecLayer.initialize(
		(int)(POS_X_FACTOR_REC_MAP*width),
		(int)(POS_Y_FACTOR_REC_MAP*height),
		widthScreen,
		heightScreen,
		sizeMapX,
		sizeMapY,
		(int) (width*SIZE_FACTOR_REC_MAP),
		0.9f);
}

void MapLayer::update(float dt)
{
}

void MapLayer::render(Graphics * g)
{
	g->translate(rec.getLeft());
	mapRecLayer.render(g);
	g->translate(-rec.getLeft());
}

LayerNs::LayerEvent MapLayer::handleEvent(Input & input, const Vector3D& translation)
{
	Vector3D trans = rec.getLeft() + translation;
	if (input.getMouseDown(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= trans;

		if (mapRecLayer.isColliding(mousePos))
		{
			mapRecLayer.handleEvent(input, translation);
		}
	}

	return LayerNs::NOCOLLISION;
}
