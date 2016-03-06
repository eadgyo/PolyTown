#include <SDL2/SDL.h>
#include "Maths/Vector3D.h"
#include <iostream>
#include "Maths/Rectangle.h"
#include "Maths/Form.h"
#include "FileManager.h"


int main(int argc, char* args[])
{
	/*
    SDL_Window *window;

    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
        );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Delay(3000);*/

	Graphics *g = new Graphics("Ma bite", 1600, 900);

	FileManager& fileM = FileManager::getInstance();
	fileM.initialize();
	fileM.load(g);

	/*g->clear();
	Image image;
	image.initialize(g, 565, 203, 0, "a.png");
	image.setPositionX(0);
	image.setPositionY(0);

	image.draw();*/

	Form form;
	form.addPoint(Vector3D(10, 10));
	//form.addPoint(Vector3D(70, 60));
	form.addPoint(Vector3D(200, 30));
	form.addPoint(Vector3D(100, 120));
	form.addPoint(Vector3D(10, 100));

	form.triangulate();

	g->setColor(1.0f, 0.0f, 0.0f);
	g->drawLines(form);


	g->update();



	SDL_Delay(1000);
    return 0;
}
