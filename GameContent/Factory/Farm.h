#ifndef FARM_H
#define FARM_H

#include "Factory.h"

#include "../Resources/Water.h"

class Farm final : public virtual Factory, public virtual Water
{
public:
    Farm(int x, int y);

    // ----- GETTER ----- //
    bool isWorking() const;

private:
    p_uint m_output_rate;
};

#endif // FARM_H