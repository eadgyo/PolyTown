
#ifndef SPRITEDATA_H_
#define SPRITEDATA_H_

#include "mySurface.h"
#include <string.h>
#include "../Maths/sRectangle.h"


class SpriteData
{
public:
	inline SpriteData()
	{
		flipH = false;
		flipV = false;
		rect = new sRectangle(0, 0, 0, 0);
		texture = NULL;
		textureName = "";
		isText = false;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 0.0f;
	};
	inline SpriteData(sRectangle* rect)
	{
		flipH = false;
		flipV = false;
		this->rect = rect;
		texture = NULL;
		textureName = "";
		isText = false;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 0.0f;
	};
	inline SpriteData(mySurface* texture, std::string textureName)
	{
		flipH = false;
		flipV = false;
		rect = new sRectangle(0, 0, 0, 0);
		this->texture = texture;
		this->textureName = textureName;
		isText = false;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 0.0f;
	};

	mySurface* texture;
	std::string textureName;
	sRectangle* rect;
	bool flipH, flipV, isText;
	float r, g, b, a;
};

#endif /* SPRITEDATA_H_ */
