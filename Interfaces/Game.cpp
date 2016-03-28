#include "Game.h"

Game::Game(Graphics* g, GameStruct* gs) : Interface(g), leftLayer(g), mapLayer(g), scoresLayer(g), mapRecLayer(g), timeLayer(g)
{
	this->gs = gs;
}

Game::~Game()
{
}

void Game::initialize(int width, int height)
{
	gs->initialize((float) SIZE_MAP_X, (float) SIZE_MAP_Y);
	creatorManager.initialize(gs, &linkManager);
	linkManager.initialize(gs);

	leftLayer.initialize(0, (int) (height*0.05f), (int) (width*0.1f), (int) (height*0.9f), gs);
	mapLayer.initialize(0, 0, width, height, 200, gs);
	mapRecLayer.initialize(
		(int)(POS_X_FACTOR_REC_MAP*width),
		(int)(POS_Y_FACTOR_REC_MAP*height),
		width,
		height,
		(int) SIZE_MAP_X,
		(int) SIZE_MAP_Y,
		(int)(width*SIZE_FACTOR_REC_MAP),
		200,
		gs);
	scoresLayer.initialize((int)(0.83f*width), 0, (int)(0.17f*width), 35, "test",
		20, myColor(1.0f, 1.0f, 1.0f), myColor(0.4f, 0.4f, 0.4f, 0.6f), gs);
	timeLayer.initialize((int)(0.5f*width - 35), 0, (int)(0.08f*width), 35, "test",
		20, myColor(1.0f, 1.0f, 1.0f), myColor(0.4f, 0.4f, 0.4f, 0.6f), gs);


	mapLayer.setCreatorManager(&creatorManager);

	
	gs->QTCollision.insert(StructFactory::newHouse(50, 50));
	gs->QTCollision.insert(StructFactory::newHouse(150, 150));
	gs->QTCollision.insert(StructFactory::newHouse(150, 150));

	gs->QTCollision.insert(StructFactory::newHouse(600, 450));
	gs->QTCollision.insert(StructFactory::newHouse(40, 850));
	gs->QTCollision.insert(StructFactory::newHouse(50, 350));

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
	else
	{
		mapLayer.handleEvent(input, Vector3D(false));
	}

	return HudNs::OK;
}
