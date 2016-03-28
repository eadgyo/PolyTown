#include "Building.h"

Building::Building(int x, int y) :
    QTEntityBuild(BUILDING_RECTANGLE(x, y)),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
    m_floor = BUILDING_FLOOR;
    setName(BUILDING_NAME);
}

Building::Building(int x, int y, p_uint floor) :
	QTEntityBuild(BUILDING_RECTANGLE(x, y)),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
}

Building::Building(int x, int y, p_uint water_needs, p_uint energy_needs) :
	QTEntityBuild(BUILDING_RECTANGLE(x, y)),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
    setName(BUILDING_NAME);
}

Building::Building(int x, int y, p_uint floor, p_uint water_needs, p_uint energy_needs) :
	QTEntityBuild(BUILDING_RECTANGLE(x, y)),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
    setName(BUILDING_NAME);
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
    if (m_floor > BUILDING_MAX_FLOOR) {
        n = m_floor - BUILDING_MAX_FLOOR;
        m_floor = BUILDING_MAX_FLOOR;
    } else {
        m_floor += n;
        n = 0;
    }
    m_max_inhabitants = BUILDING_MAX_INHAB_PER_FLOOR * m_floor;
    return n;
}