#pragma once

#include <vector>
#include "../Quadtree/QTEntity.h"
#include "../Maths/myRectangle.h"

#define minSize 10

class Road : public QTEntity
{
public:
	Road();
	Road(const Vector3D& center, const Vector3D& length);
	Road(const Vector3D& center, const Vector3D& length, float theta);
	~Road() {};
	static Road create2points(const Vector3D& A, const Vector3D& B, float width);
	static Road createLeft(const Vector3D& left, const Vector3D& length);

	// Getter
	myRectangle getBigRectangle(float width, float height) const;
	Vector3D getStart() const;
	Vector3D getEnd() const;
	Vector3D get(unsigned n) const;
	Vector3D getDirectorVec() const;
	Vector3D getLeftCenter() const;
	Vector3D getRightCenter() const;
	Vector3D getCenter() const;
	float getAngle2D() const;
	float getWidth() const;
	float getHeight() const;
	Vector3D getLength() const;
	void getLength(float& width, float& height) const;
	myRectangle getStartColl(float width, float height) const;
	myRectangle getEndColl(float width, float height) const;
	myRectangle getRect() const;
	std::vector<myRectangle> getMidColl(float defHeight) const;
	std::set<QTEntity*> getEntConnected() const;
	std::vector<QTEntity*> getEntConnectedVec() const;
	bool isColliding(Form& form);
	bool isColliding(Form& form, Vector3D& push, float& t);
	inline unsigned sizeEnt() const { return entConnected.size(); };
	QTEntity* getEnt(unsigned n) const;
	inline Road* getLast() { if (connected.size() > 0) return connected[0]; else return NULL; };
	inline Road* getNext() { if (connected.size() > 1) return connected[1]; else return NULL; };
	inline int getConnexitude() const { return connex; };

	inline unsigned sizeConnected() const { return connected.size(); };
	inline Road* getConnected(unsigned n) const { return connected[n]; };

	inline bool addRoad(Road* road) { connected.push_back(road); };
	inline bool removeRoad(unsigned i) { connected.erase(connected.begin() + i); };
	bool removeRoad(Road* road);

	// Setter
	void setStart(const Vector3D& center, float minHeight);
	void setEnd(const Vector3D& center, float minHeight);
	void setStartMove(const Vector3D& center);
	void setEndMove(const Vector3D& center);
	void erase(QTEntity* entity);
	void erase(unsigned i);
	void addEntity(QTEntity* entity);
	void addAllEntities(std::vector<QTEntity*> entities);
	inline void setConnexitude(int connex) { this->connex = connex; };

protected:
	int connex;
	std::set<QTEntity*> entConnected;
	std::vector<Road*> connected;
};