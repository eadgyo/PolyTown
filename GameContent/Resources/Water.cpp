#include "Water.h"

Water::Water() : m_water_needs(0), m_water_tower(NULL)
{
}

Water::Water(p_uint water_needs) : m_water_needs(water_needs)
{
}

// ----- GETTER ----- //
bool Water::hasWater() const
{
    return (m_water_tower != NULL);
}
