#include "Input.h"
#include "../Constant.h"

#include <SDL2/SDL.h>

#include <iostream>

using namespace std;

Input::Input()
{
    quit = false;

    mouseMoves = false;
    mouseDown = false;
    mousePressed;
    keyDown = false;
    keyPressed = false;
    keysCode[0] = KEY_CODE_1;
    keysCode[1] = KEY_CODE_2;
}

void Input::update()
{
    SDL_Event event;

    mouseMoves = false;
    clearMousePressed();
    clearKeysPressed();

    while (SDL_PollEvent(&event)) {
		switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEMOTION:
                mouseMoves = true;
                mousePos[0] = event.motion.x;
                mousePos[1] = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mouseButtonsPressed[0] = !mouseButtonsDown[0];
                        mouseButtonsDown[0] = true;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mouseButtonsPressed[1] = !mouseButtonsDown[1];
                        mouseButtonsDown[1] = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mouseButtonsDown[0] = false;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mouseButtonsDown[1] = false;
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

    mousePressed = (mouseButtonsPressed[0] || mouseButtonsPressed[1]);
    mouseDown = (mouseButtonsDown[0] || mouseButtonsDown[1]);;

    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        keyPressed = (keyPressed || keysPressed[i]);
        keyDown = (keyDown || keysDown[i]);
    }
}

// ----- GETTER ----- //

// Keyboard

bool Input::isKeyDown() const
{
    return keyDown;
}

bool Input::isKeyPressed() const
{
    return keyPressed;
}

bool Input::getKeyDown(unsigned int n) const
{
    return keysDown[n];
}

bool Input::getKeyPressed(unsigned int n) const
{
    return keysPressed[n];
}

// Mouse

bool Input::isMouseMoving() const
{
    return mouseMoves;
}

int Input::getMousePos(unsigned int n) const
{
    return mousePos[n];
}

Vector3D Input::getMousePos() const
{
	return Vector3D(mousePos[0], mousePos[1]);
}

bool Input::isMouseDown() const
{
    return mouseDown;
}

bool Input::isMousePressed() const
{
    return mousePressed;
}

bool Input::getMouseDown(unsigned int n) const
{
    return mouseButtonsDown[n];
}

bool Input::getMousePressed(unsigned int n) const
{
    return mouseButtonsPressed[n];
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

void Input::clearKey(unsigned int n)
{
    clearKeyPressed(n);
    clearKeyDown(n);
}

void Input::clearKeysDown()
{
    keyDown = false;
    for (unsigned i = 0; i < NUMBER_OF_KEYS; i++) {
        keysDown[i] = false;
    }
}

void Input::clearKeyDown(unsigned int n)
{
    keysDown[n] = false;
}

void Input::clearKeysPressed()
{
    keyPressed = false;
    for (unsigned i = 0; i < NUMBER_OF_KEYS; i++) {
        keysPressed[i] = false;
    }
}

void Input::clearKeyPressed(unsigned int n)
{
    keysPressed[n] = false;
}

// Mouse

void Input::clearMouse()
{
    clearMousePressed();
    clearMouseDown();
}
void Input::clearMouse(unsigned int n)
{
    clearMousePressed(n);
    clearMouseDown(n);
}

void Input::clearMouseDown()
{
    mouseDown = false;
    for (unsigned i = 0; i < 2; i++) {
        mouseButtonsDown[i] = false;
    }
}

void Input::clearMouseDown(unsigned int n)
{
    mouseButtonsDown[n] = false;
}

void Input::clearMousePressed()
{
    mousePressed = false;
    for (unsigned i = 0; i < 2; i++) {
        mouseButtonsPressed[i] = false;
    }
}

void Input::clearMousePressed(unsigned int n)
{
    mouseButtonsPressed[n] = false;
}

// ----- DEBUG ----- //

void Input::display()
{
    cout << "mousePos     : " << '[' << mousePos[0] << ", " << mousePos[1] << ']' << endl;
    //cout << "mouseDown : " << "Left = "<< mouseDown[0] << ' ' << "Right = " << mouseDown[1]<< endl;
    cout << "mousePressed : " << "[Left " << mouseButtonsPressed[0] << "][Right " << mouseButtonsPressed[1] << ']' << endl;

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