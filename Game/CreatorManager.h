#pragma once

#include "../Quadtree/QTEntity.h"
#include "../GameContent/Road.h"
#include "../HUD/Input.h"
#include "../Layers/Layer.h"
#include "GameStruct.h"

class CreatorManager : public Layer
{
public:
	CreatorManager();
	~CreatorManager();

	void initialize(GameStruct* gameStruct);
	void setGameStruct(GameStruct* gameStruct);

	// isPossibleToMake
	bool isMakableRoad(Road* road);
	bool isMakable(QTEntity* qtEntity);

	// Remove ressources
	void removeRoad(Road* road);
	void remove(QTEntity* qtEntity);
	
	// AddRessource
	void add(QTEntity* qtEntity);
	void addRoad(Road* road);

	void render(Graphics * g, const Vector3D translation);
	LayerNs::LayerEvent virtual handleEvent(Input& input);
	
protected:
	QTEntity* lastSelected;
	Form* possibleForm;
	bool isLastMakable;
	GameStruct* gameStruct;
};

