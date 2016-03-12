/*
* Graphics.h
*
*  Created on: Mar 3, 2016
*      Author: ronan-h
*/

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
class Graphics;

#include <Windows.h>
#include <GL/glew.h>
#include "mySurface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include "../Maths/Vector3D.h"
#include "../Maths/Form.h"
#include <string>
#include <assert.h>
#include "Image.h"
#include <vector>
#include <map>




class Graphics
{
public:
	Graphics();
	virtual ~Graphics();
	void init(std::string windowName, int width, int height);
	mySurface* getTexture(std::string textureName);
	void initGL(int width, int height);
	void initGL3D(float width, float height);
	void clear();
	void swapGL();
	void render(Image& image);
	void render(Image& image, const Vector3D& translation);
	void render(Image& image, const Vector3D& translation, float scale);
	void render(SDL_Surface *texture, SDL_Rect* dest);
	void render(const Form& form);
	void renderCopy(mySurface* surface, SDL_Rect& rec);
	void loadSurface(SDL_Surface* image, std::string name);
	void loadAllSurfaces();
	void renderText(std::string text, const Vector3D& pos, float size);
	void renderTextCentered(std::string text, const Vector3D& pos, float size);
	

	// Draw forms
	void drawLine(const Vector3D& p1, const Vector3D& p2);
	void drawForm(const Form& form);
	void drawTriangle(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3);
	void setColor(float r, float g, float b);
	// Gestion de la transparence
	void setColor(float r, float g, float b, float a);
	void setSize(float a);

private:
	SDL_Window *screen;
	SDL_GLContext* context;
	std::vector<mySurface*> surfaces;
	std::map<std::string, int> names;
};

#endif /* GRAPHICS_H_ */