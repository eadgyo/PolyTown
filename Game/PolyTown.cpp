#include "PolyTown.h"
#include "../Constant.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <Windows.h>

#include "../Maths/myRectangle.h"

using namespace std;

PolyTown::PolyTown() :
    HUD()
{
    cout << "PolyTown : Construction" << endl;
    running = false;

}

bool PolyTown::init()
{
    HUD::initialize("PolyTown Alpha 0.1", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	// Création des ressources
	house = new House(g, myRectangle(Vector3D(0, 0), 250, 250));

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

        HUD::clear();
        house->draw();
		HUD::render();
        HUD::swap();
		HUD::checkEvent();

        SDL_Delay(500);

        if (wantQuit()) {
            running = false;
        }
    }
}

void PolyTown::exit()
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