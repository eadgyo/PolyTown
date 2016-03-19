#ifndef POLYTOWN_H
#define POLYTOWN_H

// TEMP
#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"
#include "../GameContent/Factory/Shop.h"
#include "../GameContent/Factory/Manufactory.h"
#include "../GameContent/Factory/Farm.h"
//

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

private:
    bool running;

    House* house;
    Building* building;
    Shop* shop;
    Manufactory* manufactory;
    Farm* farm;
	
	// Graphique et input
	std::deque<Interface*> iStack;
	std::vector<Interface*> interfaces;
	Graphics* g;
	Input input;
};

#endif // !POLYTOWN_H