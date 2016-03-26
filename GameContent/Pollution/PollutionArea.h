#ifndef POLLUTION_AREA_H
#define POLLUTION_AREA_H

#include "../Constant.h"
#include "../GameContentConstant.h"

#include "../Quadtree/QTEntity.h"

class PollutionArea : public virtual QTEntity
{
public:
    PollutionArea(unsigned int pollution, unsigned int decrease_rate);

    // ----- GETTER ----- //
    p_uint getIntensity() const;
    p_uint getIntensity(unsigned int d) const;
    unsigned int getRadius() const;

    // ----- SETTER ----- //
    void increasePollution(unsigned int n);
    void decreasePollution();

protected:
    p_uint m_quantity;
    p_uint m_pollution;
    p_uint m_decrease_rate;
};
#endif // !POLLUTION_AREA_H