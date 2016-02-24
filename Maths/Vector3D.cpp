
#include "Vector3D.h"

Vector3D::Vector3D(const Vector3D& a, const Vector3D& b)
{
	Vector3D result = b - a;
	set(result);
}
Vector3D::Vector3D(float x, float y, float z)
{
	coor[0] = x;
	coor[1] = y;
	coor[2] = z;
	coor[3] = 1;
}
Vector3D::Vector3D(float x, float y, float z, bool isPoint)
{
	coor[0] = x;
	coor[1] = y;
	coor[2] = z;
	if(isPoint)
		coor[3] = 1;
	else
		coor[3] = 0;
}
Vector3D::Vector3D(float const* v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] = v[i];
	}
}

Vector3D::Vector3D copy()
{
	return Vector3D(this);
}

Vector3D::Vector3D getTransformation(Matrix4 m4)
{

}

float Vector3D::getMagnitude()
{
	return std::sqrt((*this)*(*this));
}
float Vector3D::getSqMagnitude()
{
	return (*this)*(*this);
}
void Vector3D::normalize()
{
	float magn = getMagnitude();
	for(int i=0; i<SIZE_V; i++)
		coor[i] /= magn;
}

// Setter
void Vector3D::set(const Vector3D& a)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] = a[i];
	}
}
void Vector3D::set(int i, float f)
{
	assert(i > 0 and i < SIZE_V);
	coor[i] = f;
}
void Vector3D::set(float f)
{
	coor[0]= f;
}
void Vector3D::set(float a, float b)
{
	coor[0] = a;
	coor[1] = b;
}
void Vector3D::set(float a, float b, float c)
{
	coor[0] = a;
	coor[1] = b;
	coor[2] = c;
}
void Vector3D::set(float a, float b, float c, float w)
{
	coor[0] = a;
	coor[1] = b;
	coor[2] = c;
	coor[3] = w;
}

// Surchage opérateurs

Vector3D Vector3D::operator-()
{
	Vector3D vec();
	for(int i=0; i<SIZE_V; i++)
		vec[i] = -coor[i];
	return vec;
}
void Vector3D::operator+=(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] += v[i];
	}
}
Vector3D Vector3D::operator+(Vector3D const& v)
{
	Vector3D vec();
	for(int i=0; i<SIZE_V; i++)
	{
		vec[i] = coor[i] + v[i];
	}
	return vec;
}
void Vector3D::operator-=(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] -= v[i];
	}
}
Vector3D Vector3D::operator-(Vector3D const& v)
{
	Vector3D vec();
	for(int i=0; i<SIZE_V; i++)
	{
		vec[i] = coor[i] - v[i];
	}
	return vec;
}
float Vector3D::operator*(Vector3D const& v)
{
	float scalar = 0;
	for(int i=0; i<3; i++)
	{
		scalar += coor[i]*v[i];
	}
	return scalar;
}
Vector3D Vector3D::operator*(float const& f)
{
	Vector3D vec();
	for(int i=0; i<3; i++)
	{
		vec[i] = coor[i]*f;
	}
	return vec;
}
void Vector3D::operator*=(float const& f)
{
	for(int i=0; i<3; i++)
	{
		coor[i] *= f;
	}
}
Vector3D Vector3D::operator%(Vector3D const& v)
{
	// cross Product
	Vector3D vec();
	vec[0] = coor[1]*vec[2] - coor[2]*vec[1];
	vec[1] = coor[2]*vec[0] - coor[0]*vec[2];
	vec[2] = coor[0]*vec[1] - coor[1]*vec[0];
	vec[3] = 0;
	return vec;
}

void Vector3D::operator%=(Vector3D const& v)
{
	Vector3D vec = (*this)%v;
	set(vec);
}
float Vector3D::operator[](int const& i)
{
	return coor[i];
}

bool Vector3D::operator==(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		float res = (v[i]-coor[i]);
		if(std::abs(res) > MIN_DIFF_EQ)
			return false;
	}
	return true;
}

