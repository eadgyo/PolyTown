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

	SDL_Surface* sur = fileM.loadTexture("a.png", false);

	SDL_Texture* tex = g->loadTextureFromSurface(sur);

	SDL_Texture* texture = IMG_LoadTexture(g->getRenderer(), "a.png");

	//
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 450;
	dst.w = 565;
	dst.h = 203;
	//g->update();
	SDL_Rect texture_rect;

	//g->render(texture, NULL);
	//glLoadIdentity();
	Image image;
	image.initialize(g, 260, 203, 2, texture, "a.png");
	image.setCurrentFrame(0);
	image.setPositionX(0);
	image.setPositionY(0);
	image.scale(2.0f, Vector3D(true));
	// image.flipV(Vector3D(true));

	SDL_RenderClear(g->getRenderer());
	glTranslatef(600, 400, 0);
	image.draw();


	//SDL_RenderCopy(g->getRenderer(), texture, NULL, &dst);
	g->update();

	SDL_Delay(1000);

	image.setCurrentFrame(1);
	image.draw();
	g->update();

	SDL_Delay(1000);
    return 0;
}
