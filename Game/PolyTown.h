#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../HUD/HUD.h" // H�ritage

#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"

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
};

#endif // !POLYTOWN_H