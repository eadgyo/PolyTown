#include "myRectangle.h"

myRectangle::myRectangle() : Form(4)
{
	set(Vector3D(true), Vector3D(true), 0);
}

myRectangle::myRectangle(const myRectangle& rectangle) : Form(rectangle)
{
	length.set(rectangle.getLength());
}

myRectangle::myRectangle(const Form& form) : Form(form)
{
	assert(form.size() == 4);

	//Les 2 points doivent être opposés
	Vector3D vec = Vector3D::sub(points.at(0), points.at(2));
	orientation.setPos(points.at(0) + vec * 0.5f);

	Vector3D side = Vector3D::sub(points.at(0), points.at(1));
	length[0] = side.getMagnitude();

	side.set(points.at(0), points.at(1));
	length[1] = side.getMagnitude();
}

myRectangle::myRectangle(const Vector3D& center, const Vector3D& length) : Form(4)
{
	set(center, length, 0);
}

myRectangle::myRectangle(const Vector3D& center, const Vector3D& length,
		float omega) : Form(4)
{
	set(center, length, omega);
}

myRectangle::~myRectangle()
{
}

myRectangle myRectangle::clone()
{
	return myRectangle((*this));
}

void myRectangle::set(const Vector3D& center, const Vector3D& length, float omega)
{
	clearTransformations();
	orientation.setPos(center);
	this->length.set(length);

	points.at(0).set2D(- 0.5f*length.x(),- 0.5f*length.y());
	points.at(1).set2D(- 0.5f*length.x(),+ 0.5f*length.y());
	points.at(2).set2D(+ 0.5f*length.x(),+ 0.5f*length.y());
	points.at(3).set2D(+ 0.5f*length.x(),- 0.5f*length.y());

	rotateRadians(omega, center);
}

void myRectangle::set(const myRectangle& rec)
{
	set(rec.getCenter(), rec.getLength(), rec.getAngle());
	setInit(rec);
}

void myRectangle::set(const Form& form)
{
	assert(form.size() == 4);

	for(int i=0; i<4; i++)
		points[i].set(form.getLocal(i));

	//Les 2 points doivent être opposés
	Vector3D vec = Vector3D::sub(form.getLocal(0), form.getLocal(2));
	orientation.setPos(form.getLocal(0) + vec*0.5f);

	Vector3D side = Vector3D::sub(form.getLocal(0), form.getLocal(1));
	length[0] = side.getMagnitude();

	side.set(form.getLocal(0), form.getLocal(3));
	length[1] = side.getMagnitude();

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
	length *= factor;
}
