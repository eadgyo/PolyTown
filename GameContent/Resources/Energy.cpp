#include "Energy.h"

Energy::Energy() : m_energy_needs(0), m_power_plant(NULL)
{
}

Energy::Energy(p_uint energy_needs) : m_energy_needs(energy_needs)
{
}

// ----- GETTER ----- //
bool Energy::hasEnergy() const
{
    return (m_power_plant != NULL);
}

PowerPlant * Energy::getPowerPlant()
{
	return m_power_plant;
}

void Energy::setPowerPlant(PowerPlant* power_plant)
{
	m_power_plant = power_plant;
}
