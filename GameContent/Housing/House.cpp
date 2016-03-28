#include "House.h"

House::House(int x, int y) :
	QTEntityBuild(HOUSE_RECTANGLE(x, y)),
    Housing(HOUSE_MAX_INHAB),
    Energy(HOUSE_ENERGY_NEEDS),
    Water(HOUSE_WATER_NEEDS)
{
    setName(HOUSE_NAME);
}

House::House(int x, int y, p_uint energy_needs, p_uint water_needs) :
	QTEntityBuild(HOUSE_RECTANGLE(x, y)),
    Housing(HOUSE_MAX_INHAB),
    Energy(energy_needs),
    Water(water_needs)
{
    setName(HOUSE_NAME);
}