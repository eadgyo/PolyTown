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


	inline void setLast(Road* next) { assert(false); }; // Mauvaise utilisation
	inline void setNext(Road* last) { assert(false); }; // Mauvaise utilisation

	inline void addConnectedRoad(Road* road)
	{
		connectedRoads.push_back(road);
	}
	inline void removeConnectedRoad(Road* road)
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