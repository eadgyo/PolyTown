#ifndef WATER_H
#define WATER_H

#include "../Constant.h"

class Water
{
public:
    Water();
    Water(p_uint water_needs);

protected:
    p_uint m_water_needs;
};

#endif // !WATER_H