#include "Game/PolyTown.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    PolyTown game = PolyTown::getInstance();

    if (game.init()) {
        cout << "Impossible d'initialiser le jeu .." << endl;
        return 1;
    }

    game.mainLoop();

    game.quit();

    return 0;
}