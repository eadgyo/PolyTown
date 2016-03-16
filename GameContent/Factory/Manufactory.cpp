#include "Manufactory.h"

Manufactory::Manufactory(Image& image, myRectangle& rect) :
    m_power_plant(NULL),
    m_water_tower(NULL),
    m_air_pollution_area(NULL),
    m_water_pollution_area(NULL)
{
}

Manufactory::Manufactory(std::string name, Image& image, myRectangle& rect) :
    m_power_plant(NULL),
    m_water_tower(NULL),
    m_air_pollution_area(NULL),
    m_water_pollution_area(NULL)
{
}