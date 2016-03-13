#ifndef INPUT_H
#define INPUT_H
class Input;
#include "../Constant.h"
#include <SDL2/SDL.h>
#include <string>

class Input
{
public:
    Input();
    void update();
    void display();
    const bool* getMouseState() const;
    const bool* getKeysState() const;
    const int* getMousePos() const;
	bool getQuit();

	// Les fonctions de Ronan
	// Getter
	bool getKeyDown(int n);
	bool getKeyPressed(int n);
	bool getMouseDown(int n);
	bool getMousePressed(int n);

	// Setter
	void clearKeyPressed();
	void clearKeyPressed(int n);
	void clearKeyDown();
	void clearKeyDown(int n);
	void clearKey();
	void clearKey(int n);
	void clearMouse();
	void clearMouse(int n);
	void clearMousePressed();
	void clearMousePressed(int n);
	void clearMouseDown();
	void clearMouseDown(int n);
	void clear();


	inline Uint32 getLastEvent() { return lastEvent; };
   
private:
    bool quit;
	Uint32 lastEvent;

    int mousePos[2] = {0};
    bool mouseDown[2] = {false};
    bool mousePressed[2] = {false};

    int keysCode[NUMBER_OF_KEYS];
    bool keysDown[NUMBER_OF_KEYS] = {false};
    bool keysPressed[NUMBER_OF_KEYS] = {false};
};

#endif // !INPUT_H