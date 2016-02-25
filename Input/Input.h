class Input
{
    public:
        void update();

    private:
        Input() {}
        ~Input() {}

        bool keysDown[];
        bool keysPressed[];

        int mouse[2];
        int mouseIn;
        bool mouseDown[3];
        bool mousePressed[3];
        int mouse[2];
};
