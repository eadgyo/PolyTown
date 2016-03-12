#ifndef INPUT_H
#define INPUT_H

#include "../Constant.h"

#include <string>

class Input
{
public:
    Input();
    void update();
    void display();
    bool* getKeys();

    bool getQuit();

private:
    bool quit;

    int mousePos[2] = {0};
    bool mouseDown[2] = {false};
    bool mousePressed[2] = {false};

    static std::string const keysName[NUMBER_OF_KEYS];
    static int const keysCode[NUMBER_OF_KEYS];
    bool keysDown[NUMBER_OF_KEYS] = {false};
    bool keysPressed[NUMBER_OF_KEYS] = {false};
};

#endif // !INPUT_H