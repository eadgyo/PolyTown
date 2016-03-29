#ifndef RESOURCES_H
#define RESOURCES_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../Quadtree/QTEntityBuild.h"

#include <vector>

class Resources : public virtual QTEntityBuild
{
public:
	sRectangle getBoundsCover() const;
protected:
    Resources(float radius);
	

    std::vector<QTEntity*> m_connected; // Connected
	float radius;
};

#endif // !RESOURCES_H