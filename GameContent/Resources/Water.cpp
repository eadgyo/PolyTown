#include "Water.h"

Water::Water() : m_water_needs(0), m_water_tower(NULL)
{
}

Water::Water(p_uint water_needs) : m_water_needs(water_needs), m_water_tower(NULL)
{
}

// ----- GETTER ----- //
bool Water::hasWater() const
{
    return (m_water_tower != NULL);
}

WaterTower * Water::getWaterTower()
{
	return m_water_tower;
}

void Water::setWaterTower(WaterTower * waterTower)
{
	m_water_tower = waterTower;
}
