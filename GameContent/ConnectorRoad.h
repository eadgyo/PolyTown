#pragma once

#include "Road.h"
class ConnectorRoad : public Road
{
public:
	~ConnectorRoad() {};

	inline bool addRoad(Road* road) { if (connected.size() < 4) connected.push_back(road); };

	inline Road* getLast() { return NULL; };
	inline Road* getNext() { return NULL; };

protected:
	
};