#pragma once
#include "Interface.h"
#include "../Layers/LeftLayer.h"
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
	LeftLayer leftLayer;

	/*Test Début*/
	GameStruct gameStruct;
	CreatorManager creatorManager;
	LinkManager linkManager;
	int a = -1;
	Vector3D a1;
	Vector3D a2;
	Road road;
	/* Test fin*/
};



