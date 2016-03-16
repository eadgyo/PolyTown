#include "QTEntity.h"

QTEntity::QTEntity(std::string name, const Form& form)
{
	this->name = name;
	this->form = new Form(form);
}
QTEntity::QTEntity(const Form& form)
{
	this->form = new Form(form);
}
QTEntity::QTEntity(const Vector3D& center, const Vector3D& length)
{
	form = NULL;
	initRectangle(center, length);
}
QTEntity::QTEntity(const Vector3D& center, const Vector3D& length, float theta)
{
	form = NULL;
	initRectangle(center, length, theta);
}
QTEntity::QTEntity(const Vector3D& center, float radius)
{
	form = NULL;
	initCircle(center, radius);
}

QTEntity::QTEntity(const myRectangle& rectangle)
{
	form = NULL;
	form = new myRectangle(rectangle);
}
QTEntity::QTEntity(const Circle& circle)
{
	form = NULL;
	form = new Circle(circle);
}

QTEntity::~QTEntity()
{
	if (form)
	{
		delete form;
	}
}

void QTEntity::initRectangle(const Vector3D& center, const Vector3D& length)
{
	if (!form)
	{
		form = new myRectangle(center, length);
	}
}

void QTEntity::initRectangle(const Vector3D& center, const Vector3D& length, float theta)
{
	if (!form)
	{
		form = new myRectangle(center, length, theta);
	}
}

void QTEntity::initRectangle()
{
	initRectangle(Vector3D(true), Vector3D(true));
}

void QTEntity::initCircle(const Vector3D& center, float radius)
{
	if (!form)
	{
		form = new Circle(center, radius);
	}
}

void QTEntity::set2points(const Vector3D& A, const Vector3D& B, float width)
{
	float height = (A - B).getMagnitude();
	set2points(A, B, Vector3D(width, height));
}

void QTEntity::set2points(const Vector3D& A, const Vector3D& B, const Vector3D& length)
{
	// A start Middle, B end middle

	// On récupère le milieu des deux points
	Vector3D center = (A + B)*0.5f;
	Vector3D vec = (B - A).getNormalize();
	float theta = vec.getAngle2D(Vector3D(1, 0, 0, false));
	set(center, length, theta);
}

void QTEntity::set(const Vector3D & center, const Vector3D length, float theta)
{
	Form *testForm = form;
	if (form)
	{
		myRectangle* castmyRectangle = dynamic_cast<myRectangle*>(testForm);
		if (castmyRectangle != NULL)
		{
			castmyRectangle->set(center, length, theta);
		}
		else
		{
			std::cout << "La form n'est du bon type" << std::endl;
			assert(0);
		}
	}
}

void QTEntity::set(const Vector3D & center, const Vector3D length)
{
	Form *testForm = form;
	if (form)
	{
		myRectangle* castmyRectangle = dynamic_cast<myRectangle*>(testForm);
		sRectangle* castsRectangle = dynamic_cast<sRectangle*>(testForm);
		if (castmyRectangle != NULL)
		{
			castmyRectangle->set(center, length, 0);
			return;
		}

		if (castsRectangle != NULL)
		{
			castsRectangle->set(center, length);
		}
		else
		{
			std::cout << "La form n'est du bon type" << std::endl;
			assert(0);
		}
	}
}

void QTEntity::set(const Vector3D& center, float radius)
{
	Form *testForm = form;
	if (form)
	{
		Circle* castCircle = dynamic_cast<Circle*>(testForm);
		if (castCircle != NULL)
		{
			castCircle->set(center, radius);
		}
		else
		{
			std::cout << "La form n'est du bon type" << std::endl;
			assert(0);
		}
	}
}


sRectangle *QTEntity::castSRectangle()
{
	return dynamic_cast<sRectangle*>(form);
}
myRectangle *QTEntity::castMyRectangle()
{
	return dynamic_cast<myRectangle*>(form);
}
Circle *QTEntity::castCircle()
{
	return dynamic_cast<Circle*>(form);
}

const sRectangle *QTEntity::castSRectangleConst() const
{
	return dynamic_cast<sRectangle*>(form);
}
const myRectangle *QTEntity::castMyRectangleConst() const
{
	return dynamic_cast<myRectangle*>(form);
}
const Circle *QTEntity::castCircleConst() const 
{
	return dynamic_cast<Circle*>(form);
}