#ifndef INPUT_H
#define INPUT_H
class Input;
#include "../Constant.h"
#include <SDL2/SDL.h>
#include <string>
#include "../Maths/Vector3D.h"

class Input
{
public:
    Input();

    void update();
    
    // ----- GETTER ----- //

    // Keyboard
    bool getKeyDown(int n) const;
    bool getKeyPressed(int n) const;

    // Mouse

    int getMousePos(int n) const;
	Vector3D getMousePos() const;
    bool getMouseDown(int n) const;
    bool getMousePressed(int n) const;

	// ----- SETTER ----- //
    void clear();

    // Keyboard
    void clearKeys();
    void clearKey(int n);
    void clearKeysDown();
    void clearKeyDown(int n);
    void clearKeysPressed();
    void clearKeyPressed(int n);

    // Mouse
	void clearMouse();
	void clearMouse(int n);
	void clearMousePressed();
	void clearMousePressed(int n);
	void clearMouseDown();
	void clearMouseDown(int n);

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