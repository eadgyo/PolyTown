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
	static Road create2points(const Vector3D& A, const Vector3D& B, float width);
	static Road createLeft(const Vector3D& left, const Vector3D& length);

	// Getter
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
	inline Road* getLast() { return last; };
	inline Road* getNext() { return next; };
	
	// Setter
	void setStart(const Vector3D& center, float minHeight);
	void setEnd(const Vector3D& center, float minHeight);
	void setStartMove(const Vector3D& center);
	void setEndMove(const Vector3D& center);
	void erase(QTEntity* entity);
	void erase(unsigned i);
	void addEntity(QTEntity* entity);
	void addAllEntities(std::vector<QTEntity*> entities);

protected:
	std::set<QTEntity*> entConnected;
	Road* last;
	Road* next;
};