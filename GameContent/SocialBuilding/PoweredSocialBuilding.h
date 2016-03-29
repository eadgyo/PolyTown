#ifndef POWERED_SOCIAL_BUILDING_H
#define POWERED_SOCIAL_BUILDING_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "SocialBuilding.h"

#include "../Resources/Energy.h"

class PoweredSocialBuilding : public virtual SocialBuilding, public virtual Energy
{
public:
    PoweredSocialBuilding();
    PoweredSocialBuilding(std::string name, myRectangle rect, int x, int y, p_uint score, float radius);

    // ---- GETTER ----- //
    p_uint getEnergyNeeds() const;
    virtual bool isWorking() const;

    // ----- SETTER ----- //
    virtual void init(PowerPlant* power_plant);

protected:
};

#endif // !SOCIAL_BUILDING_H