#include "Energy.h"

Energy::Energy() : m_energy_needs(0), m_power_plant(NULL)
{
}

Energy::Energy(p_uint energy_needs) : m_energy_needs(energy_needs)
{
}