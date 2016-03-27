#include "Game.h"

Game::Game(Graphics* g) : Interface(g), leftLayer(g), mapLayer(g), scoresLayer(g), mapRecLayer(g), timeLayer(g)
{
	/* 
	Test Début
	*/
}

Game::~Game()
{
}

void Game::initialize(int width, int height)
{
	leftLayer.initialize(0, (height*0.05f), (int) (width*0.1f), (int) (height*0.9f), &gs);
	mapLayer.initialize(0, 0, width, height, &gs);
	creatorManager.initialize(&gs, &linkManager);
	gs.initialize((float) width, (float) height);
	mapRecLayer.initialize(
		(int)(POS_X_FACTOR_REC_MAP*width),
		(int)(POS_Y_FACTOR_REC_MAP*height),
		width,
		height,
		6000,
		4000,
		(int)(width*SIZE_FACTOR_REC_MAP),
		0.9f,
		&gs);
	scoresLayer.initialize((int)(0.83f*width), 0, (int)(0.17f*width), 35, "test",
		20, myColor(1.0f, 1.0f, 1.0f), myColor(0.4f, 0.4f, 0.4f, 0.6f), &gs);
	timeLayer.initialize((int)(0.5f*width - 35), 0, (int)(0.08f*width), 35, "test",
		20, myColor(1.0f, 1.0f, 1.0f), myColor(0.4f, 0.4f, 0.4f, 0.6f), &gs);
}

void Game::reset()
{
}

void Game::resize(int width, int height)
{
}

void Game::render(Graphics * g)
{
	std::vector<QTEntity*> entity;
	timeLayer.render(g);
	mapLayer.render(g);
	leftLayer.render(g);
	mapRecLayer.render(g);
	scoresLayer.render(g);


}

HudNs::HudEvent Game::update(float dt)
{
	return HudNs::OK;
}

HudNs::HudEvent Game::handleEvent(Input & input)
{
	Vector3D mouse = input.getMousePos();

	if (input.getMousePressed(1))
	{
		leftLayer.reset();
	}

	if (leftLayer.isColliding(mouse))
	{
		leftLayer.handleEvent(input, Vector3D(false));
	}
	else if (mapRecLayer.isColliding(mouse))
	{
		mapRecLayer.handleEvent(input, Vector3D(false));
	}
	else if (mapLayer.isColliding(mouse))
	{
		mapLayer.handleEvent(input, Vector3D(false));
	}

	

	return HudNs::HudEvent();
}
