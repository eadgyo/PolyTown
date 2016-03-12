#include "PolyTown.h"

#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    PolyTown game = PolyTown::getInstance();

    if (game.init()) {
        return 1;
    }

    game.mainLoop();

    game.quit();

    return 0;
}