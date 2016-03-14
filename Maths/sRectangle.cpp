
#include "sRectangle.h"

sRectangle::sRectangle() : Form(4)
{

	set(0, 0, 0, 0);
}

sRectangle::sRectangle(const Vector3D& left, const Vector3D& length) : Form(4)
{

	setLeft(left, length);
}

sRectangle::sRectangle(float x, float y, float width, float height) : Form(4)
{
	setLeft(x, y, width, height);
}

sRectangle::sRectangle(int x, int y, int width, int height) : Form(4)
{
	setLeft((float) x, (float) y, (float) width, (float) height);
}

sRectangle::sRectangle(const Form& form) : Form(form)
{
	set(form);
}

sRectangle::~sRectangle()
{

}

sRectangle sRectangle::createSRectangleCenter(const Vector3D& center,
		const Vector3D& length)
{
	sRectangle rec(center, length);
	rec.translate(Vector3D::sub(rec.getCenter(), center));
	return rec;
}

void sRectangle::set(const Form& form)
{
	assert(form.size() == 4);
	//Les 2 points doivent être opposés
	Vector3D vec = Vector3D::sub(points[0], points[2]);
	orientation.setPos(points[0] + vec*0.5f);

	Vector3D side = Vector3D::sub(points[0], points[1]);
	length[0] = side.getMagnitude();

	side.set(points[0], points[1]);
	length[1] = side.getMagnitude();
}

void sRectangle::set(const Vector3D& center, const Vector3D& length)
{
	orientation.setPos(center);
	this->length.set(length);
	points.at(0).set2D(center.x() - 0.5f*length.x(), center.y() - 0.5f*length.y());
	points.at(1).set2D(center.x() - 0.5f*length.x(), center.y() + 0.5f*length.y());
	points.at(2).set2D(center.x() + 0.5f*length.x(), center.y() + 0.5f*length.y());
	points.at(3).set2D(center.x() + 0.5f*length.x(), center.y() - 0.5f*length.y());
}

void sRectangle::set(const sRectangle& rec)
{
	setLeft(rec.getLeft(), rec.getLength());
}

void sRectangle::set(float x, float y, float width, float height)
{
	orientation.setX(x);
	orientation.setY(y);
	length[0] = width;
	length[1] = height;
	points.at(0).set2D(- 0.5f*length.x(), - 0.5f*length.y());
	points.at(1).set2D(- 0.5f*length.x(), + 0.5f*length.y());
	points.at(2).set2D(+ 0.5f*length.x(), + 0.5f*length.y());
	points.at(3).set2D(+ 0.5f*length.x(), - 0.5f*length.y());
}

void sRectangle::setLeft(const Vector3D& left, const Vector3D& length)
{
	this->length.set(length);
	orientation.setPos(Vector3D(left.x() + length.x()*0.5f, left.y() + length.y()*0.5f));

	points.at(0).set2D(- 0.5f*length.x(), - 0.5f*length.y());
	points.at(1).set2D(- 0.5f*length.x(), + 0.5f*length.y());
	points.at(2).set2D(+ 0.5f*length.x(), + 0.5f*length.y());
	points.at(3).set2D(+ 0.5f*length.x(), - 0.5f*length.y());
}

void sRectangle::setLeft(float x, float y, float width, float height)
{
	this->length.set2D(width, height);
	orientation.setPos(Vector3D(x + width*0.5f, y + height*0.5f));

	points.at(0).set2D(- 0.5f*length.x(), - 0.5f*length.y());
	points.at(1).set2D(- 0.5f*length.x(), + 0.5f*length.y());
	points.at(2).set2D(+ 0.5f*length.x(), + 0.5f*length.y());
	points.at(3).set2D(+ 0.5f*length.x(), - 0.5f*length.y());
}

bool sRectangle::isInside(const sRectangle& rect) const
{
	if(rect.getX() > points.at(0).x() && rect.getX(2) < points.at(2).x())
		if(rect.getY() > points.at(0).y() &&  rect.getY(2) < points.at(2).y())
			return true;
	return false;
}

bool sRectangle::isInside(const Vector3D& p) const
{
	if(p.x() > points.at(0).x() && p.x() < points.at(2).x())
		if(p.y() > points.at(0).y() &&  p.y() < points.at(2).y())
			return true;
	return false;
}

bool sRectangle::isInsideBorder(const sRectangle& rect) const
{
	if(rect.getX() >= points.at(0).x() && rect.getX(2) <= points.at(2).x())
		if(rect.getY() >= points.at(0).y() &&  rect.getY(2) <= points.at(2).y())
			return true;
	return false;
}

bool sRectangle::isInsideBorder(const Vector3D& p) const
{
	if(p.x() >= points.at(0).x() && p.x() <= points.at(2).x())
		if(p.y() >= points.at(0).y() &&  p.y() <= points.at(2).y())
			return true;
	return false;
}

bool sRectangle::collision(const sRectangle& rect) const
{
	return ((getX(0) > rect.getX(0) || getX(2) > rect.getX(0)) && (getX(0) < rect.getX(2) || getX(2) < rect.getX(2))) &&
		((getY(0) > rect.getY(0) || getY(2) > rect.getY(0)) && (getY(0) < rect.getY(2) || getY(2) < rect.getY(2)));
}


bool sRectangle::collisionBorder(const sRectangle& rect) const
{
	return ((getX(0) >= rect.getX(0) || getX(2) >= rect.getX(0)) && (getX(0) <= rect.getX(2) || getX(2) <= rect.getX(2))) &&
			((getY(0) >= rect.getY(0) || getY(2) >= rect.getY(0)) && (getY(0) <= rect.getY(2) || getY(2) <= rect.getY(2)));
}

SDL_Rect sRectangle::getSDLRect()
{
	SDL_Rect src;
	src.x = (int) getLeftX();
	src.y = (int) getLeftY();
	src.w = (int) getWidth();
	src.h = (int) getHeight();
	return src;
}

SDL_Rect sRectangle::getSDLRect(bool flipH, bool flipW)
{
	SDL_Rect src;
	src.x = (int) getLeftX();
	src.y = (int) getLeftY();
	src.w = (int) getWidth()*(flipH)?-1:1;
	src.h = (int) getHeight()*(flipV)?-1:1;
	return src;
}

SDL_Rect sRectangle::getSDLRectDest()
{
	SDL_Rect src;
	src.x = (int) getLeftX();
	src.y = (int) getLeftY();
	src.w = (int) getWidth();
	src.h = (int) getHeight();
	return src;
}
