#include "QuadTree.h"



QuadTree::QuadTree(int level, const sRectangle & rec)
{
	this->level = level;
	this->rect.set(rec);
}

QuadTree::~QuadTree()
{
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
		nodes[i] = NULL;
	}
	nodes.clear();
}

void QuadTree::set(int level, const sRectangle & rec)
{
	this->level = level;
	rect.set(rec);
}

void QuadTree::setRect(const sRectangle & rec)
{
	rect.set(rec);
}

void QuadTree::split()
{
	if (nodes.size() == 0)
	{
		int subWidth = (int)(rect.getWidth() / 2.0f);
		int subHeight = (int)(rect.getHeight() / 2.0f);
		int x = (int)rect.getLeftX();
		int y = (int)rect.getLeftY();
		nodes.push_back(new QuadTree(level + 1, sRectangle(x + subWidth, y, subWidth, subHeight)));
		nodes.push_back(new QuadTree(level + 1, sRectangle(x, y, subWidth, subHeight)));
		nodes.push_back(new QuadTree(level + 1, sRectangle(x, y + subHeight, subWidth, subHeight)));
		nodes.push_back(new QuadTree(level + 1, sRectangle(x + subWidth, y + subHeight, subWidth, subHeight)));
	}
}

void QuadTree::clear()
{
	entities.clear();
	if (nodes.size() != 0)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			nodes[i]->clear();
			delete nodes[i];
			nodes[i] = NULL;
		}
		nodes.clear();
	}
}

int QuadTree::getIndex(const sRectangle & rec)
{
	int index = -1;
	Vector3D l_rectCenter((float)(rect.getCenterX()), (float)(rect.getCenterY()));
	float x0 = rec.getX(0);
	float x2 = rec.getX(2);

	float y0 = rec.getY(0);
	float y2 = rec.getY(2);

	Vector3D left = rec.get(0);
	Vector3D right = rec.get(2);
	assert(x0 == left.x() && x2 == right.x() && y0 == left.y() && y2 == right.y());
	if (rec.getX(2) < l_rectCenter.x())
	{
		if (rec.getY(2) < l_rectCenter.y())
			index = 1;
		else if (rec.getY(0) > l_rectCenter.y())
			index = 2;
	}
	else if (rec.getX() > l_rectCenter.x())
	{
		if (rec.getY(2) < l_rectCenter.y())
			index = 0;
		else if (rec.getY(0) > l_rectCenter.y())
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
	if (nodes.size() != 0)
	{
		int index = getIndex(recEntity);
		if (index != -1)//si le rectangle rentre dans l'une des quatres cases
		{
			nodes[index]->insert(entity);
			return;
		}
	}

	if (entities.size() + 1 > MAX_OBJECTS && level + 1 < MAX_LEVELS)
	{
		if (nodes.size() == 0)
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
					nodes[index]->insert(q);
				}
				else
					i++;
			}
		}
		int index = getIndex(recEntity);
		if (index != -1)
			nodes[index]->insert(entity, recEntity);
		else
			entities.push_back(entity);
	}
	else
		entities.push_back(entity);
}

bool QuadTree::isValid(const sRectangle& rec) const
{
	return rec.getX(0) > rect.getX(0) && rec.getX(2) < rect.getX(2)
		&& rec.getY(0) > rect.getY(0) && rec.getY(2) < rect.getY(2);
}

void QuadTree::insert(QTEntity * entity)
{
	sRectangle rec = entity->getBounds();
	if (isValid(rec))
	{
		insert(entity, rec);
	}
	else
	{
		std::cout << "QuadTree -> insertion, rec ne rentre pas";
	}
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
	sRectangle rec = entity->getBounds();
	if (isValid(rec))
	{
		retrieve(rec, entities);
	}
	else
	{
		std::cout << "QuadTree -> retrieve, rec ne rentre pas";
	}
}

void QuadTree::retrieve(const sRectangle& sRectangle, std::vector<QTEntity*>& entities)
{
	int index = getIndex(sRectangle);
	if (index != -1 && nodes.size() != 0)
		nodes[index]->retrieve(sRectangle, entities);
	else if (nodes.size() != 0)
	{
		for (unsigned i = 0; i < nodes.size(); i++)
		{
			nodes[i]->addEntities(entities);
		}
	}
	for (unsigned i = 0; i < this->entities.size(); i++)
	{
		unsigned j;
		for (j = 0; j < entities.size(); j++)
		{
			if (this->entities[i] == entities[j])
				break;
		}
		if(j == entities.size())
			entities.push_back(this->entities[i]);
	}
}

void QuadTree::addEntities(std::vector<QTEntity*>& entities)
{
	if (nodes.size() != 0)
	{
		for (unsigned i = 0; i < nodes.size(); i++)
			nodes[i]->addEntities(entities);
	}
	for (unsigned i = 0; i < this->entities.size(); i++)
	{
		unsigned j;
		for (j = 0; j < entities.size(); j++)
		{
			if (this->entities[i] == entities[j])
				break;
		}
		if (j == entities.size())
			entities.push_back(this->entities[i]);
	}
}

void QuadTree::erase(QTEntity* qtEntity, const sRectangle& recEntity)
{
	int index = getIndex(qtEntity->getBounds());

	if (index != -1 && nodes.size() != 0)
		nodes[index]->erase(qtEntity, recEntity);
	else
	{	
		unsigned i = 0;
		while (i < entities.size() && qtEntity != entities[i])
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

void QuadTree::draw(Graphics* g)
{
	g->setColor(myColor::RED());
	g->drawForm(rect);

	if (nodes.size() != 0)
	{
		nodes[0]->draw(g);
		nodes[1]->draw(g);
		nodes[2]->draw(g);
		nodes[3]->draw(g);
	}
}