
#ifndef SPRITEDATA_H_
#define SPRITEDATA_H_

#include <SDL2/SDL.h>
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
	};
	inline SpriteData(sRectangle* rect)
	{
		flipH = false;
		flipV = false;
		this->rect = rect;
		texture = NULL;
		textureName = "";
	};
	inline SpriteData(SDL_Texture* texture, std::string textureName)
	{
		flipH = false;
		flipV = false;
		rect = new sRectangle(0, 0, 0, 0);
		this->texture = texture;
		this->textureName = textureName;
	};

	SDL_Texture* texture;
	std::string textureName;
	sRectangle* rect;
	bool flipH, flipV;
};

#endif /* SPRITEDATA_H_ */
