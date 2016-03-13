#include "BottomLayer.h"

BottomLayer::BottomLayer()
{

}

void BottomLayer::initialize(float x, float y, int width, int height)
{
	translate.set(x, y, 0, 0);
	// Création des infrastructures
	int addX = width / 16;
	int posX = addX;
	int posY = height / 2;
	
	int sizeBW = addX / 2;
	int sizeBH = addX / 2;
	// Routes
	Bouton *routesB = new Bouton("R", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(routesB);
	// Zones
	Bouton *zonesB = new Bouton("Z", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(zonesB);
	// Energies
	Bouton *energB = new Bouton("En", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(energB);
	// Traitement des déchets
	Bouton *dechB = new Bouton("D", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(dechB);
	// Traitement et stockage des eaux
	Bouton *eauxB = new Bouton("Ea", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(eauxB);
	// Etablissement
	Bouton *etablB = new Bouton("Et", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(etablB);
	// Destruction


	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->setColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	isInitialized = true;
}

void BottomLayer::reset()
{

}

void BottomLayer::resize(int width, int height)
{
}

void BottomLayer::render(Graphics * g)
{
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->render(g, translate);
	}
}

void BottomLayer::render(Graphics * g, const Vector3D translation)
{

}

void BottomLayer::update(float dt)
{

}

LayerNs::LayerEvent BottomLayer::handleEvent(Input & input)
{
	if (input.getLastEvent() == SDL_MOUSEBUTTONUP && input.getMousePressed(0))
	{
		const int *mousePosI = input.getMousePos();
		Vector3D mousePos((float)mousePosI[0], (float)mousePosI[1], 0, true);
		mousePos -= translate;
		for (unsigned i = 0; i < boutons.size(); i++)
		{
			if (boutons[i]->isColliding(mousePos))
			{
				return LayerNs::COLLISION;
			}
		}
	}
	return LayerNs::NOCOLLISION;
}
