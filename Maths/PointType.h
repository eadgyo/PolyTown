

#ifndef POINT_TYPE_H_

#define POINT_TYPE_H_

#include "Vector3D.h"

class PointType : public Vector3D
{
public:
	PointType() : Vector3D(true) { init(); };
	PointType(const Vector3D& point2D) : Vector3D(point2D) { init(); };

	inline void init()
	{
		posPoint = 0;
		posEdge = 0;
		type = 0;
	};
	inline bool operator<(const Vector3D& p) const { std::cout << "PointType <"; return true; };
	inline bool operator<(const PointType& p) const { std::cout << "PointType <"; return true; };

	const static int REGULAR = 0;
	const static int START = 1;
	const static int END = 2;
	const static int SPLIT = 3;
	const static int MERGE = 4;

	int posPoint;
	int posEdge;
	int type;
};

#endif
