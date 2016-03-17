#ifndef FACTORY_H
#define FACTORY_H

#include "../Constant.h"

#include "Displayable.h"

class Factory : public virtual Displayable
{
public:
    // ----- GETTER ----- //
    p_uint getIncome() const;

    // ----- SETTER ----- //
    p_uint addWorkers(p_uint n);
    p_uint delWorkers(p_uint n);

protected:
    Factory();
    Factory(p_uint max_workers, p_uint income_rate);

    p_uint m_workers;
    p_uint m_max_workers;
    p_uint m_income_rate;
};

#endif // !FACTORY_H