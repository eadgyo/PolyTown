#ifndef MANUFACTORY_H
#define MANUFACTORY_H

#include "../Factory.h"

#include "../Energy.h"
#include "../Water.h"

class Manufactory final : public virtual Factory, public virtual Energy, public virtual Water
{
public:
    Manufactory(Graphics* graphics, int x, int y);

private:

};

#endif // !MANUFACTORY_H