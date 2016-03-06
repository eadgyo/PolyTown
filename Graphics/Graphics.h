/*
 * Graphics.h
 *
 *  Created on: Mar 3, 2016
 *      Author: ronan-h
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <string>
#include <assert.h>

class Graphics
{
public:
	Graphics(std::string windowName, int width, int height);
	virtual ~Graphics();
	void clear();
	void update();
	void render(const Image& image);
	void render(SDL_Texture *texture, SDL_Rect& textureRect);
	SDL_Texture* loadTextureFromSurface(SDL_Surface *surface);
	void loadTextures(std::vector<SDL_Surface*>& surfaces, std::vector<std::string>& names);

private:
	SDL_Window *screen;
	SDL_Renderer *renderer;
	std::vector<SDL_Texture*> textures;
	std::vector<std::string> names;
};

#endif /* GRAPHICS_H_ */
