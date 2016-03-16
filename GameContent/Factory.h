#ifndef FACTORY_H
#define FACTORY_H

#include "../Constant.h"

class Factory
{
public:
    // ----- GETTER ----- //
    p_uint getIncome() const;

    // ----- SETTER ----- //
    p_uint addWorkers(p_uint n);
    p_uint delWorkers(p_uint n);

protected:
    p_uint m_workers;
    p_uint m_max_workers;
    p_uint m_income_rate;
};

#endif // !FACTORY_H