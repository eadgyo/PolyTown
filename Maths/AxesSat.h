#pragma once

#include <vector>
#include "Vector3D.h"

struct AxesSat
{
	std::vector<Vector3D> axes;
	std::vector<float> tAxes;
	std::vector<Vector3D> axesT;
	std::vector<float> tAxesT;
};
