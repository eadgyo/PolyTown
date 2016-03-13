#pragma once

#include "Layer.h"
#include "../GameElements/Bouton.h"

class BottomLayer : public Layer
{
	BottomLayer();
	void initialize(float x, float y, int width, int height);
	void initialize(int width, int height) { initialize(0, 0, width, height); };
	void reset();
	void resize(int width, int height);
	void render(Graphics* g);
	void render(Graphics * g, const Vector3D translation);
	void update(float dt);
	LayerNs::LayerEvent handleEvent(Input& input);

private:
	std::vector<Bouton*> boutons;
};