#include "SDL/SDL.h"
#include "Maths/Vector3D.h"
#include <iostream>

int main(int argc, char* args[])
{
	float tab[] = { 0, 6, 3, 4, 7, 6, 7, 8, 9, 10, 101, 12, 13, 14, 15, 16 };
	Vector3D vec(1, 2, 4, 2);
	Matrix4 m1(tab);
	std::cout << m1.getDeterminant() << "\n";
	//m.transpose();
	m1.display();
	vec.display();

	Vector3D vec1 = vec * m1;
	vec1.display();

    return 0;
}
