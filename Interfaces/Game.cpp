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

	QTEntity* a = StructFactory::newHouse(600, 800);
	a->setRadians((float) (PI / 3));
	
	gs->QTCollision.insert(a);
	//gs->QTCollision.insert(StructFactory::newHouse(400, 850));
	//gs->QTCollision.insert(StructFactory::newHouse(470, 350));

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
	
	mapLayer.render(g);
	leftLayer.render(g);
	mapRecLayer.render(g);
	scoresLayer.render(g);
	timeLayer.render(g);
}

HudNs::HudEvent Game::update(float dt)
{
	return HudNs::OK;
}

HudNs::HudEvent Game::handleEvent(Input & input)
{
	Vector3D mouse = input.getMousePos();
	LayerNs::LayerEvent leftLayRed = LayerNs::NOCOLLISION;

	if (input.getMousePressed(1))
	{
		leftLayer.reset();
		mapLayer.reset();
	}

	if (leftLayer.isColliding(mouse))
	{
		leftLayRed = leftLayer.handleEvent(input, Vector3D(false));
	}
	else if (mapRecLayer.isColliding(mouse))
	{
		mapRecLayer.handleEvent(input, Vector3D(false));
	}
	if(leftLayRed % LayerNs::NOCOLLISION)
		mapLayer.handleEvent(input, Vector3D(false));
	

	return HudNs::OK;
}
