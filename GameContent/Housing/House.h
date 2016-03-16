#ifndef HOUSE_H
#define HOUSE_H

#include "../Housing.h"

class House final : public virtual Housing
{
public:
    House(Graphics* graphics);
    House(Graphics* graphics, int x, int y);
    House(Graphics* graphics, int x, int y, p_uint water_needs, p_uint energy_needs);

private:

};

#endif // !HOUSE_H