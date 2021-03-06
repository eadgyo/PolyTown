#include "MapLayer.h"

MapLayer::MapLayer(Graphics* g) : Layer(g)
{
	round = new Image(g, 128, 128, 0, "LeftLayer.png");
	round->setSize(32);
}

MapLayer::~MapLayer()
{
}

void MapLayer::initialize(int x, int y, int width, int height, int deltaSide, GameStruct* gs)
{
	Layer::initialize(x, y, width, height, gs);
	this->deltaSide = deltaSide;
}

bool MapLayer::back()
{
	if (gs->roadState == 1 && gs->state == 0)
	{
		gs->roadState = 0;
		return false;
	}
	else
	{
		gs->roadState = -1;
		return true;
	}
}

void MapLayer::reset()
{
	gs->roadState = -1;
}

void MapLayer::update(float dt)
{
}

void MapLayer::render(Graphics * g)
{
	g->setColor(myColor(0.2f, 0.6f, 0.2f, 0.3f));
	g->render(rec);

	g->translate(rec.getLeft());

	// Scale
	float scale = rec.getWidth() / gs->zoneToDisplay.getWidth();
	
	g->scale(scale);
	

	// Rendu des images
	std::vector<QTEntity*> entities;

	gs->QTCollision.retrieve(gs->zoneToDisplay, entities);
	
	g->translate(-gs->zoneToDisplay.getLeft());

	renderElements(g, entities);
	renderTempEntity(g, entities);
	renderSelected(g);

	// Rendu debug
	if (gs->isDebugRoad)
	{
		renderConnexitude(g, entities);
		renderLinkRoad(g, entities);
	}
	if (gs->isDebugQuadTree)
	{
		g->setColor(myColor::RED());
		gs->QTCollision.draw(g);
	}
	if (gs->isDebugEntity)
	{
		renderConnexitudeBuilding(g, entities);
	}
	if (gs->isDebugGenResLink)
	{
		renderGenResLink(g, entities);
	}
	
	g->setColor(myColor::RED());
	g->drawForm(gs->QTCollision.getRec());

	g->translate(gs->zoneToDisplay.getLeft());

	g->scale(1/scale);
	
	g->translate(-rec.getLeft());
}

void MapLayer::renderElements(Graphics * g, std::vector<QTEntity*> entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On regarde si l'�l�ment est une route
		Road* cast = dynamic_cast<Road*>(entities[i]);
		if (cast != NULL)
		{
			g->setColor(myColor(0.3f, 0.3f, 0.3f));
			g->render(*(cast->getForm()));

			myRectangle line = myRectangle::create2points(cast->getStart(), cast->getEnd(), 5);
			g->setColor(myColor::WHITE(0.4f));
			g->render(line);
		}
		else
		{
			QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(entities[i]);
			if (cast != NULL && cast->getName().size() > 5)
			{
				g->setColor((float)(cast->getName()[2] + cast->getName()[3] - 128) / 128,
					(float)(cast->getName()[0] + cast->getName()[4] - 128) / 128,
					(float)(cast->getName()[5] + cast->getName()[1] - 128) / 128);
			}
			else if (cast != NULL && cast->getName().size() > 2)
			{
				g->setColor((float)(cast->getName()[0] - 64) / 64,
					(float)(cast->getName()[1] - 64) / 64,
					(float)(cast->getName()[2] - 64) / 64);
			}
			else
				g->setColor(myColor(0.2f, 0.2f, 0.2f));

			g->render(*(entities[i]->getForm()));
			g->setColor(myColor(0.0f, 0.0f, 0.0f));
			g->setLineSize(1.5f);
			g->drawForm(*(entities[i]->getForm()));
			g->setLineSize(1.0f);
			
			if (cast != NULL)
			{
				
				Vector3D director = cast->getDirectorVec();
				Image* image = g->createImageFromFont("test", 15, cast->getName());
				image->setPos(cast->getCenter() + director*cast->castMyRectangle()->getWidth()*0.3f);
				image->setColor(myColor(0.0f, 0.0f, 0.0f, 1.0f));
				image->setRadians(-cast->getAngle2D());
				image->draw(g);
				delete image;
			}
		}
	}
}

void MapLayer::renderSelected(Graphics * g)
{
	if (gs->lastSelected != NULL)
	{
		g->setColor(myColor(0.45f, 0.5f, 0.38f, 0.5f));
		g->render(*(gs->lastSelected->getForm()));
	}
}

void MapLayer::renderTempEntity(Graphics * g, std::vector<QTEntity*> entities)
{
	// Affichage de l'�l�ment qui peut �tre dessiner
	if (gs->tempEntity != NULL)
	{
		if (gs->isLastMakable)
		{
			g->setColor(myColor::GREEN(0.5f));
		}
		else
		{
			g->setColor(myColor::RED(0.5f));
		}
		g->render(*(gs->tempEntity->getForm()));
		g->drawForm(*(gs->tempEntity->getForm()));

		for (unsigned i = 0; i < entities.size(); i++)
		{
			if (entities[i]->isColliding(*(gs->tempEntity->getForm())))
			{
				g->setColor(myColor::RED(0.3f));
				g->render(*(entities[i]->getForm()));
			}
		}
	}
}

void MapLayer::renderConnexitude(Graphics * g, std::vector<QTEntity*> entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On regarde si l'�l�ment est une route
		Road* cast = dynamic_cast<Road*>(entities[i]);
		if (cast != NULL)
		{
			g->renderTextCenteredTTF("test", std::to_string(cast->getConnexitude()), myColor::BLACK(), cast->getCenter(), 20);
		}
	}
}

void MapLayer::renderLinkRoad(Graphics * g, std::vector<QTEntity*> entities)
{
	myColor defaultColor = myColor(0.2f, 1.0f, 0.2f);
	g->setColor(defaultColor);
	g->setLineSize(3.0f);
	float defDist = 10.0f;

	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On regarde si l'�l�ment est une route
		Road* cast = dynamic_cast<Road*>(entities[i]);
		if (cast != NULL)
		{
			Connector* castCo = dynamic_cast<Connector*>(entities[i]);

			if (castCo != NULL)
			{
				Vector3D center = castCo->getCenter();
				for (unsigned i = 0; i < castCo->sizeConnectedRoad(); i++)
				{
					Vector3D otherPoint;
					bool result = castCo->guessPointFromConnected(i, otherPoint);
					Vector3D director = (otherPoint - center).getNormalize();
					Vector3D p0 = otherPoint - director*min(defDist, castCo->getWidth()*0.2f);
					Vector3D p1 = otherPoint + director*min(defDist, castCo->getConnectedRoad(i)->getHeight()*0.2f);
					
					if(result)
						g->drawLine(p0, p1);
					else
					{
						g->setColor(myColor::RED());
						g->drawLine(p0, p1);
						g->setColor(defaultColor);
					}
					
				}
			}
			else
			{
				if (cast->getLast() != NULL && dynamic_cast<Connector*>(cast->getLast()) == NULL)
				{
					Vector3D start0 = cast->getStart();
					Vector3D director0 = cast->getDirectorVec();
					Vector3D otherPoint;
					Vector3D director1;
				
					bool result = cast->getLastRoadPoint(otherPoint, director1);
					Vector3D p0 = otherPoint + director0*min(defDist, cast->getHeight()*0.2f);
					Vector3D p1 = otherPoint + director1*min(defDist, cast->getLast()->getHeight()*0.2f);

					if (result)
						g->drawLine(p0, p1);
					else
					{
						g->setColor(myColor::RED());
						g->drawLine(p0, p1);
						g->setColor(defaultColor);
					}

				}
				if (cast->getNext() != NULL && dynamic_cast<Connector*>(cast->getNext()) == NULL)
				{
					Vector3D end0 = cast->getEnd();
					Vector3D director0 = -cast->getDirectorVec();
					Vector3D otherPoint;
					Vector3D director1;

					bool result = cast->getNextRoadPoint(otherPoint, director1);
					Vector3D p0 = otherPoint + director0*min(defDist, cast->getHeight()*0.2f);
					Vector3D p1 = otherPoint + director1*min(defDist, cast->getNext()->getHeight()*0.2f);

					if (result)
						g->drawLine(p0, p1);
					else
					{
						g->setColor(myColor::RED());
						g->drawLine(p0, p1);
						g->setColor(defaultColor);
					}
				}
			}

		}
	}

	g->setLineSize(1.0f);
}

void MapLayer::renderConnexitudeBuilding(Graphics* g, std::vector<QTEntity*> entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On regarde si l'�l�ment est une route
		QTEntityBuild* cast = dynamic_cast<QTEntityBuild*>(entities[i]);
		if (cast != NULL)
		{
			g->renderTextCenteredTTF("test", std::to_string(cast->getMinConnex()), myColor::BLACK(), cast->getCenter(), 20);
		}
	}
}

void MapLayer::renderGenResLink(Graphics * g, std::vector<QTEntity*> entities)
{
	myColor waterColor(0.2f, 0.4f, 1.0f, 0.8f);
	myColor EnergyColor(0.7f, 0.7f, 0.1f, 0.8f);

	// Rendu des liens entre g�n�rateurs et consommateurs
	for (unsigned i = 0; i < entities.size(); i++)
	{
		// On regarde si c'est un consommateur ou un g�n�rateur
		Energy* energy = dynamic_cast<Energy*>(entities[i]);
		Water* water = dynamic_cast<Water*>(entities[i]);
		Resources* res = dynamic_cast<Resources*>(entities[i]);
		if (water != NULL)
		{
			if (!water->hasWater())
			{
				Vector3D director = entities[i]->getDirectorVec().getPerpendicular2D();
				round->setColor(waterColor);
				round->setPos(entities[i]->getCenter() + director*round->getWidth() * 0.8f);
				round->draw(g);
			}
			else
			{
				g->setColor(waterColor);
				g->setLineSize(2.0f);
				Vector3D p0 = entities[i]->getCenter();
				Vector3D p1 = water->getWaterTower()->getCenter();
				g->drawLine(p0, p1);
				g->setLineSize(1.0f);
			}
		}
		if (energy != NULL)
		{
			if (!energy->hasEnergy())
			{
				Vector3D director = entities[i]->getDirectorVec().getPerpendicular2D();
				round->setColor(EnergyColor);
				round->setPos(entities[i]->getCenter() - director*round->getWidth() * 0.8f);
				round->draw(g);
			}
			else
			{
				g->setColor(EnergyColor);
				g->setLineSize(2.0f);
				Vector3D p0 = entities[i]->getCenter();
				Vector3D p1 = energy->getPowerPlant()->getCenter();
				g->drawLine(p0, p1);
				g->setLineSize(1.0f);
			}
		}
			
		if (res != NULL)
		{
			if (dynamic_cast<PowerPlant*>(res) != NULL)
			{
				g->setColor(EnergyColor);
			}
			else
			{
				g->setColor(waterColor);
			}
			g->setLineSize(2.0f);
			for (unsigned j = 0; j < res->sizeConnectedCons(); j++)
			{
				Vector3D p0 = entities[i]->getCenter();
				Vector3D p1 = res->getConnectedCons(j)->getCenter();
				g->drawLine(p0, p1);
			}
			g->setLineSize(1.0f);
		}
		
	}
	g->setColor(myColor::BLACK());
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

bool MapLayer::remove()
{
	if (gs->lastSelected == NULL)
		return false;

	QTEntityBuild* castBuild = dynamic_cast<QTEntityBuild*>(gs->lastSelected);
	Road* castRoad = dynamic_cast<Road*>(gs->lastSelected);
	if (castBuild != NULL)
	{
		cm->remove(castBuild);
	}
	else if (castRoad != NULL)
	{
		cm->removeRoad(castRoad);
	}
	gs->lastSelected = NULL;
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
	// Cr�ation de la route
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

void MapLayer::updateSelected(const Vector3D & mousePos)
{
	sRectangle recMouse(mousePos.x() - 1.0f, mousePos.y() - 1.0f, 2.0f, 2.0f);
	std::vector<QTEntity*> entities;
	gs->QTCollision.retrieve(recMouse, entities);
	unsigned i = 0;
	
	while(i < entities.size() && gs->lastSelected == NULL)
	{
		if ((*entities[i]->getForm()).isColliding(recMouse))
			gs->lastSelected = entities[i];
		i++;
	}
}

void MapLayer::handleLeftClick()
{
	if (gs->state != -1 && gs->stateIn != -1)
	{
		if (gs->state == 0)
		{
			if (gs->roadState == 0)
			{
				gs->roadState = 1;
			}
			else if (gs->roadState == 1)
			{
				create();
				gs->roadState = -1;
			}
		}
		else if (gs->state == 8)
		{
			remove();
		}
		else
		{
			create();
		}
	}
}

void MapLayer::handleMouseWheel(int mouseWheelY, const Vector3D& mousePos)
{
	float factor;
	if (mouseWheelY < 0)
	{
		factor = 1.5f*abs(mouseWheelY);
	}
	else
	{
		factor = 1.0f / 1.5f*abs(mouseWheelY);
	}

	scale(factor, mousePos);
}

void MapLayer::updateEntity(const Vector3D& mousePos)
{
	Vector3D l_mousePos;
	gs->lastSelected = NULL;
	if(isUpdating)
		l_mousePos.set(gs->zoneToDisplay.getLeft() + mousePos*(gs->zoneToDisplay.getWidth()/rec.getWidth()));
	else
		l_mousePos.set(lastMousePos);


	if (gs->state != -1 && gs->stateIn != -1)
	{

		if (gs->roadState == -1 && gs->tempEntity != NULL)
		{
			delete gs->tempEntity;
			gs->tempEntity = NULL;
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
                case 1:
                    gs->tempEntity = StructFactory::newLowImpactHouse((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 2:
                    gs->tempEntity = StructFactory::newBuilding((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 3:
                    gs->tempEntity = StructFactory::newLowImpactBuilding((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
            }
            break;
        case 2:
            switch (gs->stateIn) 
			{
                case 0:
                    gs->tempEntity = StructFactory::newManufactory((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 1:
                    gs->tempEntity = StructFactory::newShop((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 2:
                    gs->tempEntity = StructFactory::newFarm((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
            }
            break;
        case 3:
            switch (gs->stateIn)
			{
                case 0:
                    gs->tempEntity = StructFactory::newPoliceStation((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 1:
                    gs->tempEntity = StructFactory::newFireStation((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 2:
                    gs->tempEntity = StructFactory::newSchool((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 3:
                    gs->tempEntity = StructFactory::newHospital((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
            }
            break;
        case 4:
            switch (gs->stateIn) 
			{
                case 0:
                    gs->tempEntity = StructFactory::newStadium((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 1:
                    gs->tempEntity = StructFactory::newCinema((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
                case 2:
                    gs->tempEntity = StructFactory::newPark((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
            }
            break;
        case 5:
            switch (gs->stateIn) 
			{
                case 0:
                    gs->tempEntity = StructFactory::newPowerPlant((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
				case 1:
					gs->tempEntity = StructFactory::newPowerPlant((int)l_mousePos.x(), (int)l_mousePos.y());
					break;
				case 2:
					gs->tempEntity = StructFactory::newPowerPlant((int)l_mousePos.x(), (int)l_mousePos.y());
					break;
            }
            break;
        case 6:
            switch (gs->stateIn) 
			{
                case 0:
                    gs->tempEntity = StructFactory::newWaterTower((int) l_mousePos.x(), (int) l_mousePos.y());
                    break;
            }
			break;
		case 7:
			break;
		case 8:
			updateSelected(l_mousePos);
			break;

		default:
			break;
		};
		if(gs->tempEntity != NULL)
			gs->isLastMakable = isMakable();
	}
	else
	{
		gs->tempEntity = NULL;
	}
}

void MapLayer::scale(float scale, const Vector3D& mousePos)
{
	float widthFac = gs->mapRec.getWidth() / (scale*gs->zoneToDisplay.getWidth());
	float heightFac = gs->mapRec.getHeight() / (scale*gs->zoneToDisplay.getHeight());
	
	float widthFacScreen = rec.getWidth() / (scale*gs->zoneToDisplay.getWidth());
	float heightFacScreen = rec.getHeight() / (scale*gs->zoneToDisplay.getHeight());

	if (widthFacScreen >= MAX_SCALE_SCREEN || heightFacScreen >= MAX_SCALE_SCREEN)
	{
		gs->zoneToDisplay.scaleF(scale*min(widthFacScreen, heightFacScreen)/MAX_SCALE_SCREEN, transformMouse(mousePos));
	}
	if (widthFac >= 1.0f && heightFac >= 1.0f)
	{
		gs->zoneToDisplay.scaleF(scale, transformMouse(mousePos));
	}
	else
	{
		gs->zoneToDisplay.scaleF(scale*min(widthFac, heightFac), transformMouse(mousePos));
	}
	setPos(gs->zoneToDisplay.getCenter());
}

Vector3D MapLayer::transformMouse(const Vector3D& mousePos)
{
	return gs->zoneToDisplay.getLeft() + mousePos*(gs->zoneToDisplay.getWidth() / rec.getWidth());
}

void MapLayer::handleMouseTranslation(const Vector3D & mousePos)
{
	if (!canTranslate)
		return;

	float facX = 0.10f;
	float facY = 0.10f;

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
	
	if (input.getMouseWheelY() != 0)
	{
		handleMouseWheel(input.getMouseWheelY(), mousePos);
	}

	if (input.getKeyPressed(1))
	{
		lastMousePos.set(gs->zoneToDisplay.getLeft() + mousePos);
		isUpdating = !isUpdating;
	}

	handleMouseTranslation(mousePos);

	if (input.getMousePressed(0))
	{
		handleLeftClick();
	}
	
	updateEntity(mousePos);
	canTranslate = true;
	return LayerNs::NOCOLLISION;
}
