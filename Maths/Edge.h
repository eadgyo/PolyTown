/*
 * Edge.h
 *
 *  Created on: Feb 27, 2016
 *      Author: ronan-h
 */

#ifndef EDGE_H_
#define EDGE_H_
#include "PointType.h"
#include <iostream>

struct Edge
{
	Edge* prev;
	Edge* next;
	PointType* p0;
	PointType* p1;

	inline float getMinX()
	{
		if(p0->x() < p1->x())
			return p0->x();
		else
			return p1->x();
	};

	inline bool operator<(const Edge& e) const
	{
		std::cout << "What?";
		return false;
	};

	inline bool operator==(const Edge& e) const
	{
		return this == &e;
	};
};



#endif /* EDGE_H_ */
