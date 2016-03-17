#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "../Constant.h"
#include "../Quadtree/QTEntity.h"
#include "../Graphics/Image.h"
#include "../Maths/myRectangle.h"
#include "../Maths/Vector3D.h"
#include <string>

class Displayable : public virtual QTEntity
{
public:
    Displayable();
    Displayable(std::string name, Image* image, int x, int y);

    void render();

    // ----- GETTER ----- //
    std::string getName() const;

    // ----- SETTER ----- //
    void setPos(int x, int y);
    void translate(int x, int y);

protected:
    Image* m_image;
    std::string name;
};

#endif // ! DISPLAYABLE_H