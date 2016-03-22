#include "NewGame.h"



NewGame::NewGame(Graphics *g) : Interface(g)
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
	std::string boutonsTexte[] = { "Démarrer La partie", "Back",  ""};
	
	// Création de démarrer la partie
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

HudNs::HudEvent NewGame::update(float dt)
{
	return HudNs::OK;
}

HudNs::HudEvent NewGame::handleEvent(Input & input)
{
	return HudNs::HudEvent();
}


