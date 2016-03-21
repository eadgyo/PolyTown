#pragma once
#include "Interface.h"
#include "../GameElements/Bouton.h"
#include "../HUD/Input.h"

class NewGame : public Interface
{
public:
	NewGame(Graphics* g);
	~NewGame();
	void initialize(int width, int height);
	void virtual reset();
	void virtual resize(int width, int height);
	void virtual render(Graphics* g);
	void virtual update(float dt);
	HudNs::HudEvent virtual handleEvent(Input& input);

};

