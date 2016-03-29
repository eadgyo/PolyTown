#pragma once
#include "QTEntity.h"
#include "../GameContent/Road.h"

class QTEntityBuild : public QTEntity
{
public:
	QTEntityBuild() { form = NULL; name = ""; };
	QTEntityBuild(std::string name) { form = NULL; this->name = name; };
	QTEntityBuild(std::string name, const Form& form);
	QTEntityBuild(const Form& form);
	QTEntityBuild(const myRectangle& rectangle);
	QTEntityBuild(const Circle& circle);
	QTEntityBuild(const Vector3D& center, float width, float height);
	QTEntityBuild(const Vector3D& center, float width, float height, float theta);
	QTEntityBuild(const Vector3D& center, float radius);
	~QTEntityBuild() {};

	inline std::string getName() const { return name; };

	void addRoad(Road* road);
	Road* removeRoad(unsigned i);
	bool removeRoad(Road* road);
	inline void setName(std::string name) { this->name = name; };

	unsigned sizeConnected() const;
	Road* getConnected(unsigned n) const;
	int getMinConnex();

private:
	std::string name;
	std::vector<Road*> connected;
};

