#ifndef ENERGY_H
#define ENERGY_H

#include "../Constant.h"

class Energy
{
public:
    Energy();
    Energy(p_uint energy_needs);

protected:
    p_uint m_energy_needs;
};

#endif // !ENERGY_H