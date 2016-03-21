#pragma once

#include "Bouton.h"

class BoutonImage : public Bouton
{
public:
    BoutonImage(Graphics* graphics, Image* image, int x, int y, int width, int height);
	void render(Graphics* graphics);
	void render(Graphics* graphics, const Vector3D& translation);

protected:
    Image* m_image;
};