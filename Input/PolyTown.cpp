#include "PolyTown.h"

#include <SDL2/SDL.h>

//
#include <iostream>

using namespace std;
//

PolyTown& PolyTown::instance = PolyTown();

PolyTown::PolyTown()
{
    running = false;
}

PolyTown& PolyTown::getInstance()
{
    return instance;
}

bool PolyTown::init()
{
    window = SDL_CreateWindow(
        "PolyTown Alpha 0.1.1",            // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
        );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        cout << "Could not create window : " << SDL_GetError() << endl;
        return 1;
    }

    running = true;

    cout << "Game initialized" << endl;

    return 0;
}

void PolyTown::mainLoop()
{
    cout << "Game running" << endl;

    while (running) {
        input.update();
        input.display();
        SDL_Delay(500);

        if (wantQuit()) {
            running = false;
        }
    }
}

void PolyTown::quit()
{
    SDL_DestroyWindow(window);
    SDL_Quit();

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