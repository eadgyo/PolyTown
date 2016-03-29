#include "PoweredSocialBuilding.h"

PoweredSocialBuilding::PoweredSocialBuilding()
{
}

PoweredSocialBuilding::PoweredSocialBuilding(std::string name, myRectangle rect, int x, int y, p_uint score, float radius) :
    QTEntityBuild(rect),
    SocialBuilding(score, radius)
{
    setName(name);
}

// ----- GETTER ----- //
p_uint PoweredSocialBuilding::getEnergyNeeds() const
{
    if (isWorking()) {
        return m_energy_needs;
    } else {
        return 0;
    }
}

bool PoweredSocialBuilding::isWorking() const
{
    return (m_power_plant != NULL);
}

// ----- SETTER ----- //
void PoweredSocialBuilding::init(PowerPlant* power_plant)
{
    m_power_plant = power_plant;
}