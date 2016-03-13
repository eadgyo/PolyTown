#pragma once
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"
#include "LayerEvent.h"

class Layer : public GraphicsObject
{
public:
	Layer() { isInitialized = false; };
	~Layer() {};
	Layer(int, int) { isInitialized = false; };

	// Détection des collisions 
	LayerNs::LayerEvent virtual handleEvent(Input& input) = 0;
protected:
	bool isInitialized;
};

