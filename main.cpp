#include "Game/PolyTown.h"
#include "FileManager\FileManager.h"

int main(int argc, char *argv[])
{

    PolyTown game;

    if (game.init("PolyTown Alpha 0.1", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        return 1;
    }

    game.mainLoop();

    game.exit();

    return 0;
}