#pragma once
#include "Interface.h"
#include "Bouton.h"
#include "../HUD/Input.h"

class NewGame :
	public Interface
{
public:
	NewGame();
	~NewGame();
	void initialize(int width, int height);
	void virtual reset();
	void virtual resize(int width, int height);
	void virtual render(Graphics* g);
	void virtual update(float dt);
	HudEvent virtual handleEvent(Input& input);

};

