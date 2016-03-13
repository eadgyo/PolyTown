#pragma once
#include "Interface.h"

class Game :
	public Interface
{

public:
	Game();
	~Game();

	void initialize(int width, int height);
	void reset();
	void resize(int width, int height);
	void render(Graphics* g);
	void update(float dt);
	HudEvent handleEvent(Input& input);


};



