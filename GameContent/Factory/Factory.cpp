#include "Factory.h"

Factory::Factory() : m_workers(0), m_max_workers(0), m_income_rate(0)
{
}

Factory::Factory(p_uint max_workers, p_uint income_rate) : m_workers(0), m_max_workers(max_workers), m_income_rate(income_rate)
{
}

// ----- GETTER ----- //
p_uint Factory::getWorkers() const
{
    return m_workers;
}

p_uint Factory::getFreeWorkers() const
{
    if (isWorking()) {
        return (m_max_workers - m_workers);
    } else {
        return 0;
    }
}

p_uint Factory::getIncome() const
{
    return m_workers * m_income_rate;
}

bool Factory::isFull() const
{
    return (m_workers == m_max_workers);
}

bool Factory::isEmpty() const
{
    return (m_workers == 0);
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

void Factory::empty()
{
    m_workers = 0;
}