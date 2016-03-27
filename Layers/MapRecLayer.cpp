#include "MapRecLayer.h"



MapRecLayer::MapRecLayer(Graphics* g) : Layer(g)
{
}


MapRecLayer::~MapRecLayer()
{
}

void MapRecLayer::initialize(int x, int y, int widthScreen, int heightScreen, int sizeMapX, int sizeMapY, int width, float factorMap)
{
	float factorScreen = width / (float) sizeMapX;
	this->factorMap = factorMap;
	Layer::initialize(x, y, (int) (sizeMapX*factorScreen + 0.5f), (int) (sizeMapY*factorScreen + 0.5f));
	
	zoneToDisplay.set((float) x, (float) y, (float) widthScreen, (float) heightScreen);
	mapRec.set(0, 0, (float) sizeMapX, (float) sizeMapY);
	zoneToDisplay.setLeft(0.0f, 0.0f, (float) widthScreen, (float) heightScreen);
}

void MapRecLayer::update(float dt)
{
}

void MapRecLayer::render(Graphics * g)
{
	sRectangle recA = rec;
	g->setColor(myColor(0.2f, 0.2f, 0.2f, 0.3f));
	g->render(recA);

	g->translate(rec.getLeft());
	
	float factor = rec.getWidth() / mapRec.getWidth();
	

	sRectangle l_mapRec = mapRec.clone();
	l_mapRec.scaleF(factor*factorMap, Vector3D(0, 0));
	Vector3D translate = Vector3D(rec.getWidth()*(1 - factorMap)*0.5f, rec.getHeight()*(1 - factorMap)*0.5f) - l_mapRec.getLeft();
	l_mapRec.translate(translate);

	sRectangle l_zoneToDisplay = zoneToDisplay.clone();
	l_zoneToDisplay.scaleF(factor, Vector3D(0, 0));
	Vector3D translate2 = Vector3D(true) - l_zoneToDisplay.getLeft();



	g->setColor(0.2f, 0.2f, 0.2f, 0.4f);
	g->render(l_mapRec);
	
	g->setColor(0.2f, 0.2f, 0.2f, 0.8f);
	g->render(l_zoneToDisplay);

	g->translate(-rec.getLeft());
}

LayerNs::LayerEvent MapRecLayer::handleEvent(Input & input, const Vector3D& translation)
{
	Vector3D trans = rec.getLeft() + translation;
	if (input.getMouseDown(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= trans;
		setPos(mousePos);
		return LayerNs::COLLISION;
	}
	

	return LayerNs::NOCOLLISION;
}

void MapRecLayer::setPos(const Vector3D & mousePos)
{
	Vector3D l_mousePos = mousePos;
	float factor = rec.getWidth() / mapRec.getWidth();
	// On change la position de la zone d'affichage
	// D'abord on borne la souris
	float widthZ = zoneToDisplay.getWidth()*0.5f*factor;
	float heightZ = zoneToDisplay.getHeight()*0.5f*factor;
	if (l_mousePos.x() < widthZ)
	{
		l_mousePos.setX(widthZ);
	}
	else if (l_mousePos.x() > rec.getWidth() - widthZ)
	{
		l_mousePos.setX(rec.getWidth() - widthZ);
	}

	if (l_mousePos.y() < heightZ)
	{
		l_mousePos.setY(heightZ);
	}
	else if (l_mousePos.y() > rec.getHeight() - heightZ)
	{
		l_mousePos.setY(rec.getHeight() - heightZ);
	}

	// On change le centre de la zone d'affichage
	zoneToDisplay.setCenter(l_mousePos/factor);
}

void MapRecLayer::setScale(float scale)
{
	float factor = rec.getWidth()*factorMap / mapRec.getWidth();
	Vector3D center = zoneToDisplay.getCenter()*factor;
	
	zoneToDisplay.scaleF(scale, rec.getCenter());

	setPos(center);
}