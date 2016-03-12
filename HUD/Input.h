#ifndef INPUT_H
#define INPUT_H

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

    int mousePos[2];
    bool mouseDown[2] = {false};
    bool mousePressed[2] = {false};

    static const int numberOfKeys = 2;
    static std::string const keysName[];
    static int const keysCode[];
    bool keysDown[2] = {false};
    bool keysPressed[2] = {false};
};

#endif // !INPUT_H