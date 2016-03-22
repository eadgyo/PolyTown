#include "Bouton.h"



Bouton::Bouton(Graphics* graphics, int x, int y, int width, int height) : graphics(graphics)
{
	r = 1;
	g = 1;
	b = 1;
	a = 1;
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
}
void Bouton::render(Graphics* graphics, const Vector3D& translation)
{
	// Rendu du bouton
	// Si besoin d'améliorations faire un héritage
	graphics->setColor(r, g, b, a);
	graphics->render(rectangle, translation);
}

bool Bouton::isColliding(const Vector3D& pos)
{
	// Création d'un carré de coté 2 et qui a pour centre la position de la souris
	// Nous aurions pu utiliser juste la position de la souris, mais on se permet 
	// une petite marge d'erreur ainsi.
	sRectangle mouseRect(pos - Vector3D(1, 1) , 2, 2);
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