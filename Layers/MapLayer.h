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
	
	void renderElements(Graphics* g, std::vector<QTEntity*> entities);
	void renderSelected(Graphics* g, std::vector<QTEntity*> entities);
	void renderTempEntity(Graphics* h, std::vector<QTEntity*> entities);
	void renderConnexitude(Graphics* g, std::vector<QTEntity*> entities);
	void renderLinkRoad(Graphics * g, std::vector<QTEntity*> entities);

	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

	void reset();
	bool create();
	bool isMakable();
	void updateEntity(const Vector3D& mousePos);
	void updateRoad(const Vector3D& mousePos);

	void setCreatorManager(CreatorManager* cm) { this->cm = cm; };

	void scale(float scale, const Vector3D& center);
	void setPos(const Vector3D& pos);
	void translate(const Vector3D& trans);
	Vector3D transformMouse(const Vector3D& mousePos);

	void handleMouseTranslation(const Vector3D& mousePos);

protected:
	CreatorManager* cm;
	int deltaSide;
	bool isUpdating = true;
	Vector3D lastMousePos;

	const float MAX_SCALE_SCREEN = 2.0f;
};

