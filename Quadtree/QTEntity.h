#pragma once
class Road;
#include "../Maths/myRectangle.h"
#include "../Maths/sRectangle.h"
#include "../Maths/Circle.h"

class QTEntity
{
public:
	QTEntity() { form = NULL; };
	QTEntity(const Form& form);
	QTEntity(const myRectangle& rectangle);
	QTEntity(const Circle& circle);
	QTEntity(const Vector3D& center, float width, float height);
	QTEntity(const Vector3D& center, float width, float height, float theta);
	QTEntity(const Vector3D& center, float radius);
	QTEntity(const QTEntity& qtEntity);
	virtual ~QTEntity();

	

	// Getter
	float getAngle2D() const;
	Vector3D getDirectorVec() const;


	
	inline sRectangle getBounds() const { return form->getBound(); };
	inline sRectangle getBoundsMax() const { return form->getBoundMax(); };
	inline Form* getForm() const { return form; };
	inline Vector3D getCenter() const { assert(form != NULL);  return form->getCenter(); };
	inline std::string getName() const { return m_name; };

	sRectangle* castSRectangle() const;
	myRectangle* castMyRectangle() const;
	Circle* castCircle() const;
	const sRectangle* castSRectangleConst() const;
	const myRectangle* castMyRectangleConst() const;
	const Circle* castCircleConst() const;

	// Setter
	inline void setCenter(const Vector3D center) { assert(form != NULL); this->form->setPos(center); }

	void set2points(const Vector3D& A, const Vector3D& B, float width);
	void set2points(const Vector3D& A, const Vector3D& B, float width, float heigth);
	void set(const Vector3D& center, float witdh, float height, float theta);
	void set(const Vector3D& center, float witdh, float height);
	void set(const Vector3D& center, float radius);
	
    void setName(std::string name);

	// Transformations
	inline void setRadians(float theta) { form->setRadians(theta); };
	inline void translate(const Vector3D& vec) { form->translate(vec); };


	bool isColliding(Form& form);
	bool isColliding(Form& form, Vector3D& push, float& t);
	bool isColliding(QTEntity& qtEntity);
	bool isColliding(QTEntity& qtEntity, Vector3D& push, float& t);

protected:
	void initRectangle(const Vector3D& center, float width, float height);
	void initRectangle(const Vector3D& center, float width, float height, float theta);
	void initRectangle();
	void initCircle(const Vector3D& center, float radius);

	Form* form;
    std::string m_name;
	
};