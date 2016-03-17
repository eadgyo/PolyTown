#pragma once

#include "../Quadtree/QTEntity.h"
#include "../HUD/Input.h"
#include "../Layers/Layer.h"
#include "GameStruct.h"
#include "../GameContent/Road.h"

class CreatorManager : public Layer
{
public:
	CreatorManager();
	~CreatorManager();

	void initialize(GameStruct* gameStruct);
	void setGameStruct(GameStruct* gameStruct);

	// isPossibleToMake
	bool isMakableRoad(Road* road, std::vector<Road*> roadsGood, std::vector<int> side);
	bool isMakable(QTEntity* qtEntity, float minDif, std::vector<QTEntity*> entitiesNear, std::vector<Vector3D> pushes, std::vector<float> ts);

	// Remove ressources
	void removeRoad(Road* road);
	void remove(QTEntity* qtEntity);
	
	// AddRessource
	void add(QTEntity* qtEntity);
	void addRoad(Road* road);

	void render(Graphics * g, const Vector3D translation);
	LayerNs::LayerEvent virtual handleEvent(Input& input);
	
	bool stillConnected(Road* start, Road* end);

protected:
	QTEntity* lastSelected;
	Form* possibleForm;
	bool isLastMakable;
	GameStruct* gameStruct;
};

