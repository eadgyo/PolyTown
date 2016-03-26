#include "Game.h"

Game::Game(Graphics* g) : Interface(g), leftLayer(g)
{
	/* 
	Test Début
	*/
	a = -1;

}

Game::~Game()
{
}

void Game::initialize(int width, int height)
{
	leftLayer.initialize(0, 0, (int) width*0.2f, (int) (height));
	creatorManager.initialize(&gameStruct, &linkManager);
	gameStruct.initialize((float) width, (float) height);
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
	
	g->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	g->render((*road.getForm()));
	leftLayer.render(g);
	g->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	g->render(*(road.getForm()));

}

HudNs::HudEvent Game::update(float dt)
{
	return HudNs::OK;
}

HudNs::HudEvent Game::handleEvent(Input & input)
{
	LayerNs::LayerEvent res = leftLayer.handleEvent(input);
	
	Vector3D mouse = input.getMousePos();
	if (a == 0)
	{
		//std::cout << "Ok";
		a1.set(mouse);
		a2.set(mouse);
	}
	else if (a == 1)
	{
		a2.set(mouse);
	}
	road.set2points(a1, a2, 50);
	//std::cout << "a1";
	//a1.display();


	if (input.getMousePressed(0) && res % LayerNs::NOCOLLISION && leftLayer.getState() == 0)
	{
		if (leftLayer.getState() == 0)
		{
			a++;
			if (a == 1)
			{
				//std::cout << "SetA1" << " : ";
				//mouse.display();
				a1.set(mouse);
			}
			if (a == 2)
			{
				a2.set(mouse);
				road.set2points(a1, a2, 30);
			}
		}
	}

	return HudNs::HudEvent();
}
