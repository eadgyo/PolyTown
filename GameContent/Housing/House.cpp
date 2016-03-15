#include "House.h"

#include "../Constant.h"

#include <iostream>

House::House() : Housing(HOUSE_MAX_INHAB, HOUSE_WATER_NEEDS, HOUSE_ENERGY_NEEDS)
{
}

House::House(p_uint water_needs, p_uint energy_needs) : Housing(HOUSE_MAX_INHAB, water_needs, energy_needs)
{
}