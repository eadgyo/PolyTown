#ifndef SOCIAL_BUILDING_H
#define SOCIAL_BUILDING_H

#include "../Constant.h"
#include "../Displayable.h"

class SocialBuilding : public virtual Displayable
{
public:
    SocialBuilding(p_uint score, float ratio, float radius);

private:
    p_uint m_score;
    float m_ratio;
    float m_radius;
};

#endif // !SOCIAL_BUILDING_H