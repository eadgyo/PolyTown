#pragma once
#include "../Maths/Vector3D.h"
#include "../Maths/sRectangle.h"
#include "../Graphics/Graphics.h"

class Bouton
{
public:
	Bouton(int x, int y, int width, int height);
	Bouton(std::string text, int x, int y, int width, int height);
	~Bouton();

	void setColor(float r, float g, float b, float a);

	void update(float dt);
	void render(Graphics* g);
	bool isColliding(const Vector3D& pos);

private:
	int r, g, b, a;
	sRectangle rectangle;
	std::string text;
};

