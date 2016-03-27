#include "Bouton2Images.h"

Bouton2Images::Bouton2Images(Graphics* graphics, Image* image, Image* image2, int x, int y, int width, int height) :
	BoutonImage(graphics, image, x, y, width, height),
	m_image2(image2)
{
	m_addColor2 = 0;
	m_image2->setX((float)x);
	m_image2->setY((float)y);
}

Bouton2Images::Bouton2Images(Graphics * graphics, Image * image, Image * image2, int x, int y, int width, int height, bool drawRec):
	BoutonImage(graphics, image, x, y, width, height, drawRec),
	m_image2(image2)
{
	m_addColor2 = 0;
	m_image2->setX((float)x);
	m_image2->setY((float)y);
}

void Bouton2Images::render(Graphics * graphics)
{
	render(graphics, Vector3D(false));
}

void Bouton2Images::render(Graphics * graphics, const Vector3D & translation)
{
	myColor save = m_image2->getColor();
	m_image2->setColor(save + m_addColor2);
	m_image2->draw(graphics, translation);
	m_image2->setColor(save);
	BoutonImage::render(graphics, translation);
	//graphics->setColor(myColor(1.0f, 0.0f, 0.0f));
	//graphics->drawForm(rectangle);
}

void Bouton2Images::addColor2(myColor color)
{
	m_addColor2 = color;
}