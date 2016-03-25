#include "myRectangle.h"

myRectangle::myRectangle() : Form(4)
{
	width = 0;
	height = 0;
}

myRectangle::myRectangle(const myRectangle& rectangle) : Form(rectangle)
{
	width = rectangle.getWidth();
	height = rectangle.getHeight();
}

myRectangle::myRectangle(const Form& form) : Form(form)
{
	assert(form.size() == 4);

	//Les 2 points doivent être opposés
	Vector3D vec = Vector3D::sub(points.at(0), points.at(2));
	orientation.setPos(points.at(0) + vec * 0.5f);

	Vector3D side = Vector3D::sub(points.at(0), points.at(1));
	width = side.getMagnitude();

	side.set(points.at(0), points.at(1));
	height = side.getMagnitude();
}

myRectangle::myRectangle(const Vector3D& center, float width, float height, float omega) : Form(4)
{
	set(center, width, height, omega);
}
myRectangle::myRectangle(float x, float y, float width, float height, float omega) : Form(4)
{
	set(Vector3D(x, y), width, height, omega);
}

myRectangle::myRectangle(const Vector3D& center, float width, float height) : Form(4)
{
	set(center, width, height, 0);
}

myRectangle::~myRectangle()
{
}

myRectangle myRectangle::clone()
{
	return myRectangle((*this));
}

void myRectangle::set(const Vector3D& center, float width, float height)
{
	set(center, width, height, 0);
}

void myRectangle::set(const Vector3D& center, float width, float height, float omega)
{
	clearTransformations();
	orientation.setPos(center);
	this->width = width;
	this->height = height;

	points.at(0).set2D(-0.5f*width, -0.5f*height);
	points.at(1).set2D(-0.5f*width, +0.5f*height);
	points.at(2).set2D(+0.5f*width, +0.5f*height);
	points.at(3).set2D(+0.5f*width, -0.5f*height);

	rotateRadians(omega, center);
}

void myRectangle::set(const myRectangle& rec)
{
	set(rec.getCenter(), rec.getWidth(), rec.getHeight(), rec.getAngle());
	setInit(rec);
}

void myRectangle::set(const Form& form)
{
	assert(form.size() == 4);

	clearTransformations();

	for(int i=0; i<4; i++)
		points[i].set(form.getLocal(i));

	//Les 2 points doivent être opposés
	Vector3D vec = Vector3D::sub(form.getLocal(0), form.getLocal(2));
	orientation.setPos(form.getLocal(0) + vec*0.5f);

	Vector3D side = Vector3D::sub(form.getLocal(0), form.getLocal(1));
	width = side.getMagnitude();

	side.set(form.getLocal(0), form.getLocal(3));
	height = side.getMagnitude();

	setInit(form);
}

Vector3D myRectangle::getVecLocal() const
{
	return Vector3D::sub(points.at(0), points.at(3));
}

Vector3D myRectangle::getVecWorld() const
{
	Vector3D vec = Vector3D::sub(points.at(0), points.at(3));
	return orientation*vec;
}

Vector3D myRectangle::getVecWorldNormal() const
{
	Vector3D vec = Vector3D::sub(points.at(0), points.at(1));
	return orientation*vec;
}

float myRectangle::getAngle(const Vector3D& vec) const
{
	Vector3D l_vec1 = getVecWorld();
	if(l_vec1.x() == 0 && l_vec1.y() == 0)
		return getAngle();
	return l_vec1.getAngle2D(vec);
}

float myRectangle::getAngle() const
{
	return omega;
}

void myRectangle::scaleF(float factor, const Vector3D& center)
{
	Form::scaleF(factor, center);
	width *= factor;
	height *= factor;
}
