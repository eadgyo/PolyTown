#pragma once
#include "../Graphics/Graphics.h"

class Interface
{
	// initialisation de l'interface
	void virtual initialize() = 0;
	// R�initailisation de l'interface
	void virtual reset() = 0;
	// Rendu sur la fenetre
	void virtual render(Graphics* g) = 0;
	// Mise � jour graphique
	void virtual update(float dt) = 0;
	// D�tection des collisions 
	void virtual collisions() = 0;
	
};