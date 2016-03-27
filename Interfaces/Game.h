#pragma once
#include "Interface.h"
#include "../Layers/LeftLayer.h"
#include "../Game/GameStruct.h"
#include "../Game/CreatorManager.h"
#include "../Layers/MapLayer.h"
#include "../Layers/scoresLayer.h"
#include "../Layers/TimeLayer.h"

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

	/* Layers */
	LeftLayer leftLayer;
	MapLayer mapLayer;
	ScoresLayer scoresLayer;
	MapRecLayer mapRecLayer;
	TimeLayer timeLayer;

	/* Test Début */
	GameStruct gs;
	CreatorManager creatorManager;
	LinkManager linkManager;



	/* Constantes */
	const float SIZE_FACTOR_REC_MAP = 0.15f;
	const float POS_X_FACTOR_REC_MAP = 0.98f - SIZE_FACTOR_REC_MAP;
	const float POS_Y_FACTOR_REC_MAP = 0.95f - SIZE_FACTOR_REC_MAP;
};



