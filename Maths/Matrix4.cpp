#include "Matrix4.h"

Matrix4::Matrix4(const float* m)
{
	for(int i=0; i<SIZE_M; i++)
	{
		this->m[i] = m[i];
	}
}
Matrix4::Matrix4(const Quaternion& q)
{
	setOrientation(q);
}
Matrix4::Matrix4(const Quaternion& q, const Vector3D& v)
{
	setOrientation(q, v);
}
Matrix4::Matrix4(const Quaternion& q, const Vector3D& v, float factor)
{
	setOrientation(q, v, factor);
}

void Matrix4::set(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] = m4.get(i);
	}
}
Matrix4 Matrix4::copy()
{
	Matrix4 m4;
	m4.set((*this));
	return m4;
}

//====================================================
// Surchage opérateurs
//====================================================
Matrix4 Matrix4::operator+(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i] + m4.get(i);
	}
	return res;
}
void Matrix4::operator+=(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] += m4.get(i);
	}
}
Matrix4 Matrix4::operator-(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i] - m4.get(i);
	}
	return res;
}
void Matrix4::operator-=(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] -= m4.get(i);
	}
}
Matrix4 Matrix4::operator*(const float& f) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i]*f;
	}
	return res;
}
void Matrix4::operator*=(const float& f)
{
	for(int i=0; i<SIZE_M; i++)
	{
		 m[i] *= f;
	}
}
Matrix4 Matrix4::operator*(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<LINE; i++)
	{
		for(int j=0; j<COL; j++)
		{
			int startX = i*COL;
			int y = j;
			res[(j + i*COL)] = 0;
			for(int x=startX; x<startX+COL; x++)
			{
				res[(j + i*COL)] += m[x]*m4.get(y);
				y += COL;
			}
		}
	}
	return res;
}
Vector3D Matrix4::operator*(const Vector3D vec) const
{
	return transform(vec);
}
void Matrix4::operator*=(const Matrix4& m4)
{
	Matrix4 res = (*this)*m4;
	set(res);
}
float& Matrix4::operator[](int i)
{
	assert(i >=0 && i < SIZE_M);
	return m[i];
}

//====================================================
// Getter
//====================================================
float Matrix4::getDeterminant() const
{
	return	m[0]*(m[5]*(m[10]*m[15] - m[14]*m[11]) - m[9]*(m[6]*m[15] - m[7]*m[14]) + m[13]*(m[6]*m[11] - m[10]*m[7])) -
			m[4]*(m[1]*(m[10]*m[15] - m[14]*m[11]) - m[9]*(m[2]*m[15] - m[14]*m[3]) + m[13]*(m[2]*m[11] - m[10]*m[3])) +
			m[8]*(m[1]*(m[6]*m[15]  - m[14]*m[7])  - m[5]*(m[2]*m[15] - m[14]*m[3]) + m[13]*(m[2]*m[7]  - m[6]*m[3]))   -
			m[12]*(m[1]*(m[6]*m[11] - m[10]*m[7])  - m[5]*(m[2]*m[11] - m[10]*m[3]) + m[9]* (m[2]*m[7]  - m[6]*m[3]));
}
Matrix4 Matrix4::getInverse() const
{
	Matrix4 res;
	res[0] = m[6]*m[11]*m[13] - m[7]*m[10]*m[13] + m[7]*m[9]*m[14] - m[5]*m[11]*m[14] - m[6]*m[9]*m[15] + m[5]*m[10]*m[15];
	res[1] = m[3]*m[10]*m[13] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14] + m[1]*m[11]*m[14] + m[2]*m[9]*m[15] - m[1]*m[10]*m[15];
	res[2] = m[2]*m[7]*m[13] - m[3]*m[6]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] + m[1]*m[6]*m[15];
	res[3] = m[3]*m[6]*m[9] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10] + m[1]*m[7]*m[10] + m[2]*m[5]*m[11] - m[1]*m[6]*m[11];
	res[4] = m[7]*m[10]*m[12] - m[6]*m[11]*m[12] - m[7]*m[8]*m[14] + m[4]*m[11]*m[14] + m[6]*m[8]*m[15] - m[4]*m[10]*m[15];
	res[5] = m[2]*m[11]*m[12] - m[3]*m[10]*m[12] + m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] + m[0]*m[10]*m[15];
	res[6] = m[3]*m[6]*m[12] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14] + m[0]*m[7]*m[14] + m[2]*m[4]*m[15] - m[0]*m[6]*m[15];
	res[7] = m[2]*m[7]*m[8] - m[3]*m[6]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] + m[0]*m[6]*m[11];
	res[8] = m[5]*m[11]*m[12] - m[7]*m[9]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] + m[4]*m[9]*m[15];
	res[9] = m[3]*m[9]*m[12] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13] + m[0]*m[11]*m[13] + m[1]*m[8]*m[15] - m[0]*m[9]*m[15];
	res[10]= m[1]*m[7]*m[12] - m[3]*m[5]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] + m[0]*m[5]*m[15];
	res[11]= m[3]*m[5]*m[8] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9] + m[0]*m[7]*m[9] + m[1]*m[4]*m[11] - m[0]*m[5]*m[11];
	res[12]= m[6]*m[9]*m[12] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13] + m[4]*m[10]*m[13] + m[5]*m[8]*m[14] - m[4]*m[9]*m[14];
	res[13]= m[1]*m[10]*m[12] - m[2]*m[9]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] + m[0]*m[9]*m[14];
	res[14]= m[2]*m[5]*m[12] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13] + m[0]*m[6]*m[13] + m[1]*m[4]*m[14] - m[0]*m[5]*m[14];
	res[15]= m[1]*m[6]*m[8] - m[2]*m[5]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] + m[0]*m[5]*m[10];
	float det = getDeterminant();
	if(det != 0)
	{
		res *= 1.0f/det;
		return res;
	}
	else
		return NULL;
}
Matrix4 Matrix4::getTranspose() const
{
	Matrix4 res;
	res.setTranspose((*this));
	return res;
}

//====================================================
// Setter
//====================================================
void Matrix4::setInverse(const Matrix4& m4)
{
	Matrix4 res = m4.getInverse();
	set(res);
}
void Matrix4::setTranspose(const Matrix4& m4)
{
	for(int j=0; j<LINE; j++)
	{
		for(int i=0; i<COL; i++)
		{
			m[(COL - i - 1)*COL + j] = m4.get(i + j*COL);
		}
	}
}
void Matrix4::setOrientation(const Quaternion& q5)
{

}
void Matrix4::setOrientation(const Quaternion& q, const Vector3D& vec)
{

}
void Matrix4::setOrientation(const Vector3D& vec)
{

}
void Matrix4::setOrientation(const Quaternion& q, const Vector3D& vec, float factor)
{

}
void Matrix4::setIdentity(float factor)
{
	m[0] = factor;
	m[1] = m[2] = m[3] = 0;

	m[5] = factor;
	m[4] = m[6] = m[7] = 0;

	m[10] = factor;
	m[8] = m[9] = m[11] = 0;

	m[15] = factor;
	m[12] = m[13] = m[14] = 0;
}
void Matrix4::setIdentity()
{
	setIdentity(1.0f);
}

//====================================================
// Transformations
//====================================================
Vector3D Matrix4::transform(const Vector3D& v) const
{
	Vector3D res;
	for(int i=0; i<LINE; i++)
	{
		res[i] = 0;
		std::cout << "res[" << i << "] = ";
		for(int j=0; j<COL; j++)
		{
			std::cout << " + m[" << (i*COL + j) << "]*" << "v(" << j << ")";
			res[i] += m[i*COL + j]*v.get(j);
		}
		std::cout << "\n";
	}
	return res;
}
void Matrix4::invert()
{
	Matrix4 res = getInverse();
	set(res);
}
void Matrix4::transpose()
{
	Matrix4 res = getTranspose();
	set(res);
}
void Matrix4::changeBasis(const Matrix4& m4)
{
	Matrix4 inv = getInverse();
	(*this) *= (m4*inv);
}

//====================================================
// Create
//====================================================
Matrix4 Matrix4::createIdentity()
{
	Matrix4 res;
	res.setIdentity();
	return res;
}
Matrix4 Matrix4::createRotateX(float theta)
{
	float tab[] = {1.0f, 0, 0, 0,
				0, (float) cos(theta), (float) -sin(theta), 0,
				0, (float) sin(theta), (float) cos(theta), 0,
				0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotateY(float theta)
{
	float tab[] = {(float) cos(theta), 0, (float) sin(theta), 0,
					0, 1.0f, 0, 0,
					(float) -sin(theta), 0, (float) cos(theta), 0,
					0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotateZ(float theta)
{
	float tab[] = { (float) cos(theta), (float) -sin(theta), 0, 0,
					(float)sin(theta), (float) cos(theta), 0, 0,
					0, 0, 1.0f, 0,
					0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotate(const Vector3D& v, float theta)
{
	float c = cos(theta);
	float s = sin(theta);
	float Ax = v.getX();
	float Ay = v.getY();
	float Az = v.getZ();

	float tab[] = {c+(1-c)*Ax*Ax, (1-c)*Ax*Ay - s*Az, (1-c)*Ax*Az + s*Ay, 0,
					(1-c)*Ax*Ay + s*Az, c+(1-c)*Ay*Ay, (1-c)*Ay*Az - s*Ax, 0,
					(1-c)*Ax*Az - s*Ay, (1-c)*Ay*Az + s*Ax, c+(1-c)*Az*Az, 0,
					0,0,0,1.0f};
	return Matrix4(tab);
}

void Matrix4::display()
{
	for(int i=0; i<LINE; i++)
	{
		std::cout << "| ";
		for(int j=0; j<COL-1; j++)
		{
			std::cout << m[i*COL + j] << ", ";
		}
		std::cout << m[i*COL + COL - 1];
		std::cout << " |\n";
	}
}
