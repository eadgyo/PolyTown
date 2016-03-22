#pragma once
#include "Interface.h"
#include "../Layers/BottomLayer.h"

class Game :
	public Interface
{

public:
	Game(Graphics* g);
	~Game();

	void initialize(int width, int height);
	void reset();
	void resize(int width, int height);
	void render(Graphics* g);
	HudNs::HudEvent update(float dt);
	HudNs::HudEvent handleEvent(Input& input);

protected:
	BottomLayer bottomLayer;

};



