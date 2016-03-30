#ifndef FACTORY_H
#define FACTORY_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../../QuadTree/QTEntityBuild.h"

class Factory : public virtual QTEntityBuild
{
public:
    // ----- GETTER ----- //
    p_uint getWorkers() const;
    p_uint getFreeWorkers() const;
    p_uint getIncome() const;

    virtual bool isWorking() const = 0;
    bool isFull() const;
    bool isEmpty() const;

    // ----- SETTER ----- //
    p_uint addWorkers(p_uint n);
    p_uint delWorkers(p_uint n);
    void Factory::empty();

    virtual void update() = 0;

protected:
    Factory();
    Factory(p_uint max_workers, p_uint income_rate);

    p_uint m_workers;
    p_uint m_max_workers;
    p_uint m_income_rate;
};

#endif // !FACTORY_H
