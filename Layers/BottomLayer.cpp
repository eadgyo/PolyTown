#include "BottomLayer.h"

BottomLayer::BottomLayer()
{

}

void BottomLayer::initialize(float x, float y, int width, int height)
{
	// Cr�ation des infrastructures
	// Routes
	Bouton *Bouton = new Bouton("R", posX, startY, SIZE_BW, SIZE_BH);
	// Zones

	// Energies

	// Traitement des d�chets

	// Traitement et stockage des eaux

	// Etablissement


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

}

void BottomLayer::render(Graphics * g, const Vector3D translation)
{

}

void BottomLayer::update(float dt)
{

}

LayerNs::LayerEvent BottomLayer::handleEvent(Input & input)
{
	return LayerNs::LayerEvent();
}
