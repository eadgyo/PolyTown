#ifndef INPUT_H
#define INPUT_H

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
        bool mouseDown[2];
        bool mousePressed[2];

        bool keysDown[2];
        bool keysPressed[2];
};

#endif // !INPUT_H