#include "HUD.h"

#include <iostream>

HUD::HUD()
{
	// Création de l'outil graphique
	g = new Graphics();
}

HUD::~HUD()
{
	// Suppression de l'outil graphique
	delete g;
}

void HUD::initialize(std::string name, int width, int height)
{
	// Création de la fenetre
	g->init(name, width, height);
	g->initGL(width, height);

	// Création de toutes les interfaces
	// Menu
	interfaces.push_back(new Menu());

	// Initialisation des boutons
	for (unsigned i = 0; i < interfaces.size(); i++)
	{
		interfaces[i]->initialize(width, height);
	}

	// On initialise la pile
	iStack.push_back(interfaces[0]);
}

void HUD::render()
{
	checkStack();

	// On reset l'écran
	g->clear();

	// On rend le dernier élément
	iStack.back()->render(g);
	
	// Swap buffer
	g->swapGL();
}

void HUD::exitGame()
{
}

void HUD::update(float dt)
{
	checkStack();

	iStack.back()->update(dt);
}

void HUD::checkEvent()
{
	checkStack();
	std::cout << "CheckEvent" << std::endl;
	HudEvent result = iStack.back()->handleEvent(input);

	if (result % NEW_GAME)
	{
		std::cout << "New Game";
	}
}

void HUD::checkStack()
{
	if (iStack.size() == 0)
		std::cerr << "Error: HUD Stack is empty !! Bitches ain't my type.";
}
