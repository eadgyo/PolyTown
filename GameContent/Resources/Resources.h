#ifndef RESOURCES_H
#define RESOURCES_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../Quadtree/QTEntity.h"

#include <vector>

class Resources : public virtual QTEntity
{
public:

protected:
    Resources();

    std::vector<QTEntity*> m_connected; // Connected
};

#endif // !RESOURCES_H