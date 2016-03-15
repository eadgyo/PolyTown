#pragma once

#include "../Maths/sRectangle.h"
#include "QTEntity.h"

class QuadTree
{
public:
	QuadTree(int level, const sRectangle& rec);
	~QuadTree();

	void setRect(const sRectangle& rec);
	void split();
	void clear();
	int getIndex(const sRectangle& rec);
	int getIndex(const QTEntity* entity);
	void insert(QTEntity *entity);
	void insert(QTEntity * entity, const sRectangle& recEntity);
	void inserts(std::vector<QTEntity*>& entities);
	void retrieve(const QTEntity *entity, std::vector<QTEntity*>& entities);
	void retrieve(const sRectangle& sRectangle, std::vector<QTEntity*>& entities);
	void addEntities(std::vector<QTEntity*>& entities);
	void erase(QTEntity*);
	void erase(QTEntity* qtEntity, const sRectangle& sRectangle);

private:
	static const int MAX_OBJECTS = 5;
	static const int MAX_LEVELS = 50;

	int level;
	std::vector<QTEntity*> entities;
	sRectangle rect;
	QuadTree* nodes;
};

