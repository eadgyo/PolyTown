#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../HUD/HUD.h" // Héritage
#include "../HUD/Input.h" // Temp

#include <SDL2/SDL.h>

class PolyTown : public HUD
{
public:
    static PolyTown& getInstance();

    bool init();
    void mainLoop();
    void quit();

    bool wantQuit();

    void update(); 
	virtual ~PolyTown() { std::cout << "Destruction\n"; };

private:
    static PolyTown& instance;

    bool running;

    Input input;

    PolyTown();
	
};

#endif // !POLYTOWN_H