#ifndef HOUSE_H
#define HOUSE_H

#include "Housing.h"

class House final : public Housing
{
public:
    House(int x, int y);
    House(int x, int y, p_uint water_needs, p_uint energy_needs);

private:

};

#endif // !HOUSE_H