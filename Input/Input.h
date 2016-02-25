#ifndef INPUT_H
#define INPUT_H

class Input
{
    public:
        static Input& getInstance();
        void update();

    private:
        static Input &instance;

        /*
        bool keysDown[1];
        bool keysPressed[1];

        int mouse[2];
        int mouseIn;
        bool mouseDown[3];
        bool mousePressed[3];
        int mouse[2];
        */

        Input();
};

#endif // !INPUT_H