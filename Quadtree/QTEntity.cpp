#include "QTEntity.h"
#include "../GameContent/Road.h"


QTEntity::QTEntity(const Form& form)
{
	this->form = new Form(form);
    m_name = "";
}
QTEntity::QTEntity(const Vector3D& center, float width, float height)
{
	form = NULL;
	initRectangle(center, width, height);
    m_name = "";
}
QTEntity::QTEntity(const Vector3D& center, float width, float height, float theta)
{
	form = NULL;
	initRectangle(center, width, height, theta);
    m_name = "";
}
QTEntity::QTEntity(const Vector3D& center, float radius)
{
	form = NULL;
	initCircle(center, radius);
    m_name = "";
}

QTEntity::QTEntity(const myRectangle& rectangle)
{
	form = NULL;
	form = new myRectangle(rectangle);
    m_name = "";
}
QTEntity::QTEntity(const Circle& circle)
{
	form = NULL;
	form = new Circle(circle);
    m_name = "";
}
QTEntity::QTEntity(const QTEntity& qtEntity)
{
	// Il faut déterminer le type
	myRectangle* castmyRectangle = qtEntity.castMyRectangle();
	sRectangle* castsRectangle = qtEntity.castSRectangle();
	Circle* castsCircle = qtEntity.castCircle();
	if (castmyRectangle != NULL)
	{
		form = new myRectangle(*(castmyRectangle));
	}
	else if (castsRectangle != NULL)
	{
		form = new sRectangle(*(castsRectangle));
	}
	else if (castsCircle != NULL)
	{
		form = new Circle(*(castsCircle));
	}
	
	m_name = qtEntity.getName();
}

QTEntity::~QTEntity()
{
	if (form)
	{
		delete form;
		form = NULL;
	}
}

void QTEntity::initRectangle(const Vector3D& center, float width, float height)
{
	if (!form)
	{
		form = new myRectangle(center, width, height);
	}
}

void QTEntity::initRectangle(const Vector3D & center, float width, float height, float theta)
{
	if (!form)
	{
		form = new myRectangle(center, width, height, theta);
	}
}

void QTEntity::initRectangle()
{
	initRectangle(Vector3D(true), 0, 0);
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
	set2points(A, B, width, height);
}

void QTEntity::set2points(const Vector3D& A, const Vector3D& B, float width, float height)
{
	// A start Middle, B end middle

	// On récupère le milieu des deux points
	Vector3D center = (A + B)*0.5f;
	Vector3D vec = (B - A).getNormalize();
	float theta = Vector3D(0, 1, 0, false).getAngle2D(vec);
	set(center, width, height, theta);
}

void QTEntity::set(const Vector3D & center, float width, float height, float theta)
{
	Form *testForm = form;
	if (form)
	{
		myRectangle* castmyRectangle = dynamic_cast<myRectangle*>(testForm);
		if (castmyRectangle != NULL)
		{
			castmyRectangle->set(center, width, height, theta);
		}
		else
		{
			std::cout << "La form n'est du bon type" << std::endl;
			assert(0);
		}
	}
}

void QTEntity::set(const Vector3D & center, float width, float height)
{
	Form *testForm = form;
	if (form)
	{
		myRectangle* castmyRectangle = dynamic_cast<myRectangle*>(testForm);
		sRectangle* castsRectangle = dynamic_cast<sRectangle*>(testForm);
		if (castmyRectangle != NULL)
		{
			castmyRectangle->set(center, width, height);
			return;
		}

		if (castsRectangle != NULL)
		{
			castsRectangle->set(center, width, height);
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

void QTEntity::setName(std::string name)
{
    m_name = name;
}


Vector3D QTEntity::getDirectorVec() const
{
	if (form->size() > 1)
		return (form->get(1) - form->get(0)).getNormalize();
	else
		return Vector3D(0, 1, 0, false);
	
}
float QTEntity::getAngle2D() const
{
	Vector3D director = getDirectorVec();
	return director.getAngle2D(Vector3D(0, 1, 0, false));
}

sRectangle *QTEntity::castSRectangle() const
{
	return dynamic_cast<sRectangle*>(form);
}
myRectangle *QTEntity::castMyRectangle() const
{
	return dynamic_cast<myRectangle*>(form);
}
Circle *QTEntity::castCircle() const
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



bool QTEntity::isColliding(Form& form)
{
	return form.collisionSat(*(this->form));
}

bool QTEntity::isColliding(Form& form, Vector3D& push, float& t)
{
	return form.collisionSat(*(this->form), Vector3D(false), Vector3D(false), push, t);
}

bool QTEntity::isColliding(QTEntity & qtEntity)
{
	return isColliding(*qtEntity.getForm());
}

bool QTEntity::isColliding(QTEntity & qtEntity, Vector3D & push, float & t)
{
	return isColliding(*qtEntity.getForm(), push, t);
}
