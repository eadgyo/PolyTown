#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../HUD/HUD.h" // Héritage
#include "../HUD/Input.h" // Temp
#include "../GameContent/Housing/House.h"

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
};

#endif // !POLYTOWN_H