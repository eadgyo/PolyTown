#pragma once
#include "Interface.h"
#include "../Layers/BottomLayer.h"
#include "../Game/GameStruct.h"
#include "../Game/CreatorManager.h"
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

	/*Test Début*/
	GameStruct gameStruct;
	CreatorManager creatorManager;
	/* Test fin*/
};



