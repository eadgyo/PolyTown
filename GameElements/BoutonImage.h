#pragma once

#include "Bouton.h"

class BoutonImage : public Bouton
{
public:
    BoutonImage(Graphics* graphics, Image* image, int x, int y, int width, int height);
	BoutonImage(Graphics* graphics, Image* image, int x, int y, int width, int height, bool drawRec);

	virtual void render(Graphics* graphics);
	virtual void render(Graphics* graphics, const Vector3D& translation);
	void addColor(myColor color);

protected:
	myColor m_addColor;
    Image* m_image;
};