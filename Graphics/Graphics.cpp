/*
 * Graphics.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: ronan-h
 */

#include "Graphics.h"

Graphics::Graphics(std::string windowName, int width, int height)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		screen = SDL_CreateWindow(
				windowName.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_OPENGL
				); // SDL_WINDOW_FULLSCREEN

		assert(screen != NULL);

		renderer = SDL_CreateRenderer(screen, -1, 0);

		assert(renderer != NULL);
	}
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

void Graphics::update()
{
	SDL_RenderPresent(renderer);
}

void Graphics::render(SDL_Texture *texture, SDL_Rect& textureRect)
{
	SDL_RenderCopy(renderer, texture, NULL, &textureRect);
}

void Graphics::render(const Image& image)
{

}

SDL_Texture* Graphics::loadTextureFromSurface(SDL_Surface *surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface);
}

void Graphics::loadTextures(std::vector<SDL_Surface*>& surfaces, std::vector<std::string>& names)
{
	for(unsigned i=0; i<surfaces.size(); i++)
	{
		textures.push_back(loadTextureFromSurface(surfaces[i]));
		this->names.push_back(names[i]);
	}
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

