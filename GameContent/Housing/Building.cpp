#include "Building.h"

Building::Building(Graphics* graphics, int x, int y) :
    Displayable(BUILDING_NAME, BUILDING_RECTANGLE(x, y), new Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME), x, y),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
    m_floor = BUILDING_FLOOR;
}

Building::Building(Graphics * graphics, int x, int y, p_uint floor) :
    Displayable(BUILDING_NAME, BUILDING_RECTANGLE(x, y), new Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME), x, y),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
}

Building::Building(Graphics * graphics, int x, int y, p_uint water_needs, p_uint energy_needs) :
    Displayable(BUILDING_NAME, BUILDING_RECTANGLE(x, y), new Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME), x, y),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
{
}

Building::Building(Graphics * graphics, int x, int y, p_uint floor, p_uint water_needs, p_uint energy_needs) :
    Displayable(BUILDING_NAME, BUILDING_RECTANGLE(x, y), new Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME), x, y),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR),
    Energy(BUILDING_ENERGY_NEEDS),
    Water(BUILDING_WATER_NEEDS)
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