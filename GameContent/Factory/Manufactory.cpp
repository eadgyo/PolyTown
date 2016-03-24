#include "Manufactory.h"

Manufactory::Manufactory(int x, int y) :
    QTEntity(MANUFACTORY_RECTANGLE(x, y)),
    Factory(MANUFACTORY_MAX_WORKERS, MANUFACTORY_INCOME_RATE),
    Energy(MANUFACTORY_ENERGY_NEEDS),
    Water(MANUFACTORY_WATER_NEEDS)
{
    setName(MANUFACTORY_NAME);
}

// ----- GETTER ----- //
bool Manufactory::isWorking() const
{
    return (m_power_plant != NULL && m_water_tower != NULL);
}