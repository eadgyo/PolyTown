#pragma once

class Interface;
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"

class Interface
{
public:
	Interface() { isInitialized = false; };
	Interface(int, int) { isInitialized = false; };
	// initialisation de l'interface
	void virtual initialize(int width, int height) = 0;
	// Réinitailisation de l'interface
	void virtual reset() = 0;
	// Gestion possible du resize
	void virtual resize(int width, int height) = 0;
	// Rendu sur la fenetre
	void virtual render(Graphics* g) = 0;
	// Mise à jour graphique
	void virtual update(float dt) = 0;
	// Détection des collisions 
	HudEvent virtual handleEvent(Input& input) = 0;

private:
	bool isInitialized;
};