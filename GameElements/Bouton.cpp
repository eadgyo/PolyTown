#include "Bouton.h"



Bouton::Bouton(Graphics* graphics, int x, int y, int width, int height) : graphics(graphics)
{
	color.r = 1;
	color.g = 1;
	color.b = 1;
	color.a = 1;
	rectangle.set((float) x, (float) y, (float) width, (float) height);
}


Bouton::~Bouton()
{
	// Negro t'y est � moi
}

void Bouton::update(float dt)
{
	// Si besoin on peut cr�er d'autres boutons et les faire h�riter de cette classe
}

void Bouton::render(Graphics* graphics)
{
	// Rendu du bouton
	// Si besoin d'am�liorations faire un h�ritage
	graphics->setColor(color);
	graphics->render(rectangle);
}
void Bouton::render(Graphics* graphics, const Vector3D& translation)
{
	// Rendu du bouton
	// Si besoin d'am�liorations faire un h�ritage
	graphics->setColor(color);
	graphics->render(rectangle, translation);
}

bool Bouton::isColliding(const Vector3D& pos)
{
	// Cr�ation d'un carr� de cot� 2 et qui a pour centre la position de la souris
	// Nous aurions pu utiliser juste la position de la souris, mais on se permet 
	// une petite marge d'erreur ainsi.
	sRectangle mouseRect(pos - Vector3D(1, 1) , 2, 2);
	// On test juste la collision entre les deux rectangles
	return rectangle.collision(mouseRect);
}

void Bouton::setColor(myColor color)
{
	this->color.a = color.a;
	this->color.r = color.r;
	this->color.g = color.g;
	this->color.b = color.b;
}

void Bouton::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

myColor Bouton::getColor()
{
	return color;
}
