#pragma once
#include "Interface.h"
#include "../GameElements/Bouton.h"
#include "../HUD/Input.h"

#define SIZE_BW 200
#define SIZE_BH 70

class StartMenu : public Interface
{
public:
	StartMenu(Graphics* g);
	~StartMenu();

	void initialize(int, int);
	void reset();
	void render(Graphics* g);
	HudNs::HudEvent handleEvent(Input& input);
	void resize(int width, int height);

private:
	std::vector<Bouton*> boutons;

};

