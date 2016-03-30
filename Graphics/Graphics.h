/*
* Graphics.h
*
*  Created on: Mar 3, 2016
*      Author: ronan-h
*/

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
class Graphics;

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <Windows.h>

#else

#include <unistd.h>
#include <stdlib.h>
#endif

#include <GL/glew.h>
#include "mySurface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include "../Maths/Vector3D.h"
#include "../Maths/Form.h"
#include <string>
#include <assert.h>
#include "Image.h"
#include <vector>
#include <map>
#include "myColor.h"



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
	void render(const Form& form, const Vector3D& translation);
	void render(const Form& form, const Vector3D& translation, float scale);
	void renderCopy(mySurface* surface, SDL_Rect& rec);
	GLuint loadSurfaceGL(SDL_Surface* image);
	mySurface* createMySurface(GLuint texture, SDL_Surface* image);
	void loadSurface(SDL_Surface* image, std::string name);
	void loadAllSurfaces();
	void freeTexture(std::string name);
	void freeAllSurfaces();
	void translate(Vector3D translate) { glTranslatef(translate.x(), translate.y(), translate.z()); };
	void scale(float scale) { glScalef(scale, scale, scale); };

	// Fonts
	void renderText(std::string path, std::string text, const Vector3D & pos, unsigned size);
	void renderTextCentered(std::string path, std::string text, const Vector3D & pos, unsigned size);
	void renderTextCenteredTTF(std::string police, std::string text, myColor textColor, const Vector3D & pos, unsigned size);
	TTF_Font* getFont(std::string name, unsigned size);
	bool isAlreadyPresent(std::string fontName, unsigned size);
	void pushFont(std::string name, std::string path, unsigned size);
	void pushFontTTF(std::string name, std::string path, unsigned size);
	void pushFontTTF(std::string name, unsigned size);
	void freeFont(std::string name, unsigned size);
	Image* createImageFromFont(std::string name, unsigned size, std::string text);
	Image* createImageFromFont(TTF_Font* font, std::string text);

	// Draw forms
	void drawLine(const Vector3D& p1, const Vector3D& p2);
	void drawForm(const Form& form);
	void drawTriangle(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3);
	void setColor(float r, float g, float b);
	void setColor(myColor color);
	// Gestion de la transparence
	void setColor(float r, float g, float b, float a);
	void setLineSize(float a);

private:
	SDL_Window *screen;
	SDL_GLContext* context;
	std::map<std::string, mySurface*> names;
	std::map<std::string, TTF_Font*> fontNames;
	bool isInitialized;
};

#endif /* GRAPHICS_H_ */
