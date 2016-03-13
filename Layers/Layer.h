#pragma once
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"

class Layer : public GraphicsObject
{
public:
	Layer() { isInitialized = false; };
	~Layer() {};
	Layer(int, int) { isInitialized = false; };

	// D�tection des collisions 
	bool virtual handleEvent(Input& input) = 0;
protected:
	bool isInitialized;
};

