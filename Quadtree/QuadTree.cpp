#include "QuadTree.h"



QuadTree::QuadTree(int level, const sRectangle & rec)
{
	this->level = level;
	this->rect.set(rec);

	nodes = NULL;
}

QuadTree::~QuadTree()
{
	delete[] nodes;
}

void QuadTree::setRect(const sRectangle & rec)
{
	rect.set(rec);
}

void QuadTree::split()
{
	if (nodes == NULL)
	{
		int subWidth = (int)(rect.getWidth() / 2);
		int subHeight = (int)(rect.getHeight() / 2);
		int x = (int)rect.getX();
		int y = (int)rect.getY();
		std::fill(nodes, nodes + 1, QuadTree(level + 1, sRectangle(x + subWidth, y, subWidth, subHeight)));
		std::fill(nodes + 1, nodes + 2, QuadTree(level + 1, sRectangle(x, y, subWidth, subHeight)));
		std::fill(nodes + 2, nodes + 3, QuadTree(level + 1, sRectangle(x, y + subHeight, subWidth, subHeight)));
		std::fill(nodes + 3, nodes + 4, QuadTree(level + 1, sRectangle(x + subWidth, y + subHeight, subWidth, subHeight)));
	}
}

void QuadTree::clear()
{
	entities.clear();
	if (nodes != NULL)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			nodes[i].clear();
		}
		nodes = NULL;
	}
}

int QuadTree::getIndex(const sRectangle & rec)
{
	int index = -1;
	Vector3D l_rectCenter((float)(rect.getCenterX()), (float)(rect.getCenterY()));
	if (rec.getX(2) < l_rectCenter.x())
	{
		if (rec.getY(2) < l_rectCenter.y())
			index = 1;
		else if (rec.getY() > l_rectCenter.y())
			index = 2;
	}
	else if (rec.getX() > l_rectCenter.x())
	{
		if (rec.getY(2) < l_rectCenter.y())
			index = 0;
		else if (rec.getY() > l_rectCenter.y())
			index = 3;
	}
	return index;
}

int QuadTree::getIndex(const QTEntity *entity)
{
	return getIndex(entity->getBounds());
}

void QuadTree::insert(QTEntity * entity, const sRectangle& recEntity)
{
	if (nodes != NULL)
	{
		int index = getIndex(recEntity);
		if (index != -1)//si le rectangle rentre dans l'une des quatres cases
		{
			nodes[index].insert(entity);
			return;
		}
	}

	if (entities.size() + 1 > MAX_OBJECTS && level + 1 < MAX_LEVELS)
	{
		if (nodes == NULL)
		{
			split();

			//change here
			//restructuration de la liste
			unsigned i = 0;
			while (i < entities.size())
			{
				int index = getIndex(entities[i]->getBounds());
				if (index != -1)
				{
					QTEntity *q = entities[i];
					entities.erase(entities.begin() + i);
					nodes[index].insert(q);
				}
				else
					i++;
			}
		}
		int index = getIndex(recEntity);
		if (index != -1)
			nodes[index].insert(entity, recEntity);
		else
			entities.push_back(entity);
	}
	else
		entities.push_back(entity);
}

void QuadTree::insert(QTEntity * entity)
{
	insert(entity, entity->getBounds());
}

void QuadTree::inserts(std::vector<QTEntity*>& entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		insert(entities[i]);
	}
}

void QuadTree::retrieve(const QTEntity * entity, std::vector<QTEntity*>& entities)
{
	retrieve(entity->getBounds(), entities);
}

void QuadTree::retrieve(const sRectangle& sRectangle, std::vector<QTEntity*>& entities)
{
	int index = getIndex(sRectangle);
	if (index != -1 && nodes != NULL)
		nodes[index].retrieve(sRectangle, entities);
	else if(nodes != NULL)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			nodes[index].addEntities(entities);
		}
	}
	entities.insert(entities.end(), this->entities.begin(), this->entities.end());
}

void QuadTree::addEntities(std::vector<QTEntity*>& entities)
{
	if (nodes != NULL)
	{
		for (unsigned i = 0; i < 4; i++)
			nodes[i].addEntities(entities);
	}
	entities.insert(entities.end(), this->entities.begin(), this->entities.end());
}

void QuadTree::erase(QTEntity* qtEntity, const sRectangle& recEntity)
{
	int index = getIndex(qtEntity->getBounds());

	if (index != -1 && nodes != NULL)
		nodes[index].erase(qtEntity, recEntity);
	else
	{	
		unsigned i = 0;
		while (qtEntity != entities[i] && i < entities.size())
			i++;
		
		if (i == entities.size())
			std::cout << "Entity not found in Quadtree";
		else
		{
			entities.erase(entities.begin() + i);
		}
	}
}

void QuadTree::erase(QTEntity* qtEntity)
{
	erase(qtEntity, qtEntity->getBounds());
}