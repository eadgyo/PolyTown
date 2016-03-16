#include "Factory.h"

// ----- GETTER ----- //
p_uint Factory::getIncome() const
{
    return m_workers * m_income_rate;
}

// ----- SETTER ----- //
p_uint Factory::addWorkers(p_uint n)
{
    m_workers += n;
    if (m_workers > m_max_workers) {
        n = m_workers - m_max_workers;
        m_workers = m_max_workers;
        return n;
    } else {
        m_workers += n;
        return 0;
    }
}

p_uint Factory::delWorkers(p_uint n)
{
    if (m_workers < n) {
        n -= m_workers;
        m_workers = 0;
        return n;
    } else {
        m_workers -= n;
        return 0;
    }
}