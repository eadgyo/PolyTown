#include "NewGame.h"



NewGame::NewGame()
{	
}


NewGame::~NewGame()
{
}

void NewGame::initialize(int width, int height)
{
	if (isInitialized)
		return;

	// Initialisation des noms des boutons
	std::string boutonsTexte[] = { "D�marrer La partie", "Back",  ""};
	
	// Cr�ation de d�marrer la partie
	//Bouton* bouton = new Bouton(boutonsTexte[0], )
	isInitialized = true;
}

void NewGame::reset()
{
}

void NewGame::resize(int width, int height)
{
}

void NewGame::render(Graphics * g)
{
}

void NewGame::update(float dt)
{
}

HudEvent NewGame::handleEvent(Input & input)
{
	return HudEvent();
}


