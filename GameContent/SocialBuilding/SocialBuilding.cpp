#include "SocialBuilding.h"

SocialBuilding::SocialBuilding() :
    m_score(0),
    m_radius(0)
{
}

SocialBuilding::SocialBuilding(p_uint score, float radius) :
    m_score(score),
    m_radius(radius)
{
}

SocialBuilding::SocialBuilding(std::string name, myRectangle rect, int x, int y, p_uint score, float radius) :
    QTEntityBuild(rect),
    m_score(score),
    m_radius(radius)
{
    setName(name);
}

// ----- GETTER ----- //
p_uint SocialBuilding::getScore() const
{
    return m_score;
}