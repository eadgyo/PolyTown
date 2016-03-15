#ifndef HOUSE_H
#define HOUSE_H

#include "../Housing.h"

#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"

#include <string>

class House final : public Housing
{
public:
    House(Image & image, myRectangle & rect);
    House(Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs);
    House(std::string name, Image & image, myRectangle & rect);
    House(std::string name, Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs);

private:

};

#endif // !HOUSE_H