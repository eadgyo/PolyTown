/*
 * Edge.h
 *
 *  Created on: Feb 27, 2016
 *      Author: ronan-h
 */

#ifndef EDGE_H_
#define EDGE_H_
#include "PointType.h"

class Edge
{
public:
	Edge prev;
	Edge next;
	PointType p0;
	PointType p1;

	float getMinX()
	{
		if(p0.x() < p1.x())
			return p0.x();
		else
			return p1.x();
	}
};



#endif /* EDGE_H_ */
