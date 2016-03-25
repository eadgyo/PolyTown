#include "PollutionArea.h"

PollutionArea::PollutionArea(unsigned int pollution, unsigned int decrease_rate) :
    m_quantity(0),
    m_pollution(pollution),
    m_decrease_rate(decrease_rate)
{
}

// ----- GETTER ----- //
p_uint PollutionArea::getIntensity() const
{
    return getIntensity(0);
}

p_uint PollutionArea::getIntensity(unsigned int d) const
{
    return (m_quantity - d) * m_pollution;
}

unsigned int PollutionArea::getRadius() const
{
    return m_quantity;
}

// ----- SETTER ----- //
void PollutionArea::increasePollution(unsigned int n)
{
    m_quantity += n;
    castCircle()->set(m_quantity);
}

void PollutionArea::decreasePollution()
{
    if (m_quantity > m_decrease_rate) {
        m_quantity -= m_decrease_rate;
    } else {
        m_quantity = 0;
    }
}