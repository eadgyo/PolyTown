#ifndef INPUT_H
#define INPUT_H

#include "../Constant.h"
#include "../Maths/Vector3D.h"

#include <SDL2/SDL.h>

class Input
{
public:
    Input();

    void update();
    
    // ----- GETTER ----- //
    bool exit() const;

    // Keyboard
    bool isKeyDown() const;
    bool isKeyPressed() const;
    bool getKeyDown(unsigned int n) const;
    bool getKeyPressed(unsigned int n) const;

    // Mouse

    bool isMouseMoving() const;
    int getMousePos(unsigned int n) const;
	Vector3D getMousePos() const;
    bool isMouseDown() const;
    bool isMousePressed() const;
    bool getMouseDown(unsigned int n) const;
    bool getMousePressed(unsigned int n) const;
	int getMouseWheelX() const;
	int getMouseWheelY() const;

	// ----- SETTER ----- //
    void clear();

    // Keyboard
    void clearKeys();
    void clearKey(unsigned int n);
    void clearKeysDown();
    void clearKeyDown(unsigned int n);
    void clearKeysPressed();
    void clearKeyPressed(unsigned int n);

    // Mouse
	void clearMouse();
	void clearMouse(unsigned int n);
	void clearMouseDown();
	void clearMouseDown(unsigned int n);
    void clearMousePressed();
    void clearMousePressed(unsigned int n);

    // ----- DEBUG ----- //
    void display();

private:
    bool quit;

    // Mouse state
    bool mouseMoves;
    int mousePos[2] = {0};
    bool mouseDown;
    bool mouseButtonsDown[2] = {false};
    bool mousePressed;
    bool mouseButtonsPressed[2] = {false};
	int mouseWheelX, mouseWheelY;

    // Keyboard state
    int keysCode[NUMBER_OF_KEYS] = {0};
    bool keyDown;
    bool keysDown[NUMBER_OF_KEYS] = {false};
    bool keyPressed;
    bool keysPressed[NUMBER_OF_KEYS] = {false};
};

#endif // !INPUT_H