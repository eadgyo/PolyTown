#pragma once
#include "Interface.h"
#include "../GameElements/BoutonImage.h"
#include "../HUD/Input.h"
#include "../GameElements/BoutonText.h"

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
	HudNs::HudEvent update(float dt) { return HudNs::OK; };
	void resize(int width, int height);

private:
	std::vector<Bouton*> boutons;

};

