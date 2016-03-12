#ifndef POLYTOWN_H
#define POLYTOWN_H

#include <SDL2/SDL.h>

#include "Input.h"

class PolyTown
{
public:
    static PolyTown& getInstance();

    bool init();
    void mainLoop();
    void quit();

    bool wantQuit();

    void update();

private:
    static PolyTown& instance;

    Input input;

    SDL_Window *window;

    bool running;

    PolyTown();
};

#endif // !POLYTOWN_H