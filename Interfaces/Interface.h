#pragma once

class Interface;
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"

class Interface : public GraphicsObject
{
public:
	Interface() { isInitialized = false; };
	Interface(int, int) { isInitialized = false; };

	// Détection des collisions 
	HudEvent virtual handleEvent(Input& input) = 0;
};