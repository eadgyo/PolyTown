#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize(int width, int height)
{
	bottomLayer.initialize(0, height*0.8, (int) width, (int) height*0.2);
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

void Game::update(float dt)
{
}

HudNs::HudEvent Game::handleEvent(Input & input)
{
	bottomLayer.handleEvent(input);
	return HudNs::HudEvent();
}
