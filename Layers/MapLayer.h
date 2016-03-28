#pragma once
#include "Layer.h"
#include "MapRecLayer.h"
#include "../GameContent/StructFactory.h"
#include "../Game/CreatorManager.h"

class MapLayer : public Layer
{
public:
	MapLayer(Graphics* g);
	~MapLayer();
	void initialize(int x, int y, int width, int height, int deltaSide, GameStruct* gs);
	void update(float dt);
	void render(Graphics* g);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

	bool create();
	bool isMakable();
	void updateEntity(const Vector3D& mousePos);
	void updateRoad(const Vector3D& mousePos);

	void setCreatorManager(CreatorManager* cm) { this->cm = cm; };

	void setPos(const Vector3D& pos);
	void translate(const Vector3D& trans);

protected:
	CreatorManager* cm;
	int deltaSide;

	

};

