#include "MapLayer.h"

MapLayer::MapLayer(Graphics* g) : Layer(g)
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::initialize(int x, int y, int width, int height, int deltaSide, GameStruct* gs)
{
	Layer::initialize(x, y, width, height, gs);
	this->deltaSide = deltaSide;
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
	std::vector<QTEntity*> entities;

	if (gs->tempEntity != NULL)
	{
		gs->tempEntity->getCenter().display();
		gs->QTCollision.retrieve(gs->tempEntity, entities);
	}
	std::cout << entities.size() << std::endl;

	g->translate(-gs->zoneToDisplay.getLeft());

	for (unsigned i = 0; i < entities.size(); i++)
	{
		g->setColor(myColor(0.2f, 0.2f, 0.2f));
		g->render(*(entities[i]->getForm()));

		g->setColor(myColor::RED());
		sRectangle test = entities[i]->getBounds();
		g->drawForm(test);
	}
	
	// Affichage de l'élément qui peut être dessiner
	if (gs->tempEntity != NULL)
	{
		if (gs->isLastMakable)
		{
			g->setColor(myColor::GREEN());
		}
		else
		{
			g->setColor(myColor::RED());
		}
		g->render(*(gs->tempEntity->getForm()));


	}

	gs->QTCollision.draw(g);

	sRectangle recA(0, 0, 100, 100);
	g->render(recA);
	g->translate(gs->zoneToDisplay.getLeft());
	
	g->translate(-rec.getLeft());
}


bool MapLayer::create()
{
	QTEntityBuild* castBuild = dynamic_cast<QTEntityBuild*>(gs->tempEntity);
	Road* castRoad = dynamic_cast<Road*>(gs->tempEntity);
	if (castBuild != NULL)
	{
		if (cm->add(castBuild))
			gs->tempEntity = NULL;
	}
	else if (castRoad != NULL)
	{
		if(cm->addRoad(castRoad))
			gs->tempEntity = NULL;
	}

	return true;
}

bool MapLayer::isMakable()
{
	QTEntityBuild* castBuild = dynamic_cast<QTEntityBuild*>(gs->tempEntity);
	Road* castRoad = dynamic_cast<Road*>(gs->tempEntity);
	if (castBuild != NULL)
	{
		return cm->isMakableSnapp(castBuild);
	}
	else if (castRoad != NULL)
	{
		return cm->isMakableSnappRoad(castRoad);
	}

	return false;
}

void MapLayer::updateRoad(const Vector3D& mousePos)
{
	// Création de la route
	if (gs->roadState == -1)
	{
		gs->tempEntity = StructFactory::newRoad((int) mousePos.x(), (int) mousePos.y(),
			(int) mousePos.x(), (int) mousePos.y(), 50);
		gs->roadState = 0;
	}
	else if(gs->roadState == 0)
	{
		Road* cast = dynamic_cast<Road*>(gs->tempEntity);
		cast->set2points(mousePos, mousePos, 50);
	}
	else
	{
		Road* cast = dynamic_cast<Road*>(gs->tempEntity);
		cast->set2points(cast->getStart(), mousePos, 50);
	}
}

void MapLayer::updateEntity(const Vector3D& mousePos)
{
	Vector3D l_mousePos = gs->zoneToDisplay.getLeft() + mousePos;
	if (gs->state != -1 && gs->stateIn != -1)
	{
		if (gs->roadState == -1 && gs->tempEntity != NULL)
		{
			delete gs->tempEntity;
		}
		
		switch (gs->state)
		{
		// Roads
		case 0:
			switch (gs->stateIn)
			{
			case 0:
				updateRoad(l_mousePos);
				break;
			}
			break;

		// House
		case 1:
			switch (gs->stateIn)
			{
			case 0:
				gs->tempEntity = StructFactory::newHouse((int) l_mousePos.x(), (int) l_mousePos.y());
				break;
			}

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;

		default:
			break;
		};

		gs->isLastMakable = isMakable();
	}
	else
	{
		gs->tempEntity = NULL;
	}
}

void MapLayer::setPos(const Vector3D & mousePos)
{
	Vector3D l_mousePos = mousePos;
	// On change la position de la zone d'affichage
	// D'abord on borne la souris
	float widthZ = gs->zoneToDisplay.getWidth()*0.5f;
	float heightZ = gs->zoneToDisplay.getHeight()*0.5f;
	if (l_mousePos.x() < widthZ - deltaSide)
	{
		l_mousePos.setX(widthZ - deltaSide);
	}
	else if (l_mousePos.x() > gs->mapRec.getWidth() - widthZ + deltaSide)
	{
		l_mousePos.setX(gs->mapRec.getWidth() - widthZ + deltaSide);
	}

	if (l_mousePos.y() < heightZ - deltaSide)
	{
		l_mousePos.setY(heightZ - deltaSide);
	}
	else if (l_mousePos.y() > gs->mapRec.getHeight() - heightZ + deltaSide)
	{
		l_mousePos.setY(gs->mapRec.getHeight() - heightZ + deltaSide);
	}

	// On change le centre de la zone d'affichage
	gs->zoneToDisplay.setCenter(l_mousePos);
}

void MapLayer::translate(const Vector3D& translate)
{
	setPos(gs->zoneToDisplay.getCenter() + translate);
}

LayerNs::LayerEvent MapLayer::handleEvent(Input & input, const Vector3D& translation)
{
	Vector3D trans = rec.getLeft() + translation;
	Vector3D mousePos = input.getMousePos();
	mousePos -= trans;

	updateEntity(mousePos);
	
	float facX = 0.15f;
	float facY = 0.15f;

	float deltaX = 0;
	float deltaY = 0;
	if (mousePos.x() < rec.getWidth() * facX)
	{
		deltaX = mousePos.x() - rec.getWidth() * facX;
	}
	else if (mousePos.x() > rec.getWidth() * (1.0f - facX))
	{
		deltaX = mousePos.x() - rec.getWidth() * (1.0f - facX);
	}

	if (mousePos.y() < rec.getHeight() * facX)
	{
		deltaY = mousePos.y() - rec.getHeight() * facX;
	}
	else if (mousePos.y() > rec.getHeight() * (1.0f - facY))
	{
		deltaY = mousePos.y() - rec.getHeight() * (1.0f - facY);
	}

	if (deltaX != 0 || deltaY != 0)
	{
		translate(Vector3D(deltaX, deltaY, 0, false));
	}

	if (input.getMousePressed(0))
	{
		if (gs->state != -1 && gs->stateIn != -1)
		{
			if (gs->state == 0)
			{
				if (gs->roadState == 0)
				{
					std::cout << "Premier point" << std::endl;
					gs->roadState = 1;
				}
				else if (gs->roadState == 1)
				{
					std::cout << "Second point" << std::endl;
					create();
					gs->roadState = -1;
				}
			}
			else
			{
				create();
			}
		}
	}
	

	return LayerNs::NOCOLLISION;
}
