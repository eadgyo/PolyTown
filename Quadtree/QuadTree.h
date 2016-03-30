#pragma once

#include "../Maths/sRectangle.h"
#include "QTEntity.h"
#include "../Graphics/Graphics.h"

class QuadTree
{
public:
	QuadTree() { level = DEFAULT_LEVEL_NUMBER;   };
	QuadTree(int level, const sRectangle& rec);
	~QuadTree();

	void set(int level, const sRectangle& rec);
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
	void draw(Graphics* g);
	bool isValid(const sRectangle& rec) const;
	sRectangle getRec() { return rect; };

private:
	static const int MAX_OBJECTS = 5;
	static const int MAX_LEVELS = 50;
	const static int DEFAULT_LEVEL_NUMBER = 0;

	int level;
	std::vector<QTEntity*> entities;
	sRectangle rect;
	std::vector<QuadTree*> nodes;
	
};

