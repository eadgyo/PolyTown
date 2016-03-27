#include "BoutonImage.h"

BoutonImage::BoutonImage(Graphics* graphics, Image* image, int x, int y, int width, int height) :
    Bouton(graphics, x, y, width, height),
    m_image(image)
{
	m_addColor = 0;
	m_image->setX((float) x);
	m_image->setY((float) y);
}

BoutonImage::BoutonImage(Graphics * graphics, Image * image, int x, int y, int width, int height, bool drawRec) :
	Bouton(graphics, x, y, width, height),
	m_image(image)
{
	m_addColor = 0;
	m_image->setX((float)x);
	m_image->setY((float)y);
}

void BoutonImage::render(Graphics * graphics)
{
	myColor save = m_image->getColor();
	m_image->setColor(save + m_addColor);
	m_image->draw(graphics);
	m_image->setColor(save);
	if(drawRec)
		Bouton::render(graphics);
	
}

void BoutonImage::render(Graphics * graphics, const Vector3D & translation)
{
	myColor save = m_image->getColor();
	m_image->setColor(save + m_addColor);
	m_image->draw(graphics, translation);
	m_image->setColor(save);
	if (drawRec)
		Bouton::render(graphics, translation);
	
}

void BoutonImage::addColor(myColor color)
{
	m_addColor = color;
}
