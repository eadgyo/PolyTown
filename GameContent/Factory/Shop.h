#ifndef SHOP_H
#define SHOP_H

#include "../Factory.h"
#include "../Resources/PowerPlant.h"

#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"

#include <string>

class Shop final : Factory
{
public:
    Shop(Image& image, myRectangle& rect);
    Shop(std::string name, Image& image, myRectangle& rect);

private:
    PowerPlant* m_power_plant;
};

#endif // !SHOP_H