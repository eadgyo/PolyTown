#pragma once

#include "Input.h"
#include <deque>
#include "../Interfaces/Interface.h"
#include "../Graphics/Graphics.h"

class HUD : public Input
{
public:
	// Création de la fenetre et des graphics
	void initialize();
	// Rendu sur la fenetre
	void render();
	// Fin du Jeu
	void exitGame();
	// Mise à jour graphique
	void update();
	// Détection des collisions 
	void collisions();

protected:
	std::deque<Interface> interfacesStack;
	Graphics* g;

};