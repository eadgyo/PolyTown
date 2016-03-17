#include "PolyTown.h"
#include "../Constant.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <Windows.h>

#include "../Maths/myRectangle.h"

#include "../GameContent/StructFactory.h"

using namespace std;

PolyTown::PolyTown()
{
	FileManager& fileM = FileManager::getInstance();
	g = new Graphics();
	
    cout << "PolyTown : Construction" << endl;
    running = false;
}

bool PolyTown::init()
{
    initialize("PolyTown Alpha 0.1", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	// Création des ressources
    house = StructFactory::newHouse(g, 60, 65);
    building = new Building(g, 180, 70);
    shop = new Shop(g, 300, 75);
    manufactory = new Manufactory(g, 420, 80);
    farm = new Farm(g, 540, 85);

    running = true;

    cout << "Game initialized" << endl;

    return 0;
}

void PolyTown::initialize(std::string name, int width, int height)
{
	// Création de la fenetre
	g->init(name, width, height);
	g->initGL(width, height);

	// Création de toutes les interfaces
	// Menu
	interfaces.push_back(new Menu());
	interfaces.push_back(new NewGame());
	interfaces.push_back(new Game());

	// Initialisation des boutons
	for (unsigned i = 0; i < interfaces.size(); i++)
	{
		interfaces[i]->initialize(width, height);
	}

	// On initialise la pile en ajoutant le Menu
	iStack.push_back(interfaces[0]);
}

void PolyTown::mainLoop()
{
    cout << "Game is running" << endl;

    while (running) {
		
        input.update();
        //input.display();

        clear();

        house->render();
        building->render();
        shop->render();
        manufactory->render();
        farm->render();

		render();
        swap();
		checkEvent();

        SDL_Delay(500);

        if (wantQuit()) {
            running = false;
        }
    }
}

void PolyTown::exit()
{
    cout << "Game ended" << endl;
}

void PolyTown::update(float dt)
{
	checkStack();

	iStack.back()->update(dt);
}

// Changement d'interface
void PolyTown::checkEvent()
{
	checkStack();
	HudNs::HudEvent result = iStack.back()->handleEvent(input);

	if (result % HudNs::NEW_GAME)
	{
		iStack.push_back(interfaces[1]);
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


// Temporaire

bool PolyTown::wantQuit()
{
    return input.getQuit();
}


// Graphique
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

