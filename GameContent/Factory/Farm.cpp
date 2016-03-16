#include "Farm.h"

Farm::Farm(Image& image, myRectangle& rect) :
    m_output_rate(),
    m_water_tower(NULL),
    m_water_pollution_area(NULL)
{
}

Farm::Farm(std::string name, Image& image, myRectangle& rect) :
    m_output_rate(),
    m_water_tower(NULL),
    m_water_pollution_area(NULL)
{
}