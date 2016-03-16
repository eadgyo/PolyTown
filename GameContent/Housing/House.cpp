#include "House.h"

House::House(Graphics* graphics) :
    QTEntity(HOUSE_RECTANGLE(0, 0)),
    Image(graphics, HOUSE_FRAME_WIDTH, HOUSE_FRAME_HEIGHT, HOUSE_FRAME_NUMBER, HOUSE_IMAGE_COLS, HOUSE_IMAGE_NAME),
    Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
	setPos(Vector3D(0, 0));
}

House::House(Graphics* graphics, int x, int y) :
    QTEntity(HOUSE_RECTANGLE(x, y)),
    Image(graphics, HOUSE_FRAME_WIDTH, HOUSE_FRAME_HEIGHT, HOUSE_FRAME_NUMBER, HOUSE_IMAGE_COLS, HOUSE_IMAGE_NAME),
    Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
    setPos(Vector3D(x, y));
}

House::House(Graphics * graphics, int x, int y, p_uint water_needs, p_uint energy_needs) :
    QTEntity(HOUSE_RECTANGLE(x, y)),
    Image(graphics, HOUSE_FRAME_WIDTH, HOUSE_FRAME_HEIGHT, HOUSE_FRAME_NUMBER, HOUSE_IMAGE_COLS, HOUSE_IMAGE_NAME),
    Housing(HOUSE_MAX_INHAB, water_needs, energy_needs)
{
    setPos(Vector3D(x, y));
}