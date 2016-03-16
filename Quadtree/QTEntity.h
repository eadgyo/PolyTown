#pragma once
#include "../Maths/myRectangle.h"
#include "../Maths/sRectangle.h"
#include "../Maths/Circle.h"

class QTEntity
{
public:
	QTEntity() { form = NULL; name = ""; };
	QTEntity(std::string name) { form = NULL; this->name = name; };
	QTEntity(std::string name, const Form& form);
	QTEntity(const Form& form);
	QTEntity(const myRectangle& rectangle);
	QTEntity(const Circle& circle);
	QTEntity(const Vector3D& center, const Vector3D& length);
	QTEntity(const Vector3D& center, const Vector3D& length, float theta);
	QTEntity(const Vector3D& center, float radius);
	~QTEntity();

	

	// Getter
	inline std::string getName() const { return name; };
	inline sRectangle getBounds() const { return form->getBound(); };
	inline Form* getForm() { return form; };

	sRectangle* castSRectangle();
	myRectangle* castMyRectangle();
	Circle* castCircle();
	const sRectangle* castSRectangleConst() const;
	const myRectangle* castMyRectangleConst() const;
	const Circle* castCircleConst() const;

	// Setter
	inline void setName(std::string name) { this->name = name; };

	void set2points(const Vector3D& A, const Vector3D& B, float width);
	void set2points(const Vector3D& A, const Vector3D& B, const Vector3D& length);
	void set(const Vector3D& center, const Vector3D length, float theta);
	void set(const Vector3D& center, const Vector3D length);
	void set(const Vector3D& center, float radius);

protected:
	void initRectangle(const Vector3D& center, const Vector3D& length);
	void initRectangle(const Vector3D& center, const Vector3D& length, float theta);
	void initRectangle();
	void initCircle(const Vector3D& center, float radius);

	Form* form;
	std::string name;

};