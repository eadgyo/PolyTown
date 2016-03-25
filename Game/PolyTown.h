#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "GameStruct.h"
#include "CreatorManager.h"
#include "UpdateManager.h"

#include <deque>
#include <vector>

#include "../Graphics/Graphics.h"

#include "../Interfaces/Interface.h"
#include "../Interfaces/StartMenu.h"
#include "../Interfaces/Game.h"

#include "../Interfaces/NewGame.h"

class PolyTown
{
public:
    PolyTown();
    virtual ~PolyTown() { std::cout << "PolyTown : Destruction" << std::endl; };

    bool init(std::string name, int width, int height);
    void mainLoop();
    void exit();

    unsigned int delay(unsigned int lastFrame);

    // Détection des events Souris/Clavier
    void checkEvent();
    // Détection du stack empty
    void checkStack();

    // ----- UPDATE WINDOW ----- //
    void clear();
    void render();
    void swap();

    // ----- In GAME
    void startGame();

private:
    bool running;

    unsigned int dt;

    GameStruct* gs;
    CreatorManager* creator_m;
    UpdateManager* update_m;

    // Graphique et input
    std::deque<Interface*> iStack;
    std::vector<Interface*> interfaces;
    Graphics* g;
    Input input;
};

#endif // !POLYTOWN_H