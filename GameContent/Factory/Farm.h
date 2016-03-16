#ifndef FARM_H
#define FARM_H

#include "../Factory.h"
#include "../Resources/WaterTower.h"
#include "../PollutionArea.h"

#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"

#include <string>

class Farm final : public Factory
{
public:
    Farm(Image& image, myRectangle& rect);
    Farm(std::string name, Image& image, myRectangle& rect);

private:
    p_uint m_output_rate;
    WaterTower* m_water_tower;
    PollutionArea* m_water_pollution_area;
};

#endif // FARM_H