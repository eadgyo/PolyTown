/*
 * Graphics.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: ronan-h
 */

#include "Graphics.h"

Graphics::Graphics()
{
	screen = NULL;
}

SDL_Window* Graphics::init(std::string windowName, int width, int height)
{
	if (screen != NULL)
		return false;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// Creation de la fenetre
		screen = SDL_CreateWindow(
			windowName.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_OPENGL); // SDL_WINDOW_FULLSCREEN
		if (screen != NULL)
		{
			//renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
			return screen;
		}
	}
	std::cout << "Failed to init SDL\n";
	return NULL;
}
void Graphics::initGL(SDL_GLContext& context, float width, float height)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Set the cleared screen colour to black
	glViewport(0, 0, width, height);   //This sets up the viewport so that the coordinates (0, 0) are at the top left of the window

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -10, 10);

	//Back to the modelview so we can draw stuff 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen and depth buffer
	glEnable(GL_TEXTURE_2D);

	loadAllSurfaces();
}
void Graphics::initGL3D(SDL_GLContext& context, float width, float height)
{
	GLfloat ratio = (GLfloat)width / (GLfloat)height;

	/* Setup our viewport. */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective
	GLdouble fW, fH;

	fH = tan(45.0f / 360 * M_PI) * 0.1f;
	fW = fH * ratio;

	glFrustum(-fW, fW, -fH, fH, 0.1f, 100.0f);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode(GL_MODELVIEW);
	
	/* Reset The View */
	glLoadIdentity();
	
	SDL_GL_MakeCurrent(screen, context);

	/* Enable smooth shading */
	glShadeModel(GL_SMOOTH);

	/* Set the background red */
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	/* Depth buffer setup */
	glClearDepth(1.0f);

	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::swapGL()
{
	SDL_GL_SwapWindow(screen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::render(SDL_Surface *texture, SDL_Rect* textureRect)
{
	//SDL_RenderCopy(renderer, texture, NULL, NULL);
	std::cout << "Nope";
}


void Graphics::render(Image& image)
{
	glPushMatrix();

	const myRectangle rec = image.getRectangle();
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
	glTranslatef((float) -sdlRec.x, (float) - sdlRec.y, 0.0f);
	SDL_Rect destRect = spriteData->rect->getSDLRectDest(); //spriteData->flipH, spriteData->flipV);
	renderCopy(spriteData->texture, sdlRec);

	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation)
{
	glPushMatrix();

	const myRectangle rec = image.getRectangle();
	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH)?1:0),
				translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV)?1:0),
				0.0f);

	glScalef(rec.getWidth()/spriteData->rect->getWidth()*((spriteData->flipH)?-1.0f:1.0f),
			rec.getHeight()/spriteData->rect->getHeight()*((spriteData->flipV)?-1.0f:1.0f),
			0.0f);

	float rot = -rec.getAngle() + ((spriteData->flipH)?(float) PI:0);
	if(std::abs(rot) > 0.001f && std::abs(rot - PI*2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH)?1.0f:0.0f)),
				-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV)?1.0f:0.0f)),
				0.0f);

	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	SDL_Rect destRect = spriteData->rect->getSDLRect(); //spriteData->flipH, spriteData->flipV);
	//SDL_RenderCopy(renderer, spriteData->texture, &sdlRec, &destRect);
	renderCopy(spriteData->texture, sdlRec);
	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation, float scale)
{
	glPushMatrix();

	myRectangle rec(image.getRectangle());
	rec.scaleF(scale, Vector3D(true));

	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH)?1:0),
				translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV)?1:0),
				0.0f);

	glScalef(rec.getWidth()/spriteData->rect->getWidth()*((spriteData->flipH)?-1.0f:1.0f),
			rec.getHeight()/spriteData->rect->getHeight()*((spriteData->flipV)?-1.0f:1.0f),
			0.0f);

	float rot = -rec.getAngle() + ((spriteData->flipH)?(float) PI:0);
	if(std::abs(rot) > 0.001f && std::abs(rot - PI*2.0f) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH)?1.0f:0.0f)),
				-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV)?1.0f:0.0f)),
				0.0f);

	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	SDL_Rect destRect = spriteData->rect->getSDLRect();
	//SDL_RenderCopy(renderer, spriteData->texture, &sdlRec, &destRect);
	renderCopy(spriteData->texture, sdlRec);
	glPopMatrix();
}

void Graphics::renderCopy(mySurface* surface, SDL_Rect& rec)
{
	glColor4f(1.0f, 1.0f, 1.0f, 0);
	glBindTexture(GL_TEXTURE_2D, surface->texture);

	//Render texture quad
	float x1 = ((float) rec.x) / surface->image->w;
	float x2 = ((float) rec.x + rec.w) / surface->image->w;
	float y1 = ((float) rec.y) / surface->image->h;
	float y2 = ((float) rec.y + rec.h) / surface->image->h;
	glBegin(GL_QUADS);
	glTexCoord2f(x1, y1); glVertex2f(rec.x, rec.y); //Bottom left
	glTexCoord2f(x2, y1); glVertex2f(rec.x + rec.w, rec.y); //Bottom right
	glTexCoord2f(x2, y2); glVertex2f(rec.x + rec.w, rec.y + rec.h); //Top right
	glTexCoord2f(x1, y2); glVertex2f(rec.x, rec.y + rec.h); //Top left
	glEnd();
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

mySurface* Graphics::getTexture(std::string textureName)
{
	if (!textureName.compare(""))
		return NULL;

	std::map<std::string, int>::iterator it;

	it = names.find(textureName);
	assert(it != names.end());
	int i = it->second;
	return surfaces[i];
}

void Graphics::loadSurface(SDL_Surface* image, std::string name)
{
	GLuint textures;
	glGenTextures(1, &textures);

	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Map the surface to the texture in video memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels); //GL_BITMAP

	mySurface *surface = new mySurface();
	surface->image = image;
	surface->texture = textures;
	names[name] = surfaces.size();

	surfaces.push_back(surface);
}
void Graphics::loadAllSurfaces()
{
	FileManager& fileM = FileManager::getInstance();
	for (unsigned i = 0; i < fileM.sizeSurfaces(); i++)
	{
		loadSurface(fileM.getSurface(i), fileM.getNameSurface(i));
	}
}

void Graphics::renderText(std::string text, const Vector3D & pos, float size)
{
}

void Graphics::renderTextCentered(std::string text, const Vector3D & pos, float size)
{
}

// Draw forms
void Graphics::drawLine(const Vector3D& p1, const Vector3D& p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.x(), p1.y(), p1.z());
	glVertex3f(p2.x(), p2.y(), p2.z());
	glEnd();
}

void Graphics::drawTriangle(const Vector3D& p1, const Vector3D& p2,
	const Vector3D& p3)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(p1.x(), p1.y(), p1.z());
	glVertex3f(p2.x(), p2.y(), p2.z());
	glVertex3f(p3.x(), p3.y(), p3.z());
	glEnd();
}

void Graphics::render(const Form& form)
{
	glBegin(GL_POLYGON);
	for (unsigned i = 0; i<form.size(); i++)
	{
		Vector3D a = form.get(i);
		glVertex3f(a.x(), a.y(), a.z());
	}
	glEnd();
}

void Graphics::setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void Graphics::setColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
}

void Graphics::drawForm(const Form& form)
{
	for (unsigned i = 0, j = form.size() - 1; i<form.size(); j = i, i++)
	{
		drawLine(form.get(i), form.get(j));
	}
}

void Graphics::setSize(float a)
{
	glLineWidth(a);
}


