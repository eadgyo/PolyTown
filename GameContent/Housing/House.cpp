#include "House.h"

House::House(Image & image, myRectangle & rect) :
    Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
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