#include "HUD.h"

HUD::HUD()
{
	g = new Graphics();
}


void HUD::initialize(std::string name, int width, int height)
{
	// Créaition de la fenetre
	g->init(name, width, height);

}

void HUD::render()
{

}

void HUD::exitGame()
{
}

void HUD::update(float dt)
{
}

void HUD::collisions()
{
}
