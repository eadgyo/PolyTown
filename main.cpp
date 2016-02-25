#include "SDL/SDL.h"
#include "Maths/Vector3D.h"
#include <iostream>

int main(int argc, char* args[])
{
	float tab[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	float tab1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 12, 13, 14, 15, 16 };
	Matrix4 m = Matrix4::createIdentity();
	std::cout << m.getDeterminant() << "\n";
	m.transpose();

	m.display();

    return 0;
}
