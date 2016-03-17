#ifndef RESOURCES_H
#define RESOURCES_H

#include "../Constant.h"
#include "Displayable.h"

#include <vector>

class Resources
{
public:
    Resources();

protected:
    std::vector<Displayable> m_connected;
};

#endif // !RESOURCES_H