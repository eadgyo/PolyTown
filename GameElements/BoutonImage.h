#pragma once

#include "Bouton.h"

class BoutonImage : public virtual Bouton
{
public:
    BoutonImage(Image* image, int x, int y, int width, int height);

private:
    Image* m_image;
};