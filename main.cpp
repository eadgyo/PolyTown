#include "Game/PolyTown.h"

int main(int argc, char *argv[])
{
    PolyTown game;

    if (game.init()) {
        return 1;
    }

    game.mainLoop();

    game.quit();

    return 0;
}