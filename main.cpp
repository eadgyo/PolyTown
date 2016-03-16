#include "Game/PolyTown.h"
#include "FileManager\FileManager.h"

int main(int argc, char *argv[])
{
    
    PolyTown game;

    if (game.init()) {
        return 1;
    }

    game.mainLoop();

    game.exit();

    return 0;
}