#pragma once
#include "../Graphics/Graphics.h"
#include "../HUD/HudEvent.h"
#include "../HUD/Input.h"
#include "../Graphics/GraphicsObject.h"
#include "../GameElements/Bouton.h"
#include "LayerEvent.h"
#include "../Game/GameStruct.h"
class Layer : public GraphicsObject
{
public:
	Layer(Graphics* graphics) : graphics(graphics) { isInitialized = false;  };
	~Layer() {};
	Layer(int, int) { isInitialized = false; };
	Layer(int, int, int, int) { isInitialized = false; };
	
	void initialize(int width, int height, GameStruct* gs) { initialize(0, 0, width, height, gs); };
	virtual bool isColliding(const Vector3D& mousePos);
	sRectangle getRectangle() { return rec; };
	void setTranslate(const Vector3D& translate) { this->rec.setLeft(translate); };
	virtual void render(Graphics * g, const Vector3D translation) { graphics->translate(translation);  render(graphics); graphics->translate(-translation); };
	
	virtual void initialize(int x, int y, int width, int height, GameStruct* gs);
	virtual void update(float dt) {};
	virtual void render(Graphics* g) = 0;
	LayerNs::LayerEvent virtual handleEvent(Input& input, const Vector3D& translation) = 0;


	inline void setGameStruct(GameStruct* gs) { this->gs = gs; };

protected:
	bool isInitialized;
	Graphics* graphics;
	sRectangle rec;
	GameStruct* gs;

};