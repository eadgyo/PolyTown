#ifndef INPUT_H
#define INPUT_H

#include "../Constant.h"
#include "../Maths/Vector3D.h"

#include <SDL2/SDL.h>
#include <string>

class Input
{
public:
    Input();

    void update();
    
    // ----- GETTER ----- //

    // Keyboard
    bool getKeyDown(unsigned int n) const;
    bool getKeyPressed(unsigned int n) const;

    // Mouse

    int getMousePos(unsigned int n) const;
	Vector3D getMousePos() const;
    bool getMouseDown(unsigned int n) const;
    bool getMousePressed(unsigned int n) const;

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
	void clearMousePressed();
	void clearMousePressed(unsigned int n);
	void clearMouseDown();
	void clearMouseDown(unsigned int n);

	inline Uint32 getLastEvent() { return lastEvent; };

    // ----- DEBUG ----- //
    void display();

    // ----- TEMP ----- //
    bool getQuit();

private:
	Uint32 lastEvent;

    // Mouse state
    int mousePos[2] = {0};
    bool mouseDown[2] = {false};
    bool mousePressed[2] = {false};

    // Keyboard state
    int keysCode[NUMBER_OF_KEYS];
    bool keysDown[NUMBER_OF_KEYS] = {false};
    bool keysPressed[NUMBER_OF_KEYS] = {false};

    // ----- TEMP ----- //
    bool quit;
};

#endif // !INPUT_H