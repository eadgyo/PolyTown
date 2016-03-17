#ifndef RESOURCES_H
#define RESOURCES_H

#include "../Constant.h"
#include "../Displayable.h"

#include <vector>

class Resources : public virtual Displayable
{
public:

protected:
    Resources();


    std::vector<Displayable> m_connected; // Connected
};

#endif // !RESOURCES_H