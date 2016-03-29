#include "sRectangle.h"


sRectangle::sRectangle() : Form(4)
{
	set(0, 0, 0, 0);
}

sRectangle::sRectangle(const Vector3D & left, float width, float height) : Form(4)
{
	setLeft(left, width, height);
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

sRectangle::sRectangle(const sRectangle& rec) : Form(rec)
{
	width = rec.getWidth();
	height = rec.getHeight();
}

sRectangle::~sRectangle()
{

}

sRectangle sRectangle::clone() const
{
	sRectangle rec;
	rec.set((*this));
	return rec;
}

sRectangle sRectangle::createSRectangleCenter(const Vector3D& center,
		float width, float height)
{
	sRectangle rec(center, width, height);
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
	width = side.getMagnitude();

	side.set(points[0], points[1]);
	height = side.getMagnitude();
}

void sRectangle::set(const sRectangle& rec)
{
	setLeft(rec.getLeft(), rec.getWidth(), rec.getHeight());
}

void sRectangle::set(const Vector3D& center, float width, float height)
{
	orientation.setX(center.x());
	orientation.setY(center.y());
	this->width = width;
	this->height = height;
	points.at(0).set2D(-0.5f*width, -0.5f*height);
	points.at(1).set2D(-0.5f*width, +0.5f*height);
	points.at(2).set2D(+0.5f*width, +0.5f*height);
	points.at(3).set2D(+0.5f*width, -0.5f*height);
}

void sRectangle::set(float x, float y, float width, float height)
{
	orientation.setX(x);
	orientation.setY(y);
	this->width = width;
	this->height = height;
	points.at(0).set2D(- 0.5f*width, - 0.5f*height);
	points.at(1).set2D(- 0.5f*width, + 0.5f*height);
	points.at(2).set2D(+ 0.5f*width, + 0.5f*height);
	points.at(3).set2D(+ 0.5f*width, - 0.5f*height);
}

void sRectangle::setLeft(const Vector3D& left, float width, float height)
{
	this->width = width;
	this->height = height;
	orientation.setPos(Vector3D(left.x() + width*0.5f, left.y() + height*0.5f));

	points.at(0).set2D(-0.5f*width, -0.5f*height);
	points.at(1).set2D(-0.5f*width, +0.5f*height);
	points.at(2).set2D(+0.5f*width, +0.5f*height);
	points.at(3).set2D(+0.5f*width, -0.5f*height);
}

void sRectangle::setLeft(float x, float y, float width, float height)
{
	this->width = width;
	this->height = height;
	orientation.setPos(Vector3D(x + width*0.5f, y + height*0.5f));

	points.at(0).set2D(-0.5f*width, -0.5f*height);
	points.at(1).set2D(-0.5f*width, +0.5f*height);
	points.at(2).set2D(+0.5f*width, +0.5f*height);
	points.at(3).set2D(+0.5f*width, -0.5f*height);
}

void sRectangle::setLeft(float x, float y)
{
	orientation.setPos(Vector3D(x + width*0.5f, y + height*0.5f));
}

void sRectangle::setLeft(const Vector3D & left)
{
	orientation.setPos(Vector3D(left.x() + width*0.5f, left.y() + height*0.5f));
}

bool sRectangle::isInside(const sRectangle& rect) const
{
	if(rect.getX() > getX(0) && rect.getX(2) < getX(2))
		if(rect.getY() > getY(0) && rect.getY(2) < getY(2))
			return true;
	return false;
}

bool sRectangle::isInside(const Vector3D& p) const
{
	if(p.x() > getX(0) && p.x() < getX(2))
		if(p.y() > getY(0) &&  p.y() < getY(2))
			return true;
	return false;
}

bool sRectangle::isInsideBorder(const sRectangle& rect) const
{
	if(rect.getX() >= getX(0) && rect.getX(2) <= getX(2))
		if(rect.getY() >= getY(0) &&  rect.getY(2) <= getY(2))
			return true;
	return false;
}

bool sRectangle::isInsideBorder(const Vector3D& p) const
{
	if(p.x() >= getX(0) && p.x() <= getX(2))
		if(p.y() >= getY(0) &&  p.y() <= getY(2))
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

void sRectangle::scaleF(float factor, const Vector3D & center)
{
	Form::scaleF(factor, center);
	width *= factor;
	height *= factor;
}
