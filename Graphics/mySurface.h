#ifndef MYSURFACE_H_
#define MYSURFACE_H_

struct mySurface;
#include <Windows.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>


struct mySurface
{
	GLuint texture;
	SDL_Surface* image;
};

#endif