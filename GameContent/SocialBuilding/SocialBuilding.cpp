#include "SocialBuilding.h"

SocialBuilding::SocialBuilding(p_uint score, float ratio, float radius) :
    m_score(score),
    m_ratio(ratio),
    m_radius(radius)
{
}

SocialBuilding::SocialBuilding(std::string name, myRectangle rect, int frame_width, int frame_height, int frame_number, int image_cols, std::string image_name, int x, int y, p_uint score, float ratio, float radius) :
    QTEntity(rect),
    m_score(score),
    m_ratio(ratio),
    m_radius(radius)
{
    setName(name);
}

// ----- GETTER ----- //
p_uint SocialBuilding::getScore() const
{
    return m_score;
}

p_uint SocialBuilding::getEnergyNeeds() const
{
    if (isWorking()) {
        return m_energy_needs;
    }
}

bool SocialBuilding::isWorking() const
{
    return (m_power_plant != NULL);
}

// ----- SETTER ----- //
void SocialBuilding::init(PowerPlant* power_plant)
{
    m_power_plant = power_plant;
}