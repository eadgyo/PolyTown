#include "Farm.h"

Farm::Farm(int x, int y) :
    QTEntityBuild(FARM_RECTANGLE(x, y)),
    Factory(FARM_MAX_WORKERS, FARM_INCOME_RATE),
    Water(FARM_WATER_NEEDS),
    m_output_rate(FARM_OUTPUT_RATE)
{
    setName(FARM_NAME);
}

// ----- GETTER ----- //

p_uint Farm::getWaterNeeds() const
{
    return m_water_needs;
}

p_uint Farm::getProdution() const
{
    if (isWorking()) {
        return (m_output_rate * m_workers);
    } else {
        return 0;
    }
}

bool Farm::isWorking() const
{
    return (m_water_tower != NULL);
}

// ----- SETTER ----- //
void Farm::init(WaterPollution* water_pollution)
{
    m_water_pollution = water_pollution;
}

void Farm::update()
{
    if (isWorking()) {
        m_water_pollution->increasePollution(m_workers);
    }
}