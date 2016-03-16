#ifndef MANUFACTORY_H
#define MANUFACTORY_H

#include "../Factory.h"
#include "../Resources/PowerPlant.h"
#include "../Resources/WaterTower.h"
#include "../PollutionArea.h"

#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"

#include <string>

class Manufactory final : public Factory
{
public:
    Manufactory(Image& image, myRectangle& rect);
    Manufactory(std::string name, Image& image, myRectangle& rect);

private:
    PowerPlant* m_power_plant;
    WaterTower* m_water_tower;
    PollutionArea* m_air_pollution_area;
    PollutionArea* m_water_pollution_area;
};

#endif // !MANUFACTORY_H