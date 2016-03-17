#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../HUD/HUD.h" // Héritage

#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"
#include "../GameContent/Factory/Shop.h"
#include "../GameContent/Factory/Manufactory.h"
#include "../GameContent/Factory/Farm.h"

class PolyTown : public HUD
{
public:
	PolyTown();
    bool init();
    void mainLoop();
    void exit();

    bool wantQuit();

    void update();
    virtual ~PolyTown() { std::cout << "PolyTown : Destruction" << std::endl; };

private:
    bool running;

    House* house;
    Building* building;
    Shop* shop;
    Manufactory* manufactory;
    Farm* farm;
};

#endif // !POLYTOWN_H