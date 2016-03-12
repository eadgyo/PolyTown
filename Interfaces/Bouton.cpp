#include "Bouton.h"



Bouton::Bouton(int x, int y, int width, int height)
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	textSize = 16;
	text = "";
	rectangle.set((float) x, (float) y, (float) width, (float) height);
}

Bouton::Bouton(std::string text, int x, int y, int width, int height)
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	textSize = 16;
	this->text = text;
	rectangle.set((float) x, (float) y, (float) width, (float) height);
}

Bouton::~Bouton()
{
	// Negro t'y est à moi
}

void Bouton::update(float dt)
{
	// Si besoin on peut créer d'autres boutons et les faire hériter de cette classe
}

void Bouton::render(Graphics* graphics)
{
	// Rendu du bouton
	// Si besoin d'améliorations faire un héritage
	graphics->setColor(r, g, b, a);
	graphics->render(rectangle);
	graphics->renderTextCentered(text, rectangle.getCenter(), textSize);
}

bool Bouton::isColliding(const Vector3D& pos)
{
	// Création d'un carré de coté 2 et qui a pour centre la position de la souris
	// Nous aurions pu utiliser juste la position de la souris, mais on se permet 
	// une petite marge d'erreur ainsi.
	sRectangle mouseRect(pos - Vector3D(1, 1) , Vector3D(2, 2));
	// On test juste la collision entre les deux rectangles
	return rectangle.collision(mouseRect);
}

void Bouton::setColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}