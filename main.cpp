#include <Windows.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Maths/Vector3D.h"
#include <iostream>
#include "Maths/myRectangle.h"
#include "Maths/Form.h"
#include "FileManager.h"
#define WIDTH 1500
#define HEIGHT 800

int main(int argc, char* args[])
{
	Graphics *g = new Graphics();
	
	FileManager& fileM = FileManager::getInstance();
	fileM.initialize();
	
	// Création du module de gestion rendu openGL
	SDL_GLContext context = SDL_GL_CreateContext(g->init("Affichage forme", WIDTH, HEIGHT));
	g->initGL(context, WIDTH, HEIGHT);
	
	Form form;
	form.addPoint(Vector3D(10, 10));
	form.addPoint(Vector3D(70, 60));
	form.addPoint(Vector3D(200, 30));
	form.addPoint(Vector3D(100, 120));
	form.addPoint(Vector3D(10, 100));
	form.triangulate();
	glColor4f(1.0, 0, 0, 0.0);
	std::vector<Form> forms = form.getConvexForms();
	for (unsigned i = 0; i < form.getConvexFormsSize(); i++)
	{
		g->drawForm(forms.at(i));
	}
	//g->drawForm(form);

	g->swapGL();
	SDL_Delay(2000);
	/*
	Image image;
	image.initialize(g, 250, 250, 2, "a.png");
	image.setCurrentFrame(3);
	//image.flipH(Vector3D(true));
	image.scale(1.0f, Vector3D(true));
	image.setPositionX(500);
	image.setPositionY(500);
	
	image.draw();
	g->render(image);
	glColor4f(1.0, 0, 0, 0.0);
	g->drawLines(form);
	g->swapGL();

	SDL_Delay(2000);
	
	image.setCurrentFrame(1);
	image.draw();
	glColor4f(1.0, 0, 0, 0.0);
	g->drawLines(form);
	g->swapGL();
	SDL_Delay(2000);
	*/

	// Libère les éléments
	/*
	SDL_GL_DeleteContext(context);
	SDL_Quit();*/
    return 0;
}
