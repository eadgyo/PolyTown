#include "Game.h"

Game::Game(Graphics* g) : Interface(g), bottomLayer(g)
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
	bottomLayer.initialize(0, height*0.8f, (int) width, (int) (height*0.2f));
}

void Game::reset()
{
}

void Game::resize(int width, int height)
{
}

void Game::render(Graphics * g)
{
	bottomLayer.render(g);
}

HudNs::HudEvent Game::update(float dt)
{
	return HudNs::OK;
}

HudNs::HudEvent Game::handleEvent(Input & input)
{
	bottomLayer.handleEvent(input);
	return HudNs::HudEvent();
}
