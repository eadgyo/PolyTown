#ifndef SOCIAL_BUILDING_H
#define SOCIAL_BUILDING_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../Quadtree/QTEntity.h"

#include "../Resources/Energy.h"

class SocialBuilding : public virtual QTEntity, public virtual Energy
{
public:
    SocialBuilding(p_uint score, float ratio, float radius);
    SocialBuilding(std::string name, myRectangle rect, int frame_width, int frame_height, int frame_number, int image_cols, std::string image_name, int x, int y, p_uint score, float ratio, float radius);

    // ---- GETTER ----- //
    p_uint getScore() const;
    p_uint getEnergyNeeds() const;
    virtual bool isWorking() const;

    // ----- SETTER ----- //
    virtual void init(PowerPlant* power_plant);

protected:
    p_uint m_score;
    float m_ratio;
    float m_radius;
};

#endif // !SOCIAL_BUILDING_H