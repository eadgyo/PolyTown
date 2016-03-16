#pragma once

#include "Road.h"
class ConnectorRoad : public Road
{
	inline unsigned sizeConnected() const { return connected.size(); };
	inline Road* getConnected(unsigned n) const { return connected[n]; };

	inline bool addRoad(Road* road) { if (connected.size() < 4) connected.push_back(road); };

	inline Road* getLast() { return NULL; };
	inline Road* getNext() { return NULL; };

protected:
	std::vector<Road*> connected;
};