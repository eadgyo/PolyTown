#include "Housing.h"

#include <iostream>

const p_uint Housing::m_food_needs = HOUSING_FOOD_NEEDS;

Housing::Housing(p_uint max_inhabitants, p_uint water_needs, p_uint energy_needs)
    : m_inhabitants(0), m_max_inhabitants(max_inhabitants), m_water_needs(water_needs), m_energy_needs(energy_needs), m_hasFood(false), m_hasWater(false), m_hasEnergy(false)
{
}

p_uint Housing::getInhabitants()
{
    return m_inhabitants;
}

p_uint Housing::getFoodNeeds()
{
    return m_inhabitants*m_food_needs;
}

p_uint Housing::getWaterNeeds()
{
    return m_inhabitants*m_water_needs;
}

p_uint Housing::getEnergyNeeds()
{
    return m_inhabitants*m_energy_needs;
}

bool Housing::isFull()
{
    return (m_inhabitants == m_max_inhabitants);
}

bool Housing::hasFood()
{
    return m_hasFood;
}

bool Housing::hasWater()
{
    return m_hasWater;
}

bool Housing::hasEnergy()
{
    return m_hasEnergy;
}
