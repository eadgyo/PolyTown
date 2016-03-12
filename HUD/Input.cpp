#include "Input.h"

#include "../Constant.h"

#include <SDL2/SDL.h>

#include <iostream>

using namespace std;

Input::Input()
{
    quit = false;
}

string const Input::keysName[] = {KEY_1_NAME, KEY_2_NAME};
int const Input::keysCode[] = {KEY_1_CODE, KEY_2_CODE};

void Input::update()
{
    SDL_Event event;

    mousePressed[0] = false;
    mousePressed[1] = false;
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        keysPressed[i] = false;
    }

    while (SDL_PollEvent(&event)) {
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
                        mousePressed[0] = !mouseDown[0];
                        mouseDown[0] = true;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mousePressed[1] = !mouseDown[1];
                        mouseDown[1] = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mouseDown[0] = false;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mouseDown[1] = false;
                        break;
                }
                break;
            case SDL_KEYDOWN:
                for (int i = 0; i < NUMBER_OF_KEYS; i++) {
                    if (event.key.keysym.sym == keysCode[i]) {
                        keysPressed[i] = !keysDown[i];
                        keysDown[i] = true;
                    }
                }
                break;

            case SDL_KEYUP:
                for (int i = 0; i < NUMBER_OF_KEYS; i++) {
                    if (event.key.keysym.sym == keysCode[i]) {
                        keysDown[i] = false;
                    }
                }
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
    //cout << "mouseDown : " << "Left = "<< mouseDown[0] << ' ' << "Right = " << mouseDown[1]<< endl;
    cout << "mousePressed : " << "Left = " << mousePressed[0] << ' ' << "Right = " << mousePressed[1] << endl;

    cout << endl;

    cout << "keysPressed :";
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        cout << ' ' << keysName[i] << ' ' << keysPressed[i];
    }

    cout << endl;
}