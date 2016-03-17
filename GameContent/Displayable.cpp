#include "Displayable.h"

Displayable::Displayable()
{
    m_image = NULL;
    name = "";
}

Displayable::Displayable(std::string name, myRectangle rect, Image* image, int x, int y) :
    QTEntity(rect),
    name(name)
{
    m_image = image;
    m_image->setPos(Vector3D(x, y));
}

void Displayable::render()
{
    m_image->draw();
}

// ----- GETTER ----- //
std::string Displayable::getName() const
{
    return name;
}

// ----- SETTER ----- //
void Displayable::setPos(int x, int y)
{
    m_image->setPos(Vector3D(x, y));
    form->setCenter(Vector3D(x, y));
}

void Displayable::translate(int x, int y)
{
    m_image->translate(Vector3D(x, y));
    form->translate(Vector3D(x, y));
}