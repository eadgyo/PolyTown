#include "SocialBuilding.h"

SocialBuilding::SocialBuilding(p_uint score, float ratio, float radius) :
    m_score(score),
    m_ratio(ratio),
    m_radius(radius)
{
}

SocialBuilding::SocialBuilding(std::string name, myRectangle rect, int frame_width, int frame_height, int frame_number, int image_cols, std::string image_name, Graphics* graphics, int x, int y, p_uint score, float ratio, float radius) :
    QTEntity(rect),
    Displayable(name, new Image(graphics, (float) frame_width, (float) frame_height, frame_number, image_cols, image_name), x, y),
    m_score(score),
    m_ratio(ratio),
    m_radius(radius)
{
}