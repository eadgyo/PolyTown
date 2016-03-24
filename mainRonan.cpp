#include <Windows.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Maths/Vector3D.h"
#include <iostream>
#include "Maths/myRectangle.h"
#include "Maths/Form.h"
#include "FileManager/FileManager.h"
#include "Game/PolyTown.h"

#define WIDTH 1500
#define HEIGHT 800

int main(int argc, char* args[])
{
	/*
	Test Forme
	*/
	Form form;
	Form form1;
	form.addPoint(Vector3D(574, 53));
	form.addPoint(Vector3D(430, 42));
	form.addPoint(Vector3D(288, 99));
	form.addPoint(Vector3D(215, 249));
	form.addPoint(Vector3D(497, 364));
	form.rotateDegrees(30.0f, Vector3D(15, 30));
	form.scaleF(2.0f, Vector3D(55, 3));

	form.getOrientation().display();

	form1.addPoint(Vector3D(390, 232));
	form1.addPoint(Vector3D(168, 121));
	form1.addPoint(Vector3D(52, 253));
	form1.addPoint(Vector3D(134, 466));
	form1.rotateDegrees(5.0f, Vector3D(-15, 30));

	Vector3D push(0, 0);
	float t = 0;
	bool isA = form1.collisionSatA(form, Vector3D(0, 0), Vector3D(0, 0), push, t);
	

    return 0;
}
