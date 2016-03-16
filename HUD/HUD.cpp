#include "HUD.h"

#include <iostream>

HUD::HUD()
{
	// Création de l'outil graphique
    FileManager& fileM = FileManager::getInstance();
    g = new Graphics();
	//initialize
    //g->loadAllSurfaces();
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
	iStack.push_back(interfaces[0]);
}
void HUD::clear()
{
	// On reset l'écran
	g->clear();
}
void HUD::render()
{
	checkStack();
	// On rend le dernier élément
	iStack.back()->render(g);
}

void HUD::swap()
{
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
