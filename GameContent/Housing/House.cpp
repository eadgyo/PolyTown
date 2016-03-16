#include "House.h"

House::House(Graphics* graphics, myRectangle & rect) :
    QTEntity(rect),
    Image(graphics, SPRITES_WIDTH, SPRITES_HEIGHT, 0, 10, SPRITES_IMAGE),
    Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
	setPos(Vector3D(0, 0));
}

House::House(Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs) :
    Housing(HOUSE_MAX_INHAB, water_needs, energy_needs)
{
}

House::House(std::string name, Image & image, myRectangle & rect) :
    Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
}

House::House(std::string name, Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs) :
    Housing(HOUSE_MAX_INHAB, water_needs, energy_needs)
{
}