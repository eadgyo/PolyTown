#include "LeftLayer.h"

LeftLayer::LeftLayer(Graphics* g) : Layer(g)
{
	state = -1;
	stateIn = 1;
}

void LeftLayer::initialize(float x, float y, int width, int height)
{
	translate.set(x, y, 0, 0);
	// Création des infrastructures
	int addY = height / 8;
	int posX = width / 4;
	int posY = addY;
	
	int sizeBW = addY / 2;
	int sizeBH = addY / 2;
	// Routes
	Image* roadI = new Image();
	roadI->initialize(graphics, 128, 128, 0, 2, "LeftLayer.png");
	roadI->setSize(sizeBW);

	Bouton *routesB = new BoutonImage(graphics, roadI, posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(routesB);
	// Zones
	Image* zoneI = new Image();
	zoneI->initialize(graphics, 128, 128, 1, 3, "LeftLayer.png");
	zoneI->setSize(sizeBW);
	
	Bouton *zonesB = new BoutonImage(graphics, zoneI, posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(zonesB);
	// Energies
	Bouton *energB = new BoutonText(graphics, "En", posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(energB);
	// Traitement des déchets
	Bouton *dechB = new BoutonText(graphics, "D", posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(dechB);
	// Traitement et stockage des eaux
	Bouton *eauxB = new BoutonText(graphics, "Ea", posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(eauxB);
	// Etablissement
	Bouton *etablB = new BoutonText(graphics, "Et", posX, posY, sizeBW, sizeBH);
	posY += addY;
	boutons.push_back(etablB);
	// Destruction


	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->setColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	isInitialized = true;
}

void LeftLayer::reset()
{

}

void LeftLayer::resize(int width, int height)
{
}

void LeftLayer::render(Graphics * g)
{
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		if(i != state)
			boutons[i]->render(g, translate);
		else
		{
			myColor color = boutons[i]->getColor();
			myColor remplacement;
			remplacement.r = color.r * 1.7f;
			remplacement.g = color.g * 1.7f;
			remplacement.b = color.b * 1.7f;
			remplacement.a = 1.0f;
			boutons[i]->setColor(remplacement);
			boutons[i]->render(g, translate);
			boutons[i]->setColor(color);
		}
	}
}

void LeftLayer::render(Graphics * g, const Vector3D translation)
{

}

void LeftLayer::update(float dt)
{

}

LayerNs::LayerEvent LeftLayer::handleEvent(Input & input)
{
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= translate;
		for (unsigned i = 0; i < boutons.size(); i++)
		{
			if (boutons[i]->isColliding(mousePos))
			{
				state = i;
				return LayerNs::COLLISION;
			}
		}
	}
	return LayerNs::NOCOLLISION;
}
