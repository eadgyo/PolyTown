#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"
#include "../GameContent/Factory/Shop.h"
#include "../GameContent/Factory/Manufactory.h"
#include "../GameContent/Factory/Farm.h"
#include <deque>
#include <vector>
#include "../Interfaces/Interface.h"
#include "../Interfaces/Menu.h"
#include "../Interfaces/NewGame.h"
#include "../Graphics/Graphics.h"
#include "../Interfaces/Game.h"

class PolyTown
{
public:
	PolyTown();
    bool init();
    void mainLoop();
    void exit();

    bool wantQuit();

    virtual ~PolyTown() { std::cout << "PolyTown : Destruction" << std::endl; };

	
	// Partie graphique
	// Création de la fenetre et des graphics
	void initialize(std::string name, int width, int height);
	// Rendu sur la fenetre
	void clear();
	void render();
	void swap();
	// Mise à jour graphique
	void update(float dt);
	// Détection des events Souris/Clavier
	void checkEvent();
	// Détection du stack empty
	void checkStack();
	
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