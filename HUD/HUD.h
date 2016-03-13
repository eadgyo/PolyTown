#pragma once

#include "Input.h"
#include <deque>
#include <vector>
#include "../Interfaces/Interface.h"
#include "../Interfaces/Menu.h"
#include "../Graphics/Graphics.h"


class HUD
{
public:
	HUD();
	virtual ~HUD();
	// Création de la fenetre et des graphics
	void initialize(std::string name, int width, int height);
	// Rendu sur la fenetre
	void render();
	// Fin du Jeu
	void exitGame();
	// Mise à jour graphique
	void update(float dt);
	// Détection des events Souris/Clavier
	void checkEvent();
	// Détection du stack empty
	void checkStack();

protected:
	std::deque<Interface*> iStack;
	std::vector<Interface*> interfaces;
	Graphics* g;
	Input input;
};