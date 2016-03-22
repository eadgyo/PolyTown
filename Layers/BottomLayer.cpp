#include "BottomLayer.h"

BottomLayer::BottomLayer(Graphics* g) : Layer(g)
{

}

void BottomLayer::initialize(float x, float y, int width, int height)
{
	translate.set(x, y, 0, 0);
	// Création des infrastructures
	int addX = width / 8;
	int posX = addX;
	int posY = height / 2;
	
	int sizeBW = addX / 2;
	int sizeBH = addX / 2;
	// Routes
	Image* roadI = new Image();
	roadI->initialize(graphics, 128, 128, 0, 2, "BottomLayer.png");
	roadI->setSize(sizeBW);

	Bouton *routesB = new BoutonImage(graphics, roadI, posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(routesB);
	// Zones
	Image* zoneI = new Image();
	zoneI->initialize(graphics, 128, 128, 1, 3, "BottomLayer.png");
	zoneI->setSize(sizeBW);
	
	Bouton *zonesB = new BoutonImage(graphics, zoneI, posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(zonesB);
	// Energies
	Bouton *energB = new BoutonText(graphics, "En", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(energB);
	// Traitement des déchets
	Bouton *dechB = new BoutonText(graphics, "D", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(dechB);
	// Traitement et stockage des eaux
	Bouton *eauxB = new BoutonText(graphics, "Ea", posX, posY, sizeBW, sizeBH);
	posX += addX;
	boutons.push_back(eauxB);
	// Etablissement
	Bouton *etablB = new BoutonText(graphics, "Et", posX, posY, sizeBW, sizeBH);
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
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();
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
