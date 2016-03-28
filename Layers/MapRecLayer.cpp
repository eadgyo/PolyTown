#include "MapRecLayer.h"



MapRecLayer::MapRecLayer(Graphics* g) : Layer(g)
{
}


MapRecLayer::~MapRecLayer()
{
}

void MapRecLayer::initialize(int x, int y, int widthScreen, int heightScreen, int sizeMapX, int sizeMapY, int width, int deltaSide, GameStruct* gs)
{
	float factorScreen = width / (float) sizeMapX;
	this->deltaSide = deltaSide;
	Layer::initialize(x, y, (int) (sizeMapX*factorScreen + 0.5f), (int) (sizeMapY*factorScreen + 0.5f), gs);
	
	gs->zoneToDisplay.set((float) x, (float) y, (float) widthScreen, (float) heightScreen);
	gs->mapRec.set(0, 0, (float) sizeMapX, (float) sizeMapY);
	gs->zoneToDisplay.setLeft(0.0f, 0.0f, (float) widthScreen, (float) heightScreen);
}

void MapRecLayer::update(float dt)
{
}

void MapRecLayer::render(Graphics * g)
{
	sRectangle recA = rec;
	g->setColor(myColor(0.2f, 0.2f, 0.2f, 0.3f));
	g->render(recA);
	g->setColor(1.0f, 1.0f, 1.0f, 0.8f);
	g->drawForm(recA);

	g->translate(rec.getLeft());
	
	float factor = rec.getWidth() / (gs->mapRec.getWidth() + deltaSide*2);
	float factorY = rec.getHeight() / (gs->mapRec.getHeight() + deltaSide * 2);

	sRectangle l_mapRec = sRectangle::createSRectangleCenter(Vector3D(rec.getWidth()*0.5f , rec.getHeight()*0.5f),
		gs->mapRec.getWidth()*factor, gs->mapRec.getHeight()*factorY);


	// sRectangle l_zoneToDisplay = gs->zoneToDisplay;
	sRectangle l_zoneToDisplay = sRectangle::createSRectangleCenter(Vector3D(gs->zoneToDisplay.getCenterX()*factor, gs->zoneToDisplay.getCenterY()*factor),
		gs->zoneToDisplay.getWidth()*factor, gs->zoneToDisplay.getHeight()*factorY);

	Vector3D translate2 = Vector3D(deltaSide*factor, deltaSide*factorY);
	l_zoneToDisplay.translate(translate2);

	g->setColor(0.2f, 0.2f, 0.2f, 0.4f);
	g->render(l_mapRec);
	g->setColor(1.0f, 1.0f, 1.0f, 0.2f);
	g->drawForm(l_mapRec);
	
	g->setColor(0.2f, 0.2f, 0.2f, 0.8f);
	g->render(l_zoneToDisplay);
	g->setColor(1.0f, 1.0f, 1.0f, 0.8f);
	g->drawForm(l_zoneToDisplay);

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
	float factor = rec.getWidth() / (gs->mapRec.getWidth() + 2 * deltaSide);
	float factorY = rec.getHeight() / (gs->mapRec.getHeight() + 2 * deltaSide);
	// On change la position de la zone d'affichage
	// D'abord on borne la souris
	float widthZ = gs->zoneToDisplay.getWidth()*0.5f*factor;
	float heightZ = gs->zoneToDisplay.getHeight()*0.5f*factorY;
	if (l_mousePos.x() < widthZ - deltaSide*factor)
	{
		l_mousePos.setX(widthZ - deltaSide*factor);
	}
	else if (l_mousePos.x() > rec.getWidth() - widthZ - deltaSide*factor)
	{
		l_mousePos.setX(rec.getWidth() - widthZ - deltaSide*factor);
	}

	if (l_mousePos.y() < heightZ - deltaSide*factorY)
	{
		l_mousePos.setY(heightZ - deltaSide*factorY);
	}
	else if (l_mousePos.y() > rec.getHeight() - heightZ - deltaSide*factorY)
	{
		l_mousePos.setY(rec.getHeight() - heightZ - deltaSide*factorY);
	}

	// On change le centre de la zone d'affichage
	gs->zoneToDisplay.setCenter(l_mousePos/factor);
}

void MapRecLayer::setScale(float scale)
{
	float factor = rec.getWidth() / (gs->mapRec.getWidth() * 2 * deltaSide);
	Vector3D center = gs->zoneToDisplay.getCenter()*factor;
	
	gs->zoneToDisplay.scaleF(scale, rec.getCenter());

	setPos(center);
}
