#include "BoutonImage.h"

BoutonImage::BoutonImage(Graphics* graphics, Image* image, int x, int y, int width, int height) :
    Bouton(graphics, x, y, width, height),
    m_image(image)
{
}

void BoutonImage::render(Graphics * graphics)
{
	graphics->setColor(r, g, b, a);
	graphics->render(rectangle);
	m_image->draw(graphics);
}

void BoutonImage::render(Graphics * graphics, const Vector3D & translation)
{
	graphics->setColor(r, g, b, a);
	graphics->render(rectangle, translation);
	m_image->draw(graphics, translation);
}
