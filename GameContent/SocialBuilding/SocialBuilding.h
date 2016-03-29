#ifndef SOCIAL_BUILDING_H
#define SOCIAL_BUILDING_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../Quadtree/QTEntityBuild.h"

class SocialBuilding : public virtual QTEntityBuild
{
public:
    SocialBuilding();
    SocialBuilding(p_uint score, float radius);
    SocialBuilding(std::string name, myRectangle rect, int x, int y, p_uint score, float radius);

    // ---- GETTER ----- //
    virtual p_uint getScore() const;

protected:
    p_uint m_score;
    float m_radius;
};

#endif !SOCIAL_BUILDING_H