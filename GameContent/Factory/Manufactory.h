#ifndef MANUFACTORY_H
#define MANUFACTORY_H

#include "Factory.h"

#include "../Resources/Energy.h"
#include "../Resources/Water.h"

class Manufactory final : public virtual Factory, public virtual Energy, public virtual Water
{
public:
    Manufactory(int x, int y);

private:

};

#endif // !MANUFACTORY_H