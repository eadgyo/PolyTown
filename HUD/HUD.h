#pragma once

#include "Input.h"
#include <deque>
#include "../Interfaces/Interface.h"
#include "../Graphics/Graphics.h"

class HUD : public Input
{
public:
	// Cr�ation de la fenetre et des graphics
	void initialize();
	// Rendu sur la fenetre
	void render();
	// Fin du Jeu
	void exitGame();
	// Mise � jour graphique
	void update();
	// D�tection des collisions 
	void collisions();

protected:
	std::deque<Interface> interfacesStack;
	Graphics* g;

};