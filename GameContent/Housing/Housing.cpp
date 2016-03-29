#include "Housing.h"

const p_uint Housing::m_food_needs = HOUSING_FOOD_NEEDS;

Housing::Housing() : m_inhabitants(0), m_max_inhabitants(0)
{
}

Housing::Housing(p_uint max_inhabitants) : m_inhabitants(0), m_max_inhabitants(max_inhabitants)
{
}

// ----- GETTER ----- //
p_uint Housing::getInhabitants() const
{
    return m_inhabitants;
}

p_uint Housing::getFreeInhabitants() const
{
    return (m_max_inhabitants - m_inhabitants);
}

p_uint Housing::getFoodNeeds() const
{
    return m_inhabitants * m_food_needs;
}

p_uint Housing::getWaterNeeds() const
{
    return m_inhabitants * m_water_needs;
}

p_uint Housing::getEnergyNeeds() const
{
    return m_inhabitants * m_energy_needs;
}

p_uint Housing::getScore() const
{
    if (m_power_plant && m_water_tower) {
        return getFreeInhabitants();
    } else {
        return 0;
    }
}

bool Housing::isFull() const
{
    return (m_inhabitants == m_max_inhabitants);
}

bool Housing::isEmpty() const
{
    return (m_inhabitants == 0);
}

bool Housing::hasFood() const
{
    return m_hasFood;
}

// ----- SETTER ----- //

p_uint Housing::addInhabitants(p_uint n)
{
    m_inhabitants += n;
    if (m_inhabitants > m_max_inhabitants) {
        n = m_inhabitants - m_max_inhabitants;
        m_inhabitants = m_max_inhabitants;
        return n;
    } else {
        return 0;
    }
}

p_uint Housing::delInhabitants(p_uint n)
{
    if (m_inhabitants < n) {
        n -= m_inhabitants;
        m_inhabitants = 0;
        return n;
    } else {
        m_inhabitants -= n;
        return 0;
    }
}

void Housing::upgrade(p_uint water_needs, p_uint energy_needs)
{
    m_water_needs = water_needs;
    m_energy_needs = energy_needs;
}