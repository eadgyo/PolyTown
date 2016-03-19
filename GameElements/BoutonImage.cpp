#include "BoutonImage.h"

BoutonImage::BoutonImage(Image* image, int x, int y, int width, int height) :
    Bouton(x, y, width, height),
    m_image(image)
{
}