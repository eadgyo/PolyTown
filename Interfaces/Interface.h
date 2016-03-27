#pragma once

class Interface;
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"
#include "../Game/GameStruct.h"

class Interface : public GraphicsObject
{
public:
	Interface(Graphics* g) : graphics(g) { isInitialized = false; };
	Interface(Graphics* g, int, int) : graphics(g) { isInitialized = false; };

	// Détection des collisions
	virtual void initialize(int width, int height) = 0;
	HudNs::HudEvent virtual update(float dt) = 0;
	HudNs::HudEvent virtual handleEvent(Input& input) = 0;
	Graphics *graphics;
};