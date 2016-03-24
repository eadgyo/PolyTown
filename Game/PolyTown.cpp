#include "PolyTown.h"
#include "../Constant.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <Windows.h>

#include "../Maths/myRectangle.h"

#include "../GameContent/StructFactory.h"

using namespace std;

PolyTown::PolyTown() : running(false), g(new Graphics), gs(NULL)
{
    FileManager& fileM = FileManager::getInstance();

    cout << "PolyTown : Construction" << endl;
}

bool PolyTown::init(string name, int width, int height)
{
    // Création de la fenetre
    g->init(name, width, height);
    g->initGL(width, height);

    // Création des interfaces
    // Menu principal
    interfaces.push_back(new StartMenu(g));
    // Menu InGame
    interfaces.push_back(new Game(g));
    // Menu Pause

    //interfaces.push_back(new NewGame());


    // Initialisation des boutons
    for (unsigned i = 0; i < interfaces.size(); i++) {
        interfaces[i]->initialize(width, height);
    }

    iStack.push_back(interfaces[0]);

    running = true;

    cout << "PolyTown initialized" << endl;

    return 0;
}

void PolyTown::mainLoop()
{
    cout << "PolyTown is running" << endl;

    unsigned int lastFrame = 0;

    while (running) {
        // INPUT
        input.update();

        // INTERFACE(input)

        // LINK MANAGER

        // UPDATE MANAGER
        if (gs) {
            update_m->update(dt);
            //gs->housing.at(0)->addInhabitants(1);
            //gs->housing[0]->delInhabitants(1);

            gs->factory[0]->addWorkers(1);
        }

        // CREATOR MANAGER

        // CLEAR WINDOW
        clear();

        // RENDER WINDOW
        render();

        // SWAP WINDOW
        swap();

        checkEvent();

        // EXTI GAME ?
        running = !input.exit();

        // DELAY
        lastFrame = delay(lastFrame);
    }
}

void PolyTown::exit()
{
    cout << "PolyTown ended" << endl;
}

unsigned int PolyTown::delay(unsigned int lastFrame)
{
    unsigned delta = SDL_GetTicks() - lastFrame;
    if (delta < 1000 / FPS) {
        SDL_Delay(1000 / FPS - delta);
    }
    if (delta > 1050 / FPS) {
        dt = 0;
        return SDL_GetTicks();
    } else {
        unsigned int time = SDL_GetTicks();
        dt = time - lastFrame;
        return time;
    }
}

// Changement d'interface
void PolyTown::checkEvent()
{
    checkStack();
    HudNs::HudEvent result = iStack.back()->handleEvent(input);

    if (result % HudNs::NEW_GAME) {
        iStack.push_back(interfaces[1]);
        startGame();
    }
    if (result % HudNs::LOAD_GAME) {

    }
}

void PolyTown::checkStack()
{
    if (iStack.size() == 0)
        std::cerr << "Error: HUD Stack is empty !! Bitches ain't my type.";
}

// ----- UPDATE WINDOW ----- //
void PolyTown::clear()
{
    // On reset l'écran
    g->clear();
}

void PolyTown::render()
{
    checkStack();
    // On rend le dernier élément
    iStack.back()->render(g);
}

void PolyTown::swap()
{
    // Swap buffer
    g->swapGL();
}

// In GAME
void PolyTown::startGame()
{
    cout << "Game started" << endl;

    gs = new GameStruct();
    //creator_m = new CreatorManager();
    update_m = new UpdateManager(gs);

    gs->money = START_MONEY_AMOUNT;

    gs->housing.push_back(StructFactory::newHouse(10, 10));
    gs->housing.push_back(StructFactory::newHouse(100, 100));
    gs->housing[0]->addInhabitants(10);

    gs->factory.push_back(StructFactory::newFarm(0, 0));
}