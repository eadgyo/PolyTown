#pragma once
#include "Layer.h"
#include "MapRecLayer.h"

class MapLayer : public Layer
{
public:
	MapLayer(Graphics* g);
	~MapLayer();
	void initialize(int x, int y, int width, int height, int widthScreen, int heightScreen, int sizeMapX, int sizeMapY);
	void update(float dt);
	void render(Graphics* g);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

protected:
	MapRecLayer mapRecLayer;

	const float POS_X_FACTOR_REC_MAP = 0.89f;
	const float POS_Y_FACTOR_REC_MAP = 0.87f;
	const float SIZE_FACTOR_REC_MAP = 0.1f;

};

