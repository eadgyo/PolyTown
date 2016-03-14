#include "Housing.h"

#include <iostream>

Housing::Housing() : m_inhabitants(0), m_max_inhabitants(0), m_food_needs(0), m_water_needs(0), m_energy_needs(0)
{
}

Housing::Housing(p_uint inhabitants, p_uint max_inhabitants, p_uint food_needs, p_uint water_needs, p_uint energy_needs)
    : m_inhabitants(inhabitants), m_max_inhabitants(max_inhabitants), m_food_needs(food_needs), m_water_needs(water_needs), m_energy_needs(energy_needs)
{
}