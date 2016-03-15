#ifndef HOUSE_H
#define HOUSE_H

#include "../Housing.h"

class House : public Housing
{
public:
    House();
    House(p_uint water_needs, p_uint energy_needs);

private:

};

#endif // !HOUSE_H