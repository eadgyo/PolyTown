#pragma once
#include "../Maths/Vector3D.h"
#include "../Maths/sRectangle.h"
#include "../Graphics/Graphics.h"

class Bouton
{
public:
	Bouton(Graphics* graphics, int x, int y, int width, int height);

	virtual ~Bouton();

	void setColor(float r, float g, float b, float a);

	virtual void update(float dt);
	virtual void render(Graphics* g);
	virtual void render(Graphics* g, const Vector3D& translation);
	virtual inline void render() { render(graphics);  };
	virtual inline void render(const Vector3D& translation) { render(graphics, translation); };

	bool isColliding(const Vector3D& pos);

protected:
	float r, g, b, a;
	sRectangle rectangle;
	Graphics* graphics = NULL;
};

