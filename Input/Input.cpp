#include "Input.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

Input Input::instance = Input();

Input::Input() {}

Input Input::getInstance()
{
    return instance;
}

void Input::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch (event.type) {
            case SDL_KEYDOWN:
                cout << "Key press detected" << endl;
                break;

            case SDL_KEYUP:
                cout << "Key release detected" << endl;
                break;

            default:
                break;
        }
    }
}
