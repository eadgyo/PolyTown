#pragma once

#include "Layer.h"
#include "../GameElements/BoutonImage.h"
#include "../GameElements/BoutonText.h"

class LeftLayer : public Layer
{
public:
	LeftLayer(Graphics* g);
	void initialize(float x, float y, int width, int height);
	void initialize(int width, int height) { initialize(0, 0, width, height); };
	void reset();
	void resize(int width, int height);
	void render(Graphics* g);
	void render(Graphics * g, const Vector3D translation);
	void update(float dt);
	LayerNs::LayerEvent handleEvent(Input& input);

	inline int getState() { return state; };
	inline int getStateInt() { return stateIn; };
private:
	std::vector<Bouton*> boutons;
	int state;
	int stateIn;
};