#pragma once
#include "Road.h"


class Connector : public Road
{
public:
	Connector()
	{
		isConnector = true;
	};
	Connector(const Connector& connector) : Road(connector)
	{
		for (unsigned i = 0; i < connector.sizeConnectedRoad(); i++)
		{
			connectedRoads.push_back(connector.getConnectedRoad(i));
		}
	}
	Connector(const Vector3D& center, float width, float height) : Road(center, width, height)
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

	inline Road* getNext() const { assert(false); return NULL; };
	inline Road* getLast() const { assert(false); return NULL; };
	inline void setLast(Road* last) { assert(false); }; // Mauvaise utilisation
	inline void setNext(Road* next) { assert(false); }; // Mauvaise utilisation

	inline void addConnectedRoad(Road* road)
	{
		connectedRoads.push_back(road);
	};
	inline unsigned sizeConnectedRoad() const
	{
		return connectedRoads.size();
	};
	inline Road* getConnectedRoad(unsigned i) const
	{
		return connectedRoads[i];
	};

	inline void removeConnectedRoad(unsigned i)
	{
		connectedRoads.erase(connectedRoads.begin() + i);
	};
	virtual bool removeConnectedRoad(Road* road)
	{
		unsigned i = 0;
		while (i < connectedRoads.size() && road != connectedRoads[i])
		{
			i++;
		}
		if (i < connectedRoads.size())
		{
			connectedRoads.erase(connectedRoads.begin() + i);
			return true;
		}
		std::cout << "Road not found in connector";
		return false;
	};
	std::vector<Road*> copyConnectedRoads()
	{
		std::vector<Road*> copy;
		copy.insert(copy.end(), connectedRoads.begin(), connectedRoads.end());
		return copy;
	};

	Vector3D getNearestSideP(const Vector3D& p, float& min)
	{
		float l_tmp;
		Vector3D nearest;

		Vector3D r0 = getStart();
		Vector3D r1 = getEnd();
		Vector3D r2 = getLeftCenter();
		Vector3D r3 = getRightCenter();

		nearest.set(r0);
		min = (p - r0).getSqMagnitude();
		
		l_tmp = (p - r1).getSqMagnitude();
		if (l_tmp < min)
			nearest.set(r1);

		l_tmp = (p - r2).getSqMagnitude();
		if (l_tmp < min)
			nearest.set(r2);

		l_tmp = (p - r3).getSqMagnitude();
		if (l_tmp < min)
			nearest.set(r3);

		min = sqrt(min);

		return nearest;
	};


private:
	std::vector<Road*> connectedRoads;
};