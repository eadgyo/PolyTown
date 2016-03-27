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
	Layer(Graphics* graphics) : graphics(graphics) { isInitialized = false;  };
	~Layer() {};
	Layer(int, int) { isInitialized = false; };
	Layer(int, int, int, int) { isInitialized = false; };
	virtual void update(float dt) {} ;
	virtual void initialize(int x, int y, int width, int height);
	void initialize(int width, int height) { initialize(0, 0, width, height); };
	virtual bool isColliding(const Vector3D& mousePos);

	sRectangle getRectangle() { return rec; };
	void setTranslate(const Vector3D& translate) { this->rec.setLeft(translate); };
	void virtual render(Graphics * g, const Vector3D translation) = 0;
	// Détection des collisions 
	LayerNs::LayerEvent virtual handleEvent(Input& input) = 0;

protected:
	bool isInitialized;
	Graphics* graphics;
	sRectangle rec;
};