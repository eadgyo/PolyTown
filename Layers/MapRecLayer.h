#pragma once
#include "Layer.h"

class MapRecLayer : public Layer
{
public:
	MapRecLayer(Graphics* g);
	~MapRecLayer();

	void initialize(int x, int y, int widthScreen, int heightScreen, int sizeMapX, int sizeMapY, int width, float factorScreen);
	virtual void update(float dt);
	virtual void render(Graphics* g) ;
	LayerNs::LayerEvent virtual handleEvent(Input& input, const Vector3D& translation);

	void setPos(const Vector3D& pos);
	void setScale(float scale);
	sRectangle getRectangle() const { return zoneToDisplay; };


protected:
	sRectangle zoneToDisplay;
	sRectangle mapRec;
	float factorMap;
};
