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
	interfaces.push_back(new NewGame());
	interfaces.push_back(new Game());

	// Initialisation des boutons
	for (unsigned i = 0; i < interfaces.size(); i++)
	{
		interfaces[i]->initialize(width, height);
	}

	// On initialise la pile en ajoutant le Menu
	iStack.push_back(interfaces[2]);
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
	HudNs::HudEvent result = iStack.back()->handleEvent(input);

	if (result % HudNs::NEW_GAME)
	{
		iStack.push_back(interfaces[1]);
	}
	if (result % HudNs::LOAD_GAME)
	{

	}
}

void HUD::checkStack()
{
	if (iStack.size() == 0)
		std::cerr << "Error: HUD Stack is empty !! Bitches ain't my type.";
}
