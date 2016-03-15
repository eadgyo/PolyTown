#include "Building.h"

Building::Building() :
    Housing(BUILDING_FLOOR*BUILDING_MAX_INHAB_PER_FLOOR, BUILDING_WATER_NEEDS, BUILDING_ENERGY_NEEDS),
    m_floor(BUILDING_FLOOR),
    m_max_floor(BUILDING_MAX_FLOOR),
    m_max_inhabitants_per_floor(BUILDING_MAX_INHAB_PER_FLOOR)
{
}

Building::Building(p_uint water_needs, p_uint energy_needs) :
    Housing(HOUSE_MAX_INHAB, water_needs, energy_needs),
    m_floor(BUILDING_FLOOR),
    m_max_floor(BUILDING_MAX_FLOOR),
    m_max_inhabitants_per_floor(BUILDING_MAX_INHAB_PER_FLOOR)
{
}

Building::Building(p_uint water_needs, p_uint energy_needs, p_uint floor) :
    Housing(floor * BUILDING_FLOOR, water_needs, energy_needs), m_floor(floor),
    m_max_floor(BUILDING_MAX_FLOOR),
    m_max_inhabitants_per_floor(BUILDING_MAX_INHAB_PER_FLOOR)
{
}

// ----- GETTER ----- //
p_uint Building::getFloors() const
{
    return m_floor;
}

// ----- SETTER ----- //
p_uint Building::addFloors(p_uint n)
{
    m_floor += n;
    if (m_floor > m_max_floor) {
        n = m_floor - m_max_floor;
        m_floor = m_max_floor;
    } else {
        m_floor += n;
        n = 0;
    }
    m_max_inhabitants = m_max_inhabitants_per_floor * m_floor;
    return n;
}