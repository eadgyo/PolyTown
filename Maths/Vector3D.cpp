#include "Vector3D.h"

Vector3D::Vector3D(bool isPoint)
{
	coor[0] = 0;
	coor[1] = 0;
	coor[2] = 0;
	if(isPoint)
		coor[3] = 1;
	else
		coor[3] = 0;
}
Vector3D::Vector3D(const Vector3D& a)
{
	 for(int i=0; i<SIZE_V; i++)
	 {
		 coor[i] = a.get(i);
	 }
}
Vector3D::Vector3D(float x, float y)
{
	coor[0] = x;
	coor[1] = y;
	coor[2] = 0;
	coor[3] = 1;
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


Vector3D Vector3D::copy() const
{
	return Vector3D((*this));
}

Vector3D Vector3D::sub(const Vector3D& a, const Vector3D& b)
{
	Vector3D result = b - a;
	return result;
}
//====================================================
// Getter
//====================================================
float Vector3D::getAngle2D(const Vector3D& vec) const
{
	float scalar = getNormalize()*(vec.getNormalize());
	float l_fTheta = 0;
	if(scalar > 1.0f)
		l_fTheta = 0;
	else if(scalar < -1.0f)
		l_fTheta = (float) PI;
	else
		l_fTheta = (float) acos(scalar);

	if(((*this) % vec).z() < 0)
		l_fTheta = - l_fTheta;


	return l_fTheta;
}

float Vector3D::getAngle2D(const Vector3D& A, const Vector3D& C) const
{
	Vector3D AB = Vector3D::sub((*this), A);
	Vector3D CB = Vector3D::sub(C, (*this));
	float theta = (float) (PI - AB.getAngle2D(CB));
	return theta;
}

Vector3D Vector3D::getNormalize() const
{
	Vector3D vec = copy();
	vec.normalize();
	return vec;
}

float Vector3D::get(int i) const
{
	assert(i >=0 && i < SIZE_V);
	return coor[i];
}

Vector3D Vector3D::getTransformation(const Matrix4& m4) const
{
	Vector3D res;
	for(int i=0; i<LINE; i++)
	{
		res[i] = 0;
		for(int j=0; j<COL; j++)
		{
			res[i] += m4.get(i + j*COL)*coor[j];
		}
	}
	return res;
}

float Vector3D::getMagnitude() const
{
	return std::sqrt((*this)*(*this));
}
float Vector3D::getSqMagnitude() const
{
	return (*this)*(*this);
}
float Vector3D::normalize()
{
	float magn = getMagnitude();
	(*this)/=magn;
	return magn;
}
Vector3D Vector3D::getProjection2D(const Vector3D& vec, const Vector3D& p) const
{
	Vector3D l_vec = vec.getNormalize();
	Vector3D vec1 = Vector3D::sub(p, (*this));
	float projectScalar = l_vec*vec1;
	Vector3D projection(p + (l_vec*projectScalar));
	return projection;
}
bool Vector3D::computeIntersection2D(const Vector3D& v1, const Vector3D& v2, const Vector3D& p1, const Vector3D& p2)
{
	if(v1.x()*v2.y() -v2.x()*v1.y() != 0)
	{
		if(v1.y() != 0)
		{
			setY((-(p1.x()*v1.y()-p1.y()*v1.x())*v2.y() + (p2.x()*v2.y()-p2.y()*v2.x())*v1.y())/(v1.x()*v2.y()-v2.x()*v1.y()));
			setX((p1.x()*v1.y()-p1.y()*v1.x()+v1.x()*y())/v1.y());
		}
		else
		{
			setY((-(p2.x()*v2.y()-p2.y()*v2.x())*v1.y() + (p1.x()*v1.y()-p1.y()*v1.x())*v2.y())/(v2.x()*v1.y()-v1.x()*v2.y()));
			setX((p2.x()*v2.y()-p2.y()*v2.x()+v2.x()*y())/v2.y());
		}
		return true;
	}
	return false;//Parallele
}

//====================================================
// Setter
//====================================================
void Vector3D::set(const Vector3D& a, const Vector3D& b)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] = b.get(i) - a.get(i);
	}
}
void Vector3D::set(const Vector3D& a)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] = a.get(i);
	}
}
void Vector3D::set(int i, float f)
{
	assert(i >= 0 && i < SIZE_V);
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
	if(std::abs(coor[2]) > 0.0001f || std::abs(coor[3]) > 0.0001f)
		std::cout << "set(float, float) au lieu de set2D??";
	//assert(std::abs(coor[2]) < 0.0001f && std::abs(coor[3]) < 0.0001f);
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


//====================================================
// Surchage opérateurs
//====================================================
Vector3D Vector3D::operator-() const
{
	Vector3D vec;
	for(int i=0; i<SIZE_V; i++)
		vec[i] = -coor[i];
	return vec;
}
void Vector3D::operator+=(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] += v.get(i);
	}
}
Vector3D Vector3D::operator+(Vector3D const& v) const
{
	Vector3D vec;
	for(int i=0; i<SIZE_V; i++)
	{
		vec[i] = coor[i] + v.get(i);
	}
	return vec;
}
void Vector3D::operator-=(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		coor[i] -= v.get(i);
	}
}
Vector3D Vector3D::operator-(Vector3D const& v) const
{
	Vector3D vec;
	for(int i=0; i<SIZE_V; i++)
	{
		vec[i] = coor[i] - v.get(i);
	}
	return vec;
}
float Vector3D::operator*(Vector3D const& v) const
{
	float scalar = 0;
	for(int i=0; i<3; i++)
	{
		scalar += coor[i]*v.get(i);
	}
	return scalar;
}
Vector3D Vector3D::operator*(float const& f) const
{
	Vector3D vec;
	for(int i=0; i<3; i++)
	{
		vec[i] = coor[i]*f;
	}
	return vec;
}
Vector3D Vector3D::operator*(Matrix4 const& m4) const
{
	return getTransformation(m4);
}
void Vector3D::operator*=(float const& f)
{
	for(int i=0; i<3; i++)
	{
		coor[i] *= f;
	}
}
void Vector3D::operator*=(Matrix4 const& m4)
{
	Vector3D vec = getTransformation(m4);
	set(vec);
}
Vector3D Vector3D::operator/(float const& f) const
{
	Vector3D vec;
	for(int i=0; i<3; i++)
	{
		vec[i] = coor[i]/f;
	}
	return vec;
}
void Vector3D::operator/=(float const& f)
{
	for(int i=0; i<3; i++)
	{
		coor[i] /= f;
	}
}
Vector3D Vector3D::operator%(Vector3D const& v) const
{
	// cross Product
	Vector3D vec;
	vec[0] = coor[1]*vec.get(2) - coor[2]*vec.get(1);
	vec[1] = coor[2]*vec.get(0) - coor[0]*vec.get(2);
	vec[2] = coor[0]*vec.get(1) - coor[1]*vec.get(0);
	vec[3] = 0;
	return vec;
}

void Vector3D::operator%=(Vector3D const& v)
{
	Vector3D vec = (*this)%v;
	set(vec);
}
float& Vector3D::operator[](int const& i)
{
	assert(i >=0 && i < SIZE_V);
	return coor[i];
}

bool Vector3D::operator==(Vector3D const& v)
{
	for(int i=0; i<SIZE_V; i++)
	{
		float res = (v.get(i)-coor[i]);
		if(std::abs(res) > MIN_DIFF_EQ)
			return false;
	}
	return true;
}

void Vector3D::display()
{
	std::cout << "( ";
	for(int i=0; i<SIZE_V - 1; i++)
	{
		std::cout << coor[i] << ", ";
	}
	std::cout << coor[SIZE_V - 1];
	std::cout << " )\n";

}

float Vector3D::orientation(const Vector3D& p, const Vector3D& q, const Vector3D& r)
{
	return (q.x()*r.y() + p.x()*q.y() + r.x()*p.y()) - (p.x()*r.y() + q.x()*p.y() + r.x()*q.y());
}

bool Vector3D::operator <(const Vector3D& a) const
{
	 std::cout << "Vector3D < ??";
	 return true;
}
