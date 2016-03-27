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
	context = NULL;
	isInitialized = false;
}

void Graphics::init(std::string windowName, int width, int height)
{
	if (screen != NULL)
		return;
	if (isInitialized)
		return;

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
			if (TTF_Init() != -1)
			{
				// Création du context OpenGL
				SDL_GLContext l_context = SDL_GL_CreateContext(screen);
				context = &l_context;
				// On active l'alpha
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				isInitialized = true;
				return;
			}
		}
	}
	std::cout << "\nFailed to init SDL\n";
}
void Graphics::initGL(int width, int height)
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
	isInitialized = true;
}
void Graphics::initGL3D(float width, float height)
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

	isInitialized = true;
}


void Graphics::clear()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::swapGL()
{
	// Dans le cas ou le graphics n'a pas été init
	assert(isInitialized);

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
	
	// Changement de couleur
	setColor(image.getColor());
	renderCopy(spriteData->texture, sdlRec);

	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation)
{
	glPushMatrix();

	const myRectangle rec = image.getRectangle();
	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH) ? 1 : 0),
		translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV) ? 1 : 0),
		0.0f);

	glScalef(rec.getWidth() / spriteData->rect->getWidth()*((spriteData->flipH) ? -1.0f : 1.0f),
		rec.getHeight() / spriteData->rect->getHeight()*((spriteData->flipV) ? -1.0f : 1.0f),
		0.0f);

	float rot = -rec.getAngle(); //+ ((spriteData->flipH)?PI:0);
	if (std::abs(rot) > 0.001f && std::abs(rot - PI * 2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH) ? 1.0f : 0.0f)),
		-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV) ? 1.0f : 0.0f)),
		0.0f);


	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	glTranslatef((float)-sdlRec.x, (float)-sdlRec.y, 0.0f);
	SDL_Rect destRect = spriteData->rect->getSDLRectDest(); //spriteData->flipH, spriteData->flipV);

															// Changement de couleur
	setColor(image.getColor());
	renderCopy(spriteData->texture, sdlRec);

	glPopMatrix();
}

void Graphics::render(Image& image, const Vector3D& translation, float scale)
{
	glPushMatrix();
	
	myRectangle rec(image.getRectangle());
	rec.scaleF(scale, Vector3D(true));
	SpriteData* spriteData = image.getSpriteData();
	glTranslatef(translation.x() + rec.getCenterX() + ((int)rec.getWidth())*((spriteData->flipH) ? 1 : 0),
		translation.y() + rec.getCenterY() + ((int)rec.getHeight())*((spriteData->flipV) ? 1 : 0),
		0.0f);

	glScalef(rec.getWidth() / spriteData->rect->getWidth()*((spriteData->flipH) ? -1.0f : 1.0f),
		rec.getHeight() / spriteData->rect->getHeight()*((spriteData->flipV) ? -1.0f : 1.0f),
		0.0f);

	float rot = -rec.getAngle(); //+ ((spriteData->flipH)?PI:0);
	if (std::abs(rot) > 0.001f && std::abs(rot - PI * 2) > 0.001f)
		glRotatef(rot, 0, 0, 1.0f);

	glTranslatef(-spriteData->rect->getWidth()*(0.5f - ((spriteData->flipH) ? 1.0f : 0.0f)),
		-spriteData->rect->getHeight()*(0.5f - ((spriteData->flipV) ? 1.0f : 0.0f)),
		0.0f);


	SDL_Rect sdlRec = spriteData->rect->getSDLRect();
	glTranslatef((float)-sdlRec.x, (float)-sdlRec.y, 0.0f);
	SDL_Rect destRect = spriteData->rect->getSDLRectDest(); //spriteData->flipH, spriteData->flipV);

															// Changement de couleur
	setColor(image.getColor());
	renderCopy(spriteData->texture, sdlRec);

	glPopMatrix();
}

void Graphics::renderCopy(mySurface* surface, SDL_Rect& rec)
{
	glBindTexture(GL_TEXTURE_2D, surface->texture);

	//Render texture quad
	float x1 = ((float) rec.x) / surface->image->w;
	float x2 = ((float) rec.x + rec.w) / surface->image->w;
	float y1 = ((float) rec.y) / surface->image->h;
	float y2 = ((float) rec.y + rec.h) / surface->image->h;
	glBegin(GL_QUADS);
	glTexCoord2f(x1, y1); glVertex2f((float) rec.x, (float) rec.y); //Bottom left
	glTexCoord2f(x2, y1); glVertex2f((float) (rec.x + rec.w), (float) rec.y); //Bottom right
	glTexCoord2f(x2, y2); glVertex2f((float) (rec.x + rec.w), (float) (rec.y + rec.h)); //Top right
	glTexCoord2f(x1, y2); glVertex2f((float) rec.x, (float) (rec.y + rec.h)); //Top left
	glEnd();

	// On deselectionne la Texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Graphics::~Graphics()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(screen);
    SDL_Quit();
}

mySurface* Graphics::getTexture(std::string textureName)
{
	if (!textureName.compare(""))
		return NULL;

	std::map<std::string, mySurface*>::iterator it;

	it = names.find(textureName);
	assert(it != names.end());

	return it->second;
}

void Graphics::loadSurface(SDL_Surface* image, std::string name)
{
	GLuint textures = loadSurfaceGL(image);
	mySurface *surface = createMySurface(textures, image);
	
	names[name] = surface;
}
mySurface* Graphics::createMySurface(GLuint texture, SDL_Surface* image)
{
	mySurface *surface = new mySurface();
	surface->image = image;
	surface->texture = texture;
	return surface;
}
GLuint Graphics::loadSurfaceGL(SDL_Surface* image)
{
	GLuint textures;
	glGenTextures(1, &textures);

	glBindTexture(GL_TEXTURE_2D, textures);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);  //Always set the base and max mipmap levels of a texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	// Map the surface to the texture in video memory
	
	switch(image->format->BytesPerPixel)
	{
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels); //GL_PNG
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels); //GL_BITMAP
			break;
		case 1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, image->w, image->h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image->pixels); //GL_BITMAP
			break;
		default:
			std::cout << "Fuck";
			break;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return textures;
}

void Graphics::loadAllSurfaces()
{
	FileManager& fileM = FileManager::getInstance();
	std::map<std::string, SDL_Surface*>::iterator it = fileM.mapBegin();
	std::map<std::string, SDL_Surface*>::iterator end = fileM.mapEnd();
	while(it != end)
	{
		loadSurface(it->second, it->first);
		it++;
	}
}

void Graphics::freeTexture(std::string name)
{
	std::map<std::string, mySurface*>::iterator it;
	it = names.find(name);
	if (it != names.end())
	{
		// Libération de la texture
		glDeleteTextures(1, &(it->second->texture));
		names.erase(it);
	}
}

void Graphics::freeAllSurfaces()
{
	std::map<std::string, mySurface*>::iterator it;
	it = names.begin();
	while (it != names.end())
	{
		// Libération de la texture
		glDeleteTextures(1, &(it->second->texture));
		it++;
	}

	// On vide la map
	names.clear();
}

void Graphics::pushFont(std::string name, std::string path, unsigned size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	assert(font != NULL); // Echec initialisation

	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it == fontNames.end())
	{
		fontNames[fontName] = font;
	}
}

// Prend juste le nom du fichier présent dans /bin/ttf -> exemple test.ttf
void Graphics::pushFontTTF(std::string name, std::string path, unsigned size)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it == fontNames.end())
	{
		TTF_Font* font = FileManager::getInstance().loadFont(path, size);
		assert(font != NULL); // Echec initialisation
		fontNames[fontName] = font;
	}
}

// Prise en compte directe du TTF
void Graphics::pushFontTTF(std::string name, unsigned size)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it == fontNames.end())
	{
		TTF_Font* font = FileManager::getInstance().loadFont(name + ".ttf", size);
		assert(font != NULL); // Echec initialisation
		fontNames[fontName] = font;
	}
}


TTF_Font* Graphics::getFont(std::string name, unsigned size)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it != fontNames.end())
	{
		return it->second;
	}
	return NULL;
}

bool Graphics::isAlreadyPresent(std::string name, unsigned size)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	return (it != fontNames.end());
}

void Graphics::freeFont(std::string name, unsigned size)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it != fontNames.end())
	{
		TTF_CloseFont(it->second);
	}
}

Image* Graphics::createImageFromFont(std::string name, unsigned size, std::string text)
{
	std::string fontName = name + std::to_string(size);
	std::map<std::string, TTF_Font*>::iterator it = fontNames.find(fontName);
	if (it != fontNames.end())
	{
		return createImageFromFont(it->second, text);
	}
	return NULL;
}

Image* Graphics::createImageFromFont(TTF_Font* font, std::string text)
{
	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	GLuint texture = loadSurfaceGL(surfaceMessage);
	mySurface* surface = createMySurface(texture, surfaceMessage);

	Image* image = new Image();
	image->letDeleting(true);
	image->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	image->initialize(this, surface, text);
	return image;
}

void Graphics::renderText(std::string path, std::string text, const Vector3D & pos, unsigned size)
{
	TTF_Font* Sans = TTF_OpenFont(path.c_str(), size); //this opens a font style and sets a size
	assert(Sans != NULL);

	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	GLuint texture = loadSurfaceGL(surfaceMessage);
	mySurface* surface = createMySurface(texture, surfaceMessage);

	Image image;
	image.letDeleting(true);
	image.setColor(1.0f, 1.0f, 1.0f, 1.0f);
	image.initialize(this, surface, text);
	image.setLeftPos(pos);
	render(image);

	TTF_CloseFont(Sans);
}

void Graphics::renderTextCentered(std::string path, std::string text, const Vector3D & pos, unsigned size)
{
	TTF_Font* Sans = TTF_OpenFont(path.c_str(), size); //this opens a font style and sets a size
	assert (Sans != NULL);

	SDL_Color White = { 255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	GLuint texture = loadSurfaceGL(surfaceMessage);
	mySurface* surface = createMySurface(texture, surfaceMessage);

	Image image;
	image.letDeleting(true);
	image.setColor(1.0f, 1.0f, 1.0f, 1.0f);
	image.initialize(this, surface, text);
	image.setPosition(pos);
	render(image);
	
	TTF_CloseFont(Sans);
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
void Graphics::render(const Form& form, const Vector3D& translation)
{
	glBegin(GL_POLYGON);
	for (unsigned i = 0; i<form.size(); i++)
	{
		Vector3D a = form.get(i) + translation;
		glVertex3f(a.x(), a.y(), a.z());
	}
	glEnd();
}
void Graphics::render(const Form& form, const Vector3D& translation, float scale)
{
	glBegin(GL_POLYGON);
	for (unsigned i = 0; i<form.size(); i++)
	{
		Vector3D a = (form.get(i) + translation)*scale;
		glVertex3f(a.x(), a.y(), a.z());
	}
	glEnd();
}

void Graphics::setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void Graphics::setColor(myColor color)
{
	glColor4f(color.r, color.g, color.b, color.a);
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


