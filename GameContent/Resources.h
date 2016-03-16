#ifndef RESOURCES_H
#define RESOURCES_H

#include "../Constant.h"
#include "Housing.h"

#include <vector>

class Resources
{
public:
    Resources();

protected:
    std::vector<Housing> m_housings;
};

#endif // !RESOURCES_H