#pragma once
#include "Road.h"


class Connector : public Road
{
public:
	Connector()
	{
		isConnector = true;
	};
	Connector(const Vector3D& center, const Vector3D& length) : Road(center, length)
	{
		isConnector = true;
	};
	Connector(const Vector3D& center, const Vector3D& length, float theta) : Road(center, length, theta)
	{
		isConnector = true;
	};
	Connector(const Vector3D& center, float width, float height, float theta) : Road(center, width, height, theta)
	{
		isConnector = true;
	};
	~Connector()
	{

	};

	inline Road* getNext() { assert(false); return NULL; };
	inline Road* getLast() { assert(false); return NULL; };
	inline void setLast(Road* last) { assert(false); }; // Mauvaise utilisation
	inline void setNext(Road* next) { assert(false); }; // Mauvaise utilisation

	inline void addConnectedRoad(Road* road)
	{
		connectedRoads.push_back(road);
	}
	inline unsigned sizeConnectedRoad()
	{
		return connectedRoads.size();
	}
	inline Road* getConnectedRoad(unsigned i)
	{
		return connectedRoads[i];
	}

	inline void removeConnectedRoad(unsigned i)
	{
		connectedRoads.erase(connectedRoads.begin() + i);
	}
	void removeConnectedRoad(Road* road)
	{
		unsigned i = 0;
		while (i < connectedRoads.size() && road != connectedRoads[i])
		{
			i++;
		}
		if (i < connectedRoads.size())
		{
			connectedRoads.erase(connectedRoads.begin() + i);
		}
	}

private:
	std::vector<Road*> connectedRoads;
};