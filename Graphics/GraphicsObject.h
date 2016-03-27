#pragma once

class GraphicsObject
{
public:
	GraphicsObject() { isInitialized = false; };
	GraphicsObject(int, int) { isInitialized = false; };
	// initialisation de l'objet
	void virtual initialize(int width, int height) = 0;
	// Réinitailisation de l'objet
	void virtual reset() {};
	// Gestion possible du resize
	void virtual resize(int width, int height) {};
	// Rendu sur la fenetre
	void virtual render(Graphics* g) = 0;
protected:
	bool isInitialized;
};