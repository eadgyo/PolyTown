/*
 * Graphics.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: ronan-h
 */

#include "Graphics.h"

Graphics::Graphics(std::string windowName, int width, int height)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	    std::cout << "Failed to init SDL\n";
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_CreateWindow(
			windowName.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_OPENGL
			); // SDL_WINDOW_FULLSCREEN

	assert(screen != NULL);

	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	assert(renderer != NULL);

	clear();
}

void Graphics::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Graphics::update()
{
	SDL_RenderPresent(renderer);
	clear();
}

void Graphics::render(SDL_Texture *texture, SDL_Rect* textureRect)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void Graphics::render(Image& image)
{
	glPushMatrix();

	const Rectangle rec = image.getRectangle();
	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH)?1:0),
				rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV)?1:0),
				0.0f);

	glScalef(rec.getWidth()/spriteData->rect->getWidth()*((spriteData->flipH)?-1.0f:1.0f),
			rec.getHeight()/spriteData->rect->getHeight()*((spriteData->flipV)?-1.0f:1.0f),
			0.0f);

	float rot = -rec.getAngle(); //+ ((spriteData->flipH)?PI:0);
	if(std::abs(rot) > 0.001f && std::abs(rot - PI*2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH)?1.0f:0.0f)),
				-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV)?1.0f:0.0f)),
				0.0f);


	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	glTranslatef(-sdlRec.x, - sdlRec.y, 0.0f);
	SDL_Rect destRect = spriteData->rect->getSDLRectDest(); //spriteData->flipH, spriteData->flipV);
	SDL_RenderCopy(renderer, spriteData->texture, &sdlRec, &destRect);

	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation)
{
	glPushMatrix();

	const Rectangle rec = image.getRectangle();
	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH)?1:0),
				translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV)?1:0),
				0.0f);

	glScalef(rec.getWidth()/spriteData->rect->getWidth()*((spriteData->flipH)?-1.0f:1.0f),
			rec.getHeight()/spriteData->rect->getHeight()*((spriteData->flipV)?-1.0f:1.0f),
			0.0f);

	float rot = -rec.getAngle() + ((spriteData->flipH)?PI:0);
	if(std::abs(rot) > 0.001f && std::abs(rot - PI*2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH)?1.0f:0.0f)),
				-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV)?1.0f:0.0f)),
				0.0f);

	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	SDL_Rect destRect = spriteData->rect->getSDLRect(); //spriteData->flipH, spriteData->flipV);
	SDL_RenderCopy(renderer, spriteData->texture, &sdlRec, &destRect);

	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation, float scale)
{
	glPushMatrix();

	Rectangle rec(image.getRectangle());
	rec.scaleF(scale, Vector3D(true));

	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH)?1:0),
				translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV)?1:0),
				0.0f);

	glScalef(rec.getWidth()/spriteData->rect->getWidth()*((spriteData->flipH)?-1.0f:1.0f),
			rec.getHeight()/spriteData->rect->getHeight()*((spriteData->flipV)?-1.0f:1.0f),
			0.0f);

	float rot = -rec.getAngle() + ((spriteData->flipH)?PI:0);
	if(std::abs(rot) > 0.001f && std::abs(rot - PI*2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH)?1.0f:0.0f)),
				-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV)?1.0f:0.0f)),
				0.0f);

	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	SDL_Rect destRect = spriteData->rect->getSDLRect(spriteData->flipH, spriteData->flipV);
	SDL_RenderCopy(renderer, spriteData->texture, &sdlRec, &destRect);

	glPopMatrix();
}

SDL_Texture* Graphics::loadTextureFromSurface(SDL_Surface *surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface);
}

void Graphics::loadTextures(std::vector<SDL_Surface*>& surfaces, std::map<std::string, int>& names)
{
	this->names.insert(names.begin(), names.end());
	for(unsigned i=0; i<surfaces.size(); i++)
	{
		textures.push_back(loadTextureFromSurface(surfaces[i]));
	}
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

SDL_Texture* Graphics::getTexture(std::string textureName)
{
	if(!textureName.compare(""))
			return NULL;

	std::map<std::string, int>::iterator it;

	it = names.find(textureName);
	assert(it != names.end());
	int i = it->second;
	return textures[i];

}
