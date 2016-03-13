#pragma once
#include "Interface.h"
#include "Bouton.h"
#include "../HUD/Input.h"

class NewGame :
	public Interface
{
public:
	NewGame();
	~NewGame();
	void initialize(int width, int height);


};

