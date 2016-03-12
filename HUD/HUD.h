#pragma once

#include "Input.h"
#include <deque>
#include "../Interfaces/Interface.h"
#include "../Graphics/Graphics.h"

class HUD : public Input
{
public:
	HUD();
	// Cr�ation de la fenetre et des graphics
	void initialize(std::string name, int width, int height);
	// Rendu sur la fenetre
	void render();
	// Fin du Jeu
	void exitGame();
	// Mise � jour graphique
	void update(float dt);
	// D�tection des collisions 
	void collisions();

protected:
	std::deque<Interface*> interfacesStack;
	Graphics* g;

};