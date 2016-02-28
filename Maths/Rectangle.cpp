#include "Rectangle.h"

Rectangle::Rectangle() : Form(4)
{
	set(Vector3D(), Vector3D(), 0);
}

Rectangle::Rectangle(const Rectangle& rectangle) : Form(rectangle)
{
	length.set(rectangle.getLength());
}

Rectangle::Rectangle(const Form& form) : Form(form)
{
	assert(form.size() == 4);

	//Les 2 points doivent être opposés
	Vector3D vec(points.at(0), points.at(2));
	orientation.setPos(points.at(0) + vec * 0.5f);

	Vector3D side(points.at(0), points.at(1));
	length[0] = side.getMagnitude();

	side.set(points.at(0), points.at(1));
	length[1] = side.getMagnitude();
}

Rectangle::Rectangle(const Vector3D& center, const Vector3D& length,
		float omega) : Form(4)
{
	set(center, length, omega);
}

Rectangle::~Rectangle()
{
}

Rectangle Rectangle::clone()
{
	return Rectangle((*this));
}

void Rectangle::set(const Vector3D& center, const Vector3D& length, float omega)
{
	clearTransformations();
	orientation.setPos(center);
	this->length.set(length);

	points.at(0).set(- 0.5f*length.x(),- 0.5f*length.y());
	points.at(1).set(- 0.5f*length.x(),+ 0.5f*length.y());
	points.at(2).set(+ 0.5f*length.x(),+ 0.5f*length.y());
	points.at(3).set(+ 0.5f*length.x(),- 0.5f*length.y());

	rotateRadians(omega, center);
}

void Rectangle::set(const Rectangle& rec)
{
	set(rec.getCenter(), rec.getLength(), rec.getAngle());
	setInit(rec);
}

void Rectangle::set(const Form& form)
{
	assert(form.size() == 4);

	for(int i=0; i<4; i++)
		points[i].set(form.getLocal(i));

	//Les 2 points doivent être opposés
	Vector3D vec(form.getLocal(0), form.getLocal(2));
	orientation.setPos(form.getLocal(0) + vec*0.5f);

	Vector3D side = new Vector3D(form.getLocal(0), form.getLocal(1));
	length[0] = side.getMagnitude();

	side.set(form.getLocal(0), form.getLocal(3));
	length[1] = side.getMagnitude();

	setInit(form);
}

Vector3D Rectangle::getVecLocal() const
{
	return Vector3D(points.at(0), points.at(3));
}

Vector3D Rectangle::getVecWorld() const
{
	Vector3D vec(points.at(0), points.at(3));
	return orientation*vec;
}

float Rectangle::getAngle(const Vector3D& vec) const
{
	Vector3D l_vec1 = getVecWorld();
	if(l_vec1.x() == 0 && l_vec1.y() == 0)
		return getAngle();
	return l_vec1.getAngle(vec);
}

float Rectangle::getAngle() const
{
	return omega;
}

void Rectangle::scaleF(float factor, const Vector3D& center)
{
	Form::scaleF(factor, center);
	length *= factor;
}
