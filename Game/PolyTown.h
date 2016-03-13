#ifndef POLYTOWN_H
#define POLYTOWN_H

#include "../HUD/HUD.h" // Héritage
#include "../HUD/Input.h" // Temp

class PolyTown : public HUD
{
public:
	PolyTown();
    bool init();
    void mainLoop();
    void quit();

    bool wantQuit();

    void update(); 
	virtual ~PolyTown() { std::cout << "Destruction\n"; };

private:
    bool running;

   
	
};

#endif // !POLYTOWN_H