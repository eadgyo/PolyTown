#pragma once

class Road;
#include <vector>
#include "../Quadtree/QTEntity.h"
#include "../Maths/myRectangle.h"
#include "../Maths/Vector3D.h"

#define minSize 10

class Road : public QTEntity
{
public:
	Road();
	Road(const Vector3D& center, const Vector3D& length);
	Road(const Vector3D& center, const Vector3D& length, float theta);
	Road(const Vector3D& center, float width, float height, float theta);
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
	inline unsigned sizeEnt() const { return entConnected.size(); };
	QTEntity* getEnt(unsigned n) const;
	inline Road* getLast() { if (connected.size() > 0) return connected[0]; else return NULL; };
	inline Road* getNext() { if (connected.size() > 1) return connected[1]; else return NULL; };
	inline int getConnexitude() const { return connex; };



	// Setter
	void setStart(const Vector3D& center, float minHeight);
	void setStart(const Vector3D& start);
	void setEnd(const Vector3D& center, float minHeight);
	void setEnd(const Vector3D& center);
	void setStartMove(const Vector3D& center);
	void setEndMove(const Vector3D& center);
	void erase(QTEntity* entity);
	void erase(unsigned i);
	void addEntity(QTEntity* entity);
	void addAllEntities(std::vector<QTEntity*> entities);
	inline void setConnexitude(int connex) { this->connex = connex; };

	Road* next = NULL;
	Road* prec = NULL;
	bool isConnector = false;

protected:
	int connex;
	std::set<QTEntity*> entConnected;

	const float MIN_HEIGHT = 10.0f;
	
};