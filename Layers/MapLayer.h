#pragma once
#include "Layer.h"
#include "MapRecLayer.h"

class MapLayer : public Layer
{
public:
	MapLayer(Graphics* g);
	~MapLayer();
	void initialize(int x, int y, int width, int height, GameStruct* gs);
	void update(float dt);
	void render(Graphics* g);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

protected:



	

};

