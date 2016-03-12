#pragma once
#include "Interface.h"
class Menu :
	public Interface
{
public:
	Menu();
	~Menu();

	void initialize();
	void reset();
	void render(Graphics* g);
	void update(float dt);
	void collisions();

private:
	std::vector<Bouton*> boutons;

};

