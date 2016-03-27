#pragma once

#include "BoutonImage.h"

class Bouton2Images : public BoutonImage
{
public:
	Bouton2Images(Graphics* graphics, Image* image, Image* image2, int x, int y, int width, int height);
	Bouton2Images(Graphics* graphics, Image* image, Image* image2, int x, int y, int width, int height, bool drawRec);

	virtual void render(Graphics * graphics);
	virtual void render(Graphics * graphics, const Vector3D& translation);
	void addColor2(myColor color);

protected:
	myColor m_addColor2;
	Image* m_image2;
};