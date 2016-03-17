#pragma once
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"
#include "../GameElements/Bouton.h"
#include "LayerEvent.h"

class Layer : public GraphicsObject
{
public:
	Layer() { isInitialized = false; };
	~Layer() {};
	Layer(int, int) { isInitialized = false; };
	Layer(int, int, int, int) { isInitialized = false; };

	void setTranslate(const Vector3D& translate) { this->translate.set(translate); };
	void virtual render(Graphics * g, const Vector3D translation) = 0;
	// Détection des collisions 
	LayerNs::LayerEvent virtual handleEvent(Input& input) = 0;
protected:
	bool isInitialized;
	Vector3D translate;
};