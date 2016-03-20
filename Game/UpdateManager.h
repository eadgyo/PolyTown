#pragma once

class UpdateManager
{
public:
	// Links automatiquement faits
	void add(QTEntity* qtEntity);
	void addRoad(QTEntity* qtEntity);
	void remove(QTEntity* qtEntity);
	void removeRoad(Road* road); // Suppresion des connectors...

	void linkRoadNext(Road* r1, Road* connector); // Road Connector
	void linkRoadPrec(Road* r1, Road* connector);
	void linkRoadNextPrec(Road* r1, Road* r2);
	void linkRoadPrecPrec(Road* r1, Road* r2);
	void linkRoadNextNext(Road* r1, Road* r2);
	void linkRoadPrecNext(Road* r1, Road* r2);
};