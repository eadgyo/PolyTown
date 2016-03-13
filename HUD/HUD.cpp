#include "HUD.h"

#include <iostream>

HUD::HUD()
{
	// Cr�ation de l'outil graphique
	g = new Graphics();
}

HUD::~HUD()
{
	// Suppression de l'outil graphique
	delete g;
}

void HUD::initialize(std::string name, int width, int height)
{
	// Cr�ation de la fenetre
	g->init(name, width, height);
	g->initGL(width, height);

	// Cr�ation de toutes les interfaces
	// Menu
	interfaces.push_back(new Menu());
	interfaces.push_back(new NewGame());

	// Initialisation des boutons
	for (unsigned i = 0; i < interfaces.size(); i++)
	{
		interfaces[i]->initialize(width, height);
	}

	// On initialise la pile en ajoutant le Menu
	iStack.push_back(interfaces[0]);
}

void HUD::render()
{
	checkStack();

	// On reset l'�cran
	g->clear();

	// On rend le dernier �l�ment
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
	HudEvent result = iStack.back()->handleEvent(input);

	if (result % NEW_GAME)
	{
		iStack.push_back(interfaces[1]);
	}
	if (result % LOAD_GAME)
	{

	}
}

void HUD::checkStack()
{
	if (iStack.size() == 0)
		std::cerr << "Error: HUD Stack is empty !! Bitches ain't my type.";
}
