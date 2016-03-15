#ifndef BUILDING_H
#define BUILDING_H

#include "../Housing.h"

#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"

#include <string>

class Building final : public Housing
{
public:
    Building(Image & image, myRectangle & rect);
    Building(Image & image, myRectangle & rect, p_uint floor);
    Building(Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs);
    Building(Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs, p_uint floor);
    Building(std::string name, Image & image, myRectangle & rect);
    Building(std::string name, Image & image, myRectangle & rect, p_uint floor);
    Building(std::string name, Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs);
    Building(std::string name, Image & image, myRectangle & rect, p_uint water_needs, p_uint energy_needs, p_uint floor);

    // ----- GETTER ----- //
    p_uint getFloors() const;

    // ----- SETTER ----- //
    p_uint addFloors(p_uint n);

private:
    p_uint m_floor;
    p_uint m_max_floor;
    p_uint m_max_inhabitants_per_floor;
};

#endif // !BUILDING_H