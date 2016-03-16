#include "HUD.h"

#include <iostream>

HUD::HUD()
{
	// Cr�ation de l'outil graphique
    FileManager& fileM = FileManager::getInstance();
    fileM.initialize();
    g = new Graphics();
    g->loadAllSurfaces();
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
	interfaces.push_back(new Game());

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

	Image image;
	image.initialize(g, 250, 50, 0, "Untitled.png");
	image.setCurrentFrame(1);
	//image.flipH(Vector3D(true));
	image.scale(1.0f, Vector3D(true));
	image.setPositionX(500);
	image.setPositionY(500);
	image.setVisible(255.0f);
	

	// On rend le dernier �l�ment
	//iStack.back()->render(g);
	
	image.draw();

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
