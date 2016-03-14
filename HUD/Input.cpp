#include "Input.h"
#include "../Constant.h"

#include <SDL2/SDL.h>

#include <iostream>

using namespace std;

Input::Input()
{
    quit = false;
	lastEvent = 0;

    keysCode[0] = KEY_CODE_1;
    keysCode[1] = KEY_CODE_2;
}

void Input::update()
{
    SDL_Event event;

    mousePressed[0] = false;
    mousePressed[1] = false;
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        keysPressed[i] = false;
    }

    while (SDL_PollEvent(&event)) {
		lastEvent = event.type;
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

// ----- GETTER ----- //

// Keyboard

bool Input::getKeyDown(int n) const
{
    return keysDown[n];
}

bool Input::getKeyPressed(int n) const
{
    return keysPressed[n];
}

// Mouse

int Input::getMousePos(int n) const
{
    return mousePos[n];
}

bool Input::getMouseDown(int n) const
{
    return mouseDown[n];
}

bool Input::getMousePressed(int n) const
{
    return mousePressed[n];
}

// ----- SETTER ----- //

void Input::clear()
{
	clearMouse();
	clearKeys();
}

// Keyboard

void Input::clearKeys()
{
    clearKeysPressed();
    clearKeysDown();
}

void Input::clearKey(int n)
{
    clearKeyPressed(n);
    clearKeyDown(n);
}

void Input::clearKeysDown()
{
    for (unsigned i = 0; i < NUMBER_OF_KEYS; i++) {
        mouseDown[i] = false;
    }
}

void Input::clearKeyDown(int n)
{
    mouseDown[n] = false;
}

void Input::clearKeysPressed()
{
    for (unsigned i = 0; i < NUMBER_OF_KEYS; i++) {
        mousePressed[i] = false;
    }
}

void Input::clearKeyPressed(int n)
{
    mousePressed[n] = false;
}

// Mouse

void Input::clearMouse()
{
    clearMousePressed();
    clearMouseDown();
}
void Input::clearMouse(int n)
{
    clearMousePressed(n);
    clearMouseDown(n);
}

void Input::clearMousePressed()
{
    for (unsigned i = 0; i < 2; i++) {
        mousePressed[i] = false;
    }
}

void Input::clearMousePressed(int n)
{
    mousePressed[n] = false;
}

void Input::clearMouseDown()
{
    for (unsigned i = 0; i < 2; i++) {
        mouseDown[i] = false;
    }
}

void Input::clearMouseDown(int n)
{
    mouseDown[n] = false;
}

// ----- DEBUG ----- //

void Input::display()
{
    cout << "mousePos     : " << '[' << mousePos[0] << ", " << mousePos[1] << ']' << endl;
    //cout << "mouseDown : " << "Left = "<< mouseDown[0] << ' ' << "Right = " << mouseDown[1]<< endl;
    cout << "mousePressed : " << "[Left " << mousePressed[0] << "][Right " << mousePressed[1] << ']' << endl;

    cout << "keysPressed  : ";
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        cout << '[' << SDL_GetKeyName(keysCode[i]) << ' ' << keysPressed[i] << ']';
    }

    cout << endl << endl;
}

// ----- TEMP ----- //

bool Input::getQuit()
{
    return quit;
}