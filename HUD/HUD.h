#pragma once

#include "Input.h"
#include <deque>
#include "../Interfaces/Interface.h"
#include "../Graphics/Graphics.h"

class HUD : public Input
{
public:
	HUD();
	// Création de la fenetre et des graphics
	void initialize(std::string name, int width, int height);
	// Rendu sur la fenetre
	void render();
	// Fin du Jeu
	void exitGame();
	// Mise à jour graphique
	void update(float dt);
	// Détection des collisions 
	void collisions();

protected:
	std::deque<Interface*> interfacesStack;
	Graphics* g;

};