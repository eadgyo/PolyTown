#pragma once
#include "Interface.h"
#include "../GameElements/Bouton.h"
#include "../HUD/Input.h"

#define SIZE_BW 200
#define SIZE_BH 70

class Menu :
	public Interface
{
public:
	Menu();
	~Menu();

	void initialize(int, int);
	void reset();
	void render(Graphics* g);
	void update(float dt);
	HudNs::HudEvent handleEvent(Input& input);
	void resize(int width, int height);

private:
	std::vector<Bouton*> boutons;

};

