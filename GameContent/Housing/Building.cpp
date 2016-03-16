#include "Building.h"

Building::Building(Graphics* graphics) :
    QTEntity(BUILDING_RECTANGLE(0, 0)),
    Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR, BUILDING_WATER_NEEDS, BUILDING_ENERGY_NEEDS)
{
    setPos(Vector3D(0, 0));
}

Building::Building(Graphics* graphics, int x, int y) :
    QTEntity(BUILDING_RECTANGLE(x, y)),
    Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR, BUILDING_WATER_NEEDS, BUILDING_ENERGY_NEEDS)
{
    setPos(Vector3D(x, y));
}

Building::Building(Graphics* graphics, int x, int y, p_uint floor) :
    QTEntity(BUILDING_RECTANGLE(x, y)),
    Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR, BUILDING_WATER_NEEDS, BUILDING_ENERGY_NEEDS)
{
    setPos(Vector3D(x, y));
}

Building::Building(Graphics * graphics, int x, int y, p_uint water_needs, p_uint energy_needs) :
    QTEntity(BUILDING_RECTANGLE(x, y)),
    Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME),
    Housing(BUILDING_FLOOR * BUILDING_MAX_INHAB_PER_FLOOR, water_needs, energy_needs)
{
    setPos(Vector3D(x, y));
}

Building::Building(Graphics * graphics, int x, int y, p_uint floor, p_uint water_needs, p_uint energy_needs) :
    QTEntity(BUILDING_RECTANGLE(x, y)),
    Image(graphics, BUILDING_FRAME_WIDTH, BUILDING_FRAME_HEIGHT, BUILDING_FRAME_NUMBER, BUILDING_IMAGE_COLS, BUILDING_IMAGE_NAME),
    Housing(floor * BUILDING_MAX_INHAB_PER_FLOOR, water_needs, energy_needs)
{
    setPos(Vector3D(x, y));
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