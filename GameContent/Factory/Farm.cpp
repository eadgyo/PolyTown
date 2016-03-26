#include "Farm.h"

Farm::Farm(int x, int y) :
    QTEntity(FARM_RECTANGLE(x, y)),
    Factory(FARM_MAX_WORKERS, FARM_INCOME_RATE),
    Water(FARM_ENERGY_NEEDS),
    m_output_rate(FARM_OUTPUT_RATE)
{
    setName(FARM_NAME);
}

// ----- GETTER ----- //
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
    m_water_pollution->increasePollution(m_workers);
}