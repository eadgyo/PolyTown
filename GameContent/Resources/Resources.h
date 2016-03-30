#ifndef RESOURCES_H
#define RESOURCES_H

#include "../../Constant.h"
#include "../GameContentConstant.h"

#include "../../Quadtree/QTEntityBuild.h"

#include <vector>

class Resources : public virtual QTEntityBuild
{
public:
    sRectangle getBoundsCover() const;

    // ----- GETTER ----- //
    float getRadius() const;
	unsigned sizeConnectedCons();
	QTEntity* getConnectedCons(unsigned i);

    // ----- SETTER ----- //
	bool virtual addConsumer(QTEntity* entity) = 0;
    bool addConsumer(QTEntity* entity, p_uint consumption);
	QTEntity* eraseCons(unsigned i);
	bool eraseCons(QTEntity* qtEntity);

protected:
    Resources(p_uint production, float radius);

    std::vector<QTEntity*> m_connected; // Connected
    p_uint m_production;
    p_uint m_consumption;
    float radius;
};

#endif // !RESOURCES_H
