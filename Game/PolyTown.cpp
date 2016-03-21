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
    interfaces.push_back(new StartMenu());
    // Menu InGame
    interfaces.push_back(new Game());
    // Menu Pause

    //interfaces.push_back(new NewGame());
    

    // Initialisation des boutons
    for (unsigned i = 0; i < interfaces.size(); i++) {
        interfaces[i]->initialize(width, height);
    }

    iStack.push_back(interfaces[0]);

	// Création des ressources
    house = StructFactory::newHouse(g, 60, 65);
    building = new Building(g, 180, 70);
    shop = new Shop(g, 300, 75);
    manufactory = new Manufactory(g, 420, 80);
    farm = new Farm(g, 540, 85);
    
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
    unsigned int dt = SDL_GetTicks() - lastFrame;
    if (dt < 1000 / FPS) {
        SDL_Delay(1000 / FPS - dt);
    }
    return SDL_GetTicks();
}

// Changement d'interface
void PolyTown::checkEvent()
{
	checkStack();
	HudNs::HudEvent result = iStack.back()->handleEvent(input);

	if (result % HudNs::NEW_GAME)
	{
		iStack.push_back(interfaces[1]);
        gs = new GameStruct();
	}
	if (result % HudNs::LOAD_GAME)
	{

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
    house->render();
    house->translate(1, 1);
    building->render();
    shop->render();
    manufactory->render();
    farm->render();

	checkStack();
	// On rend le dernier élément
	iStack.back()->render(g);
}

void PolyTown::swap()
{
	// Swap buffer
	g->swapGL();
}