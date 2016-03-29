#pragma once
#pragma once

#include "../Maths/sRectangle.h"
#include "../GameContent/Resources/Resources.h"
#include "../Graphics/Graphics.h"

class QuadTreeSpecial
{
public:
	QuadTreeSpecial() { level = DEFAULT_LEVEL_NUMBER; };
	QuadTreeSpecial(int level, const sRectangle& rec);
	~QuadTreeSpecial();

	void set(int level, const sRectangle& rec);
	void setRect(const sRectangle& rec);
	void split();
	void clear();
	int getIndex(const sRectangle& rec);
	int getIndex(const Resources* entity);
	int getIndex(const QTEntity* entity);
	void insert(Resources *entity);
	void insert(Resources *entity, const sRectangle& recEntity);
	void inserts(std::vector<Resources*>& entities);
	void retrieve(const QTEntity *entity, std::vector<Resources*>& entities);
	void retrieve(const sRectangle& sRectangle, std::vector<Resources*>& entities);
	void addEntities(std::vector<Resources*>& entities);
	void erase(Resources*);
	void erase(Resources* qtEntity, const sRectangle& sRectangle);
	void draw(Graphics* g);
	bool isValid(const sRectangle& rec) const;

private:
	static const int MAX_OBJECTS = 5;
	static const int MAX_LEVELS = 50;
	const static int DEFAULT_LEVEL_NUMBER = 0;

	int level;
	std::vector<Resources*> entities;
	sRectangle rect;
	std::vector<QuadTreeSpecial*> nodes;

};

