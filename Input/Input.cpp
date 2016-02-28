#include "Input.h"

#include <SDL2/SDL.h>

#include <iostream>


using namespace std;

Input::Input()
{
    quit = false;
    keysDown[2] = {0};
    keysPressed[2] = {0};
}

void Input::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEMOTION:
                mousePos[0] = event.motion.x;
                mousePos[1] = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mouseDown[0] = true;
                        break;
                    default:
                        break;
                }
                break;
            
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

bool* Input::getKeys()
{
    return keysDown;
}

bool Input::getQuit()
{
    return quit;
}

void Input::display()
{
    cout << "mousePos : " << mousePos[0] << ' ' << mousePos[1] << endl;
    cout << "mouseDown : " << mouseDown[0] << endl;

    //cout << "keysDown : " << keysDown[0] << ' ' << keysDown[1] << endl;
    //cout << "keysPressed : " << keysPressed[0] << ' ' << keysPressed[1] << endl;
}