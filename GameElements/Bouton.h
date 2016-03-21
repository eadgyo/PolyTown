#pragma once
#include "../Maths/Vector3D.h"
#include "../Maths/sRectangle.h"
#include "../Graphics/Graphics.h"

class Bouton
{
public:
	Bouton(Graphics* graphics, int x, int y, int width, int height);
	Bouton(Graphics* graphics, std::string text, int x, int y, int width, int height);
	Bouton(Graphics* graphics, std::string text, unsigned int size, int x, int y, int width, int height);
	virtual ~Bouton();

	void setColor(float r, float g, float b, float a);

	void update(float dt);
	void render(Graphics* g);
	void render(Graphics* g, const Vector3D& translation);
	inline void render() { render(graphics);  };
	inline void render(const Vector3D& translation) { render(graphics, translation); };

	bool isColliding(const Vector3D& pos);

protected:
	float r, g, b, a;
	sRectangle rectangle;
	std::string text;
	unsigned textSize;
	Graphics* graphics = NULL;
};

