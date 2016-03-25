#include "Circle.h"

Circle::Circle(const Circle& circle) : Form(circle)
{
	this->radius = circle.getRadius();
}

Circle::Circle()
{
	this->radius = 0;
}


Circle::Circle(const Vector3D& center, float radius)
{
	this->setCenter(center);
	this->radius = radius;
}

Circle::~Circle()
{
}

void Circle::set(const Circle& circle)
{
	setInit(circle);
	this->radius = circle.getRadius();
}

void Circle::set(const Vector3D& center, float radius)
{
	this->setCenter(center);
	this->radius = radius;
}

void Circle::set(float radius)
{
	this->radius = radius;
}


void Circle::scaleF(float factor, Vector3D center)
{
	Form::scaleF(factor, center);
	radius *= factor;
}
float Circle::getMinX() const
{
	return getCenterX() - radius;
}
float Circle::getMinY() const
{
	return getCenterY() - radius;
}
float Circle::getMaxX() const
{
	return getCenterX() + radius;
}
float Circle::getMaxY() const
{
	return getCenterY() + radius;
}
bool Circle::isColliding(const Circle& circle) const
{
	Vector3D vec = Vector3D::sub(circle.getCenter(), getCenter());
	if (vec.getMagnitude() <= radius + circle.radius)
		return true;
	return false;
}

bool Circle::collisionSat(Form & form)
{
	return false;
}

bool Circle::collisionSat(Form & form, const Vector3D & VA, const Vector3D & VB, const Vector3D & push, float & t)
{
	return false;
}

bool Circle::collisionSatFree(const Form & B, const Vector3D & VA, const Vector3D & VB)
{
	return false;
}
