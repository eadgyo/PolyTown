#include "QuadTreeSpecial.h"



QuadTreeSpecial::QuadTreeSpecial(int level, const sRectangle & rec)
{
	this->level = level;
	this->rect.set(rec);
}

QuadTreeSpecial::~QuadTreeSpecial()
{
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
		nodes[i] = NULL;
	}
	nodes.clear();
}

void QuadTreeSpecial::set(int level, const sRectangle & rec)
{
	this->level = level;
	rect.set(rec);
}

void QuadTreeSpecial::setRect(const sRectangle & rec)
{
	rect.set(rec);
}

void QuadTreeSpecial::split()
{
	if (nodes.size() == 0)
	{
		int subWidth = (int)(rect.getWidth() / 2.0f);
		int subHeight = (int)(rect.getHeight() / 2.0f);
		int x = (int)rect.getLeftX();
		int y = (int)rect.getLeftY();
		nodes.push_back(new QuadTreeSpecial(level + 1, sRectangle(x + subWidth, y, subWidth, subHeight)));
		nodes.push_back(new QuadTreeSpecial(level + 1, sRectangle(x, y, subWidth, subHeight)));
		nodes.push_back(new QuadTreeSpecial(level + 1, sRectangle(x, y + subHeight, subWidth, subHeight)));
		nodes.push_back(new QuadTreeSpecial(level + 1, sRectangle(x + subWidth, y + subHeight, subWidth, subHeight)));
	}
}

void QuadTreeSpecial::clear()
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

int QuadTreeSpecial::getIndex(const sRectangle & rec)
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

int QuadTreeSpecial::getIndex(const Resources *entity)
{
	return getIndex(entity->getBoundsCover());
}

int QuadTreeSpecial::getIndex(const QTEntity * entity)
{
	return getIndex(entity->getBounds());
}

void QuadTreeSpecial::insert(Resources * entity, const sRectangle& recEntity)
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
				int index = getIndex(entities[i]->getBoundsCover());
				if (index != -1)
				{
					Resources *q = entities[i];
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

bool QuadTreeSpecial::isValid(const sRectangle& rec) const
{
	return rec.getX(0) > rect.getX(0) && rec.getX(2) < rect.getX(2)
		&& rec.getY(0) > rect.getY(0) && rec.getY(2) < rect.getY(2);
}

void QuadTreeSpecial::insert(Resources * entity)
{
	sRectangle rec = entity->getBoundsCover();
	if (isValid(rec))
	{
		insert(entity, rec);
	}
	else
	{
		std::cout << "QuadTreeSpecial -> insertion, rec ne rentre pas";
	}
}

void QuadTreeSpecial::inserts(std::vector<Resources*>& entities)
{
	for (unsigned i = 0; i < entities.size(); i++)
	{
		insert(entities[i]);
	}
}

void QuadTreeSpecial::retrieve(const QTEntity * entity, std::vector<Resources*>& entities)
{
	sRectangle rec = entity->getBounds();
	if (isValid(rec))
	{
		retrieve(rec, entities);
	}
	else
	{
		std::cout << "QuadTreeSpecial -> retrieve, rec ne rentre pas";
	}
}

void QuadTreeSpecial::retrieve(const sRectangle& sRectangle, std::vector<Resources*>& entities)
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
		if (j == entities.size())
			entities.push_back(this->entities[i]);
	}
}

void QuadTreeSpecial::addEntities(std::vector<Resources*>& entities)
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

void QuadTreeSpecial::erase(Resources* qtEntity, const sRectangle& recEntity)
{
	int index = getIndex(qtEntity->getBoundsCover());

	if (index != -1 && nodes.size() != 0)
		nodes[index]->erase(qtEntity, recEntity);
	else
	{
		unsigned i = 0;
		while (i < entities.size() && qtEntity != entities[i])
			i++;

		if (i == entities.size())
			std::cout << "Entity not found in QuadTreeSpecial";
		else
		{
			entities.erase(entities.begin() + i);
		}
	}
}

void QuadTreeSpecial::erase(Resources* qtEntity)
{
	erase(qtEntity, qtEntity->getBoundsCover());
}

void QuadTreeSpecial::draw(Graphics* g)
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