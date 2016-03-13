#include "PolyTown.h"
#include "../Constant.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <Windows.h>

using namespace std;

PolyTown::PolyTown()
{
	std::cout << "Construction";
    running = false;
}

bool PolyTown::init()
{
    HUD::initialize("PolyTown Alpha 0.1", SCREEN_WIDTH, SCREEN_HEIGHT);

    running = true;

    cout << "Game initialized" << endl;

    return 0;
}

void PolyTown::mainLoop()
{
    cout << "Game is running" << endl;

    while (running) {
		
        input.update();
        //input.display();
		HUD::render();
		HUD::checkEvent();
        SDL_Delay(500);

        if (wantQuit()) {
            running = false;
        }
    }
}

void PolyTown::quit()
{
    HUD::exitGame();

    cout << "Game ended" << endl;
}

void PolyTown::update()
{

}

// Temporaire

bool PolyTown::wantQuit()
{
    return input.getQuit();
}