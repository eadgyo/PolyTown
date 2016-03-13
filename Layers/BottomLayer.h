#pragma once

#include "Layer.h"

class BottomLayer : public Layer
{
	BottomLayer();
	void initialize(int width, int height);
	void reset();
	void resize(int width, int height);
	void render(Graphics* g);
	void update(float dt);
	LayerNs::LayerEvent handleEvent(Input& input);
};