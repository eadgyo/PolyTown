#pragma once
#include "../Maths/Vector3D.h"
#include "../Maths/sRectangle.h"
#include "../Graphics/Graphics.h"

class Bouton
{
public:
	Bouton(Graphics* graphics, int x, int y, int width, int height);

	virtual ~Bouton();

	void setColor(myColor color);
	void setColorRec(myColor color);
	void setColor(float r, float g, float b, float a);
	myColor getColor();
	myColor getColorRec();

	virtual void update(float dt);
	virtual void render(Graphics* g);
	virtual void render(Graphics* g, const Vector3D& translation);
	virtual inline void render() { render(graphics);  };
	virtual inline void render(const Vector3D& translation) { render(graphics, translation); };

	bool isColliding(const Vector3D& pos);

	myColor getAddColorB() const { return m_addColorB; };
	void setAddColorB(myColor color) { m_addColorB = color; };
	void setDrawRec(bool drawRec) { this->drawRec = drawRec; };

protected:
	bool drawRec;
	myColor m_addColorB;
	myColor color_Rec;
	myColor color;
	sRectangle rectangle;
	Graphics* graphics = NULL;
};

