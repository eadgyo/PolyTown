#include "Manufactory.h"

Manufactory::Manufactory(int x, int y) :
    QTEntityBuild(MANUFACTORY_RECTANGLE(x, y)),
    Factory(MANUFACTORY_MAX_WORKERS, MANUFACTORY_INCOME_RATE),
    Energy(MANUFACTORY_ENERGY_NEEDS),
    Water(MANUFACTORY_WATER_NEEDS),
    m_water_pollution(NULL),
    m_air_pollution(NULL)
{
    setName(MANUFACTORY_NAME);
}

// ----- GETTER ----- //
p_uint Manufactory::getEnergyNeeds() const
{
    if (isWorking()) {
        return m_workers * m_energy_needs;
    } else {
        return 0;
    }
}

p_uint Manufactory::getWaterNeeds() const
{
    if (isWorking()) {
        return m_workers * m_water_needs;
    } else {
        return 0;
    }
}

bool Manufactory::isWorking() const
{
    return (m_power_plant != NULL && m_water_tower != NULL);
}

// ----- SETTER ----- //
void Manufactory::init(WaterPollution* water_pollution, AirPollution* air_pollution)
{
    m_water_pollution = water_pollution;
    m_air_pollution = air_pollution;
}

void Manufactory::update()
{
    if (isWorking()) {
        m_water_pollution->increasePollution(m_workers);
        m_air_pollution->increasePollution(m_workers);
    }
}