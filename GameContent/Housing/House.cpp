#include "House.h"

House::House(Graphics* graphics, int x, int y) :
    Displayable(HOUSE_RECTANGLE(x, y), new Image(graphics, HOUSE_FRAME_WIDTH, HOUSE_FRAME_HEIGHT, HOUSE_FRAME_NUMBER, HOUSE_IMAGE_COLS, HOUSE_IMAGE_NAME), x, y),
    Housing(HOUSE_MAX_INHAB),
    Energy(HOUSE_ENERGY_NEEDS),
    Water(HOUSE_WATER_NEEDS)
{
}

House::House(Graphics* graphics, int x, int y, p_uint energy_needs, p_uint water_needs) :
    Displayable(HOUSE_RECTANGLE(x, y), new Image(graphics, HOUSE_FRAME_WIDTH, HOUSE_FRAME_HEIGHT, HOUSE_FRAME_NUMBER, HOUSE_IMAGE_COLS, HOUSE_IMAGE_NAME), x, y),
    Housing(HOUSE_MAX_INHAB),
    Energy(energy_needs),
    Water(water_needs)
{
}