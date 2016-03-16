
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
	};
	inline SpriteData(sRectangle* rect)
	{
		flipH = false;
		flipV = false;
		this->rect = rect;
		texture = NULL;
		textureName = "";
		isText = false;
	};
	inline SpriteData(mySurface* texture, std::string textureName)
	{
		flipH = false;
		flipV = false;
		rect = new sRectangle(0, 0, 0, 0);
		this->texture = texture;
		this->textureName = textureName;
		isText = false;
	};

	mySurface* texture;
	std::string textureName;
	sRectangle* rect;
	bool flipH, flipV, isText;
};

#endif /* SPRITEDATA_H_ */
