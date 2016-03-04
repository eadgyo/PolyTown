
#include "Form.h"

Form::Form():
	Form(0, 1.0f, false, false, 0, Vector3D(true))
{

}

Form::~Form()
{
}

Form::Form(int size):
		Form(0, 1.0f, false, false, 0, Vector3D(true))
{
	points.resize(size);
}

Form::Form(float omega, float scale, bool flipH, bool flipV, float surface, const Vector3D& vec):
		omega(omega), scale(scale), flipH(flipH), flipV(flipV), surface(surface)
{
	orientation.setOrientation(omega, scale, flipH, flipV, vec);
}

Form::Form(const Form& form)
{
	// Copie de convexForms
	convexForms.reserve(form.getConvexFormsSize());
	for(int i=0; i<form.getConvexFormsSize(); i++)
	{
		convexForms.push_back(form.getConvexForms().at(i).clone());
	}

	points.reserve(form.size());
	for(int i=0; i<form.size(); i++)
	{
		points.push_back(form.get(i).copy());
	}

	omega = form.getOmega();
	scale = form.getScale();
	flipH = form.getFlipH();
	flipV = form.getFlipV();
	surface = form.getSurface();

	orientation.setOrientation(omega, scale, flipH, flipV, form.getCenter());
}

Form Form::clone() const
{
	Form form((*this));
	return form;
}


void Form::resetTransformations()
{
	omega = 0;
	scale = 1.0f;
	flipH = false;
	flipV = false;
	surface = false;

	orientation.setOrientation(omega, scale, flipH, flipV, Vector3D(true));
}

void Form::clearTransformations()
{
	resetTransformations();
}

void Form::setInit(Form form)
{
	omega = form.getOmega();
	scale = form.getScale();
	flipH = form.getFlipH();
	flipV = form.getFlipV();
}

const Matrix4& Form::getOrientation() const
{
	return orientation;
}

Matrix4 Form::getOrientationInverse() const
{
	return orientation.getInverse();
}

Vector3D Form::getCentroidWorld() const
{
	return orientation * getCentroidLocal();
}

Vector3D Form::getCentroidLocal() const
{
	if(points.size() == 0)
		return new Vector3D();
	else if(points.size() == 1)
		return getLocal();
	else if(points.size() == 2)
	{

		Vector3D* locals = getPointsLocal();
		std::vector<Vector3D> points(locals, locals + size());
		return new Vector3D((points.at(0).x() + points.at(1).x())/2,
							(points.at(0).y() + points.at(1).y())/2);
	}
	Vector3D center(true);
	float x0 = 0, y0 = 0, x1 = 0, y1 = 0, signedArea = 0, a = 0;
	Vector3D* locals = getPointsLocal();
	std::vector<Vector3D> points(locals, locals + size());
	for(int j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		x0 = points.at(i).x();
		y0 = points.at(i).y();
		x1 = points.at(j).x();
		y1 = points.at(j).y();
		a = x0*y1 - x1*y0;
		signedArea += a;
		center.setX((x0 + x1)*a + center.getX());
		center.setY((y0 + y1)*a + center.getY());
	}

	signedArea *= 0.5;
	center.setX(center.getX() / (6.0f*signedArea));
	center.setY(center.getY() / (6.0f*signedArea));

	return center;
}

float Form::getLocalX() const
{
	if(size() > 0)
		return points.at(0).getX();
	return 0;
}

float Form::getLocalY() const
{
	if(size() > 0)
		return points.at(0).getY();
	return 0;
}

const Vector3D& Form::getLocal() const
{
	assert(size() > 0);
	return points.at(0);
}

float Form::getLocalX(int n) const
{
	assert(n < size());
	return points.at(n).getX();
}

float Form::getLocalY(int n) const
{
	assert(n < size());
	return points.at(n).getY();
}

Vector3D Form::getLocal(int n) const
{
	assert(n < size());
	return points.at(n);
}

float Form::getX() const
{
	return getX(0);
}

float Form::getY() const
{
	return getY(0);
}

float Form::getX(int n) const
{
	assert(n < size());
	return orientation.multiplyX(points.at(n));
}

float Form::getY(int n) const
{
	assert(n < size());
	return orientation.multiplyY(points.at(n));
}

Vector3D Form::get() const
{
	return get(0);
}

Vector3D Form::get(int n) const
{
	assert(n < size());
	Vector3D local = points.at(n);
	Vector3D world = orientation*local;
	return world;
}

float Form::getCenterX() const
{
	return orientation.getX();
}

float Form::getCenterY() const
{
	return orientation.getY();
}

Vector3D Form::getCenter() const
{
	return orientation.getPos();
}

int* Form::getXIntArray() const
{
	// Penser à free le tableau une fois que c'est plus utilisé
	int* l_X = (int*) malloc(size()*sizeof(int));
	for(int i=0; i<points.size(); i++)
	{
		l_X[i] = (int) getX(i);
	}
	return l_X;
}

int* Form::getYIntArray() const
{
	int* l_Y = (int*) malloc(size()*sizeof(int));
	for(int i=0; i<points.size(); i++)
	{
		l_Y[i] = (int) getY(i);
	}
	return l_Y;
}

float Form::getMinX() const
{
	float xMin = getX(0);
	for(int i=1; i<points.size(); i++)
	{
		float x = getX(i);
		if(x < xMin)
			xMin = x;
	}
	return xMin;
}

float Form::getMinY() const
{
	float yMin = getY(0);
	for(int i=1; i<points.size(); i++)
	{
		float y = getY(i);
		if(y < yMin)
			yMin = y;
	}
	return yMin;
}

float Form::getMaxX() const
{
	float xMax = getX(0);
	for(int i=1; i<points.size(); i++)
	{
		float x = getX(i);
		if(x > xMax)
			xMax = x;
	}
	return xMax;
}

float Form::getMaxY() const
{
	float yMax = getY(0);
	for(int i=1; i<points.size(); i++)
	{
		float y = getY(i);
		if(y > yMax)
			yMax = y;
	}
	return yMax;
}

// Penser à liberer lorsque fin d'utilisation du tableau
std::vector<Vector3D> Form::getVectorsSatLocal() const
{
	std::vector<Vector3D> l_vectors;
	for(int j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		Vector3D v(points.at(j), points.at(i));
		l_vectors.push_back(v.getPerpendicular2D());
	}

	//On enleve les vectors colinéaires
	for(int i=0; i<l_vectors.size()-1; i++)
	{
		//Si on est en dessous de 2 vecteurs ca sert à rien de continuer,
		//On sait que ces 2 vecteurs (ou moins) ne sont pas colinéaires
		if(l_vectors.size() < 3)
			break;

		for(int j=i+1; j<l_vectors.size(); j++)
		{
			if(l_vectors.at(i).isColinear2D(l_vectors.at(j)))
			{
				l_vectors.erase(l_vectors.begin() + i);
				i--;
				break;
			}
		}
	}
	return l_vectors;
}

Vector3D* Form::getVectorsLocal() const
{
	Vector3D* l_vectors = (Vector3D*) malloc(size()*sizeof(Vector3D));
	for(int j=size()-1, i=0; i<size(); j=i, i++)
	{
		new (l_vectors[i]) Vector3D(i, Vector3D(points.at(j), points.at(i)));
	}
	return l_vectors;
}

Vector3D* Form::getVectorsWorld() const
{
	Vector3D* l_vectors = getVectorsLocal();
	for(int i=0; i<size(); i++)
	{
		l_vectors[i].set(orientation*l_vectors[i]);
	}
	return l_vectors;
}

Vector3D* Form::getPointsLocal() const
{
	return points.data();
}

Vector3D* Form::getPointsWorld() const
{
	if(orientation.getX() == 0 && orientation.getY() == 0 && omega == 0 && scale == 1.0f && !flipV && !flipH)
		return getPointsLocal();
	Vector3D* l_vectors = (Vector3D*) malloc(size()*sizeof(Vector3D));
	for(int i=0; i<size(); i++)
	{
		new (l_vectors[i]) Vector3D(get(i));
	}
	return l_vectors;
}

Vector3D Form::transform(const Vector3D& vertex, const Vector3D& p,
		const Vector3D& v, const Matrix4& orientation, float& t) const
{
	Vector3D T = p + (orientation*vertex);

	if(t > 0)
		T += (v*t);
	return T;
}

Vector3D Form::handleEdgePoint(const Vector3D& PA, const Vector3D& PB1,
		const Vector3D& PB2) const
{
	Vector3D edgeB(PB1, PB2);
	Vector3D projection(PB1, PB2);
	float fProjection = edgeB*projection;

	return edgeB*fProjection;
}

Vector3D& Form::operator [](int i)
{
	return points[i];
}

void Form::updateCenter()
{
	Vector3D newCenter = getCentroidWorld();
	// Cas NaN, lorsque un flaot est NaN la comparaison avec elle même est toujours fausse
	if(newCenter.x != newCenter.x || newCenter.y != newCenter.y)
	{
		calculateSurface();
		return;
	}

	Matrix4 lastCoor = orientation; //this.center
	Matrix4 newCoor = orientation.copy();
	newCoor.setPos(newCenter);
	Matrix4 inverse = newCoor.getInverse();
	Matrix4 result = inverse*(lastCoor);


	for(int i=0; i<points.size(); i++)
	{
		/*
		result équivaut à ces opérations

		Vector2D p = points.get(i);
		Vector2D pW = orientation.multiply(p);
		Vector2D pN = inverse.multiply(pW);

		*/
		Vector3D vec = result*points.at(i);
		points[i].set(result*points.at(i));
	}
	orientation.setPos(newCenter);

	//update inertia
	calculateSurface();
}

void Form::updateOrientation()
{
	orientation.setOrientation(omega, scale, flipH, flipV);
}

void Form::setCenter(const Vector3D& center)
{
	Vector3D vec(getCenter(), center);
	translate(vec);
}

void Form::setPoint(int n, const Vector3D& p)
{
	assert(n < size());
	points[n].set(orientation.getInverse()*p);
}

void Form::addPointFree(const Vector3D& p)
{
	// Pas d'actualisation du centre
	if(orientation.getDeterminant() != 0)
		points.push_back(orientation.getInverse()*p);
	else
		points.push_back(Vector3D(getCenter(), p));
	convexForms.clear();
}

void Form::addPoint(const Vector3D& p)
{
	addPointFree(p);
	updateCenter();
}

void Form::removePoint(int i)
{
	assert(i < size() && i > 0);
	Vector3D p = points.erase(points.begin() + i);
	convexForms.clear();
	updateCenter();
}

void Form::removeLast()
{
	removePoint(size() - 1);
}

Vector3D Form::transformLocalToWorld(const Vector3D& point) const
{
	return orientation*point;
}

Vector3D Form::transformWorldToLocal(const Vector3D& point) const
{
	Matrix4 inverse = orientation.getInverse();
	return inverse*point;
}

void Form::translate(const Vector3D& v)
{
	orientation.translate(v);
}

void Form::translateX(float x)
{
	orientation.translateX(x);
}

void Form::translateY(float y)
{
	orientation.translateY(y);
}

void Form::rotateDegrees(float omega, const Vector3D& center)
{
	rotateRadians((float) (omega*PI)/180, center);
}

void Form::rotateRadians(float omega, const Vector3D& center)
{
	this->omega += omega;
	orientation.rotateRadiansZFree(omega, center);
	updateOrientation();
}

void Form::scaleF(float factor, const Vector3D& center)
{
	scale *= factor;
	orientation.scale(factor, center);
}

void Form::flipHF(const Vector3D& center)
{
	flipH = !flipH;
	orientation.flipX(center);
}

void Form::flipVF(const Vector3D& center)
{
	flipV = !flipV;
	orientation.flipY(center);
}

void Form::setPos(const Vector3D& v)
{
	assert(v.getW() != 0); // Ce n'est pas un point mais un vecteur
	orientation.setPos(v);
}

void Form::setRadians(float omega)
{
	float f = omega - this->omega;
	this->omega = omega;
	orientation.rotateRadiansZFree(f, Vector3D(true));
	updateOrientation();
}

void Form::setScale(float scale)
{
	float factor = scale/this->scale;
	assert(factor == factor); // Pas de cas NaN
	orientation.scale(factor);
}

void Form::setFlipH(bool flipH)
{
	if(this->flipH != flipH)
	{
		this->flipH = flipH;
		orientation.flipX();
	}
}

void Form::setFlipV(bool flipV)
{
	if(this->flipV != flipV)
	{
		this->flipV = flipV;
		orientation.flipY();
	}
}

void Form::calculateSurface()
{
	surface = 0;
	if(points.size() < 3)
		return;
	for(int i=points.size()-2, i1=points.size()-1, i2=0; i2<points.size(); i=i1, i1=i2, i2++)
	{
		surface += points.at(i1).x()*(points.at(i2).y()-points.at(i).y()) + points.at(i1).y()*(points.at(i).x()-points.at(i2).x());
	}
	surface /= 2;
}

bool Form::collisionSat(Form& form)
{
	if(convexForms.size() == 0)
		updateConvexForms();
	if(form.getConvexForms().size() == 0)
		form.updateConvexForms();

	for(int i=0; i<convexForms.size(); i++)
	{
		Vector3D VA(true);
		Vector3D VB(true);
		if(convexForms.at(i).collisionSatFree(form, VA, VB))
			return true;
	}
	return false;
}

bool Form::collisionSat(Form& form, const Vector3D& VA,
		const Vector3D& VB, const Vector3D& push, float& t)
{
	if(convexForms.size() == 0)
		updateConvexForms();
	if(form.getConvexForms().size() == 0)
		form.updateConvexForms();

	for(int i=0; i<convexForms.size(); i++)
	{
		Vector3D VA(true);
		Vector3D VB(true);
		if(convexForms.at(i).collisionSatA(form, VA, VB, push, t))
			return true;
	}
	return false;
}

bool Form::collisionSatFree(const Form& B, const Vector3D& VA,
		const Vector3D& VB)
{
	Form& A = (*this);

	//Les vecteurs VA et VB sont exprimés dans le repère world
	//Les points PA et PB sont exprimés dans le repères world

	Matrix4 OA = A.getOrientation();
	Matrix4 OB = B.getOrientation();
	Matrix4 OBi = OB.getInverse();
	//La matrice orient permet le passage d'un point du repère local de A à B
	Matrix4 orient = OA*OBi;
	//La matrice orientI permet le passage d'un point du repère local de B à A
	Matrix4 orientI = orient.getInverse();

	Vector3D PA = getCenter();
	Vector3D PB = B.getCenter();

	Vector3D relPos = OBi*(PA-PB);
	Vector3D relVel = OBi*(VA-VB);

	Vector3D* pointsA = getPointsLocal();
	Vector3D* pointsB = B.getPointsLocal();

	std::vector<Vector3D> axisA = getVectorsSatLocal();
	std::vector<Vector3D> axisB = B.getVectorsSatLocal();

	AxesSat axesSat = new AxesSat();

	int sizeA = size();
	int sizeB = B.size();

	float squaredVel = relVel.getSqMagnitude();
	if(squaredVel > 0.000001f)
	{
		if(!intervalIntersectionFree(relVel.getPerpendicular2D(), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}

	for(int i=0; i<axisA.size(); i++)
	{
		if(!intervalIntersectionFree(orient*axisA.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}

	for(int i=0; i<axisB.size(); i++)
	{
		if(!intervalIntersectionFree(axisB.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}
	free(pointsA); free(pointsB);
	return true;
}

bool Form::intervalIntersectionFree(const Vector3D& axis,
		const Vector3D* pointsA, int sizeA, const Vector3D* pointsB, int sizeB,
		const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI) const
{
	Vector3D minMaxA = getInterval(orientI*axis, pointsA, sizeA);
	Vector3D minMaxB = getInterval(axis, pointsB, sizeB);

	//On ajoute le décalage entre les deux repères
	float h = relPos*(axis);
	minMaxA.x += h;
	minMaxA.y += h;

	//On calcule les distances pour determiner le chevauchement
	float d0 = minMaxA.x - minMaxB.y;
	float d1 = minMaxB.x - minMaxA.y;

	if(d0 > 0 || d1 > 0)//Pas de chevauchement
		return false;
	return true;
}

bool Form::collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB,
		const Vector3D& push, float& t) const
{
	Form& A = (*this);

	// Les vecteurs VA et VB sont exprimés dans le repère world
	// Les points PA et PB sont exprimés dans le repères world

	Matrix4 OA = A.getOrientation();
	Matrix4 OB = B.getOrientation();
	Matrix4 OBi = OB.getInverse();
	// La matrice orient permet le passage d'un point du repère local de A à B
	Matrix4 orient = OA*OBi;
	// La matrice orientI permet le passage d'un point du repère local de B à A
	Matrix4 orientI = orient.getInverse();

	Vector3D PA = getCenter();
	Vector3D PB = B.getCenter();

	Vector3D relPos = OBi*(PA-PB);
	Vector3D relVel = OBi*(VA-VB);

	Vector3D* pointsA = getPointsLocal();
	Vector3D* pointsB = B.getPointsLocal();

	std::vector<Vector3D> axisA = getVectorsSatLocal();
	std::vector<Vector3D> axisB = B.getVectorsSatLocal();

	AxesSat axesSat = new AxesSat();

	int sizeA = size();
	int sizeB = B.size();

	float squaredVel = relVel.getSqMagnitude();
	if(squaredVel > 0.000001f)
	{
		if(!intervalIntersection(relVel.getPerpendicular2D(), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}

	for(int i=0; i<axisA.size(); i++)
	{
		if(!intervalIntersection(orient*axisA.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}

	for(int i=0; i<axisB.size(); i++)
	{
		if(!intervalIntersection(axisB.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			free(pointsA); free(pointsB);
			return false;
		}
	}
	free(pointsA); free(pointsB);
	return true;
}

bool Form::intervalIntersection(const Vector3D& axis, const Vector3D* pointsA,
		int sizeA, const Vector3D* pointsB, int sizeB, const Vector3D& relPos,
		const Vector3D& relVel, const Matrix4& orientI, AxesSat& axes, float& t) const
{
	Vector3D minMaxA = getInterval(orientI*axis, pointsA, sizeA);
	Vector3D minMaxB = getInterval(axis, pointsB, sizeB);

	// On ajoute le décalage entre les deux repères
	float h = relPos*axis;
	minMaxA.x += h;
	minMaxA.y += h;

	// On calcule les distances pour determiner le chevauchement
	float d0 = minMaxA.x - minMaxB.y;
	float d1 = minMaxB.x - minMaxA.y;

	if(d0 > 0 || d1 > 0) // Pas de chevauchement
	{
		float fVel = relVel*axis;
		if(std::abs(fVel) > 0.00000001f)
		{
			float t0 =-d0/fVel;
			float t1 = d1/fVel;

			if(t0 > t1) {float temp = t0; t0 = t1; t1 = temp;}
			float l_tAxis = (t0 > 0)? t0:t1;

			if(l_tAxis < 0 || l_tAxis > t)
				return false;

			axes.axesT += (axis);
			axes.tAxesT += (l_tAxis);
			return true;
		}
		return false;
	}
	else
	{
		axes.axes += (axis);
		axes.tAxes += ((d0 > d1)? d0:d1);
		return true;
	}
}

bool Form::getInterval(const Vector3D& axis, const Vector3D* points, int size) const
{
	Vector3D minMax(points[0].getX(), points[0].getY(), 0, true);
	for(int i=1; i<size; i++)
	{
		float scalar = points[i]*axis;
		if(scalar < minMax.x)
		{
			minMax.x = scalar;
		}
		else if(scalar > minMax.y)
		{
			minMax.y = scalar;
		}
	}
	return minMax;
}

void Form::getPushVector(AxesSat& axesSat, Vector3D& push, float& t)
{
	t = 0;
	bool found = false;
	for(int i=0; axesSat.axesT.size(); i++)
	{
		if(axesSat.tAxesT.at(i) > t)
		{
			t = axesSat.tAxesT.at(i);
			push.set(axesSat.axesT.at(i));
			found = true;
		}
	}
	push.normalize();

	if(!found)
	{
		float magnitude1 = axesSat.axes[0].normalize();
		axesSat.tAxes[0] = axesSat.tAxes.at(0)/magnitude1;
		t = axesSat.tAxes[0];
		push.set(axesSat.axes[0]);

		for(int i=1; i<axesSat.axes.size(); i++)
		{
			float magnitude = axesSat.axes[i].normalize();
			axesSat.tAxes[1] = axesSat.tAxes[i]/magnitude;
			if(axesSat.tAxes[i] > t)
			{
				t = axesSat.tAxes[i];
				push.set(axesSat.axes[i]);
				found = true;
			}
		}
	}
}

bool Form::isConvex() const
{
	if(size() < 3)
		return true;
	Vector3D* locals = getVectorsLocal();
	int i=0;
	float crossProductZ = 0;

	while(crossProductZ == 0 && i<size())
	{
		crossProductZ = locals[i]%locals[(i+1)%size()];
		i++;
	}

	for(; i<size(); i++)
	{
		float crossProductZ2 = locals[i]%locals[(i+1)%size()];

		//Si les deux vectoriels z sont de sens différents, alors la forme n'est pas convexe
		if(crossProductZ * crossProductZ2 < 0)
			return false;
	}

	return true;
}

int Form::getClockwise() const
{
	if(size() < 3)
		return 0;
	double sum = 0;
	//float sumInt = 0;
	for(int i=0; i<size(); i++)
	{
		sum = sum + (PI - points.at((i+1)%size()).getAngle(Vector3D(points.at(i), points.at((i+2)%size()))));
	}

	if(PI*2 - 0.001 < std::abs(sum) && std::abs(sum) < 2*PI + 0.001f)
	{
		if(sum < 0)
			return -1;
		return 1;
	}
	else
	{
		return 0;
	}
}

Edge* Form::getEdgesLocal() const
{
	int factor = getClockwise();
	Edge* edges = (Edge*) malloc(size()*sizeof(Edge));
	if(points.size() < 2 || factor == 0)
		return edges;

	PointType* pointsType = (PointType*) malloc(size()*sizeof(PointType));

	if(factor == 1)
	{
		for(int i=size()-1, j=0; i>-1; i--, j++)
		{
			(pointsType[j]) PointType(points.at(i));
			pointsType[j].posPoint = i;
			pointsType[j].posEdge = j;
			pointsType[j].type = -1;
		}
	}
	else
	{
		for(int i=0; i<size(); i++)
		{
			(pointsType[i]) PointType(points.at(i));
			pointsType[i].posPoint = i;
			pointsType[i].posEdge = i;
			pointsType[i].type = -1;
		}
	}

	for(int i=0; i<size(); i++)
	{
		(edges[i]) (Edge());

		edges[i].p0 = pointsType[i];
		edges[i].p1 = pointsType[(i+1)%size()];

		if(i != 0)
		{
			edges[i].prev = edges[i - 1];
			edges[i - 1].next = edges[i];
		}
	}
	edges[0].prev = edges[size() - 1];
	edges[size() - 1].next = edges[0];

	return edges;
}

//--------------------
//	  Triangulate
//--------------------
void Form::triangulate()
{
	convexForms.clear();

	std::vector<Form> monotonesForms = makeMonotone();
	if(monotonesForms.size() != 0)
	{
		for(int i=0; i<monotonesForms.size(); i++)
		{
			convexForms.insert(convexForms.begin(), monotonesForms.begin(), monotonesForms.end());
		}
	}
	else
		convexForms.push_back((*this));
}

//******************
//  Make Monotone
//******************
std::vector<Form> Form::makeMonotone()
{
	Edge* edges = getEdgesLocal();

	std::vector<Form> forms();
	if(size() < 2 || size() == 3)
		return forms;

	//***************
	//Initialization
	//***************
	int sizeV = size();
	int* v = (int) malloc(sizeV*sizeof(int));

	//Scanning line l store Edges colliding with l, sorted by x
	std::map<float, std::vector<Edge>>& l();
	std::vector<Edge> preBufferL();

	//<Edge, PointType>
	std::map<Edge, PointType> helpers();
	std::set<PointType> trash();

	//***************
	//   Sorting
	//***************
	//1) on range par ordre croissant suivant Y les points
	sortPointsY(edges, size(), v, sizeV);

	//***************
	//     Loop
	//***************
	PointType p0, p1, p2;
	//2) On applique une méthode pour chaque point
	int pos = sizeV;
	while(pos > -1)
	{
		Edge edge = edges[pos];

		//On determine le type de point
		p0 = edge.prev.p0;
		p1 = edge.p0;
		p2 = edge.p1;

		trash.insert(p1);

		//On regarde si les 2 segments débutent à partir de ce point
		//ou finissent à partir de ce point
		if(trash.find(p0))
		{
			float minX = edge.prev.getMinX();
			ArrayList<Edge> e = l.get(minX);
			if(e.size() == 1)
			{
				e.clear();
				l.remove(minX);
			}
			else
			{
				e.remove(edge.prev);
			}
		}
		else
			preBufferL.add(edge.prev);

		if(trash.contains(p2))
		{
			float minX = edge.getMinX();
			ArrayList<Edge> e = l.get(minX);
			if(e.size() == 1)
			{
				e.clear();
				l.remove(minX);
			}
			else
			{
				e.remove(edge);
			}
		}
		else
			preBufferL.add(edge);

		//***************
		//     Type
		//***************
		determineType(pos, edges, helpers, l);

		//On ajoute les nouveaux segments stockés dans le prébuffer
		for(int i=0; i<preBufferL.size(); i++)
		{
			float minX = preBufferL.get(i).getMinX();
			if(l.containsKey(minX))
			{
				l.get(minX).add(preBufferL.get(i));
			}
			else
			{
				ArrayList<Edge> e = new ArrayList<Edge>();
				e.add(preBufferL.get(i));
				l.put(minX, e);
			}
		}
		preBufferL.clear();
	}

	free(edges);

	return transformEdges(edges);
}

void Form::sortPointsY(Edge* edges, int sizeE, int* v, int sizeI)
{
}

void Form::determineType(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

Edge Form::getLeftEdge(int pos, Edge* edges, int sizeE,
		std::map<float, std::vector<Edge> >& I)
{
}

Edge Form::getLeftEdge(PointType& p, Edge* lEdges, int sizeE)
{
}

Form* Form::transformEdges(Edge* edges, int sizeE)
{
}

void Form::handleStartVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers)
{
}

void Form::handleSplitVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

void Form::handleMergeVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

void Form::handleRegularVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

int Form::numberLeftEdges(int pos, Edge* edges, int sizeE,
		std::map<float, std::vector<Edge> >& I)
{
}

int Form::numberLeftEdges(PointType& p, Edge* edges, int sizeE)
{
}

std::vector<Form> Form::triangulateMonotone()
{
}

void Form::createChains(int* v, int size, Edge* edges, int sizeE,
		std::set<PointType> lChain)
{
}

std::vector<Form> Form::getTriangulation()
{
}

void Form::setConvex(const std::vector<Form>& forms)
{
}

const std::vector<Form>& Form::getConvexForms() const
{
}

void Form::updateConvexForms()
{
}
