
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
		std::vector<Vector3D> points = getPointsLocal();
		return new Vector3D((points.at(0).x + points.at(1).x)/2,
							(points.at(0).y + points.at(1).y)/2);
	}
	Vector3D center(true);
	float x0 = 0, y0 = 0, x1 = 0, y1 = 0, signedArea = 0, a = 0;
	std::vector<Vector3D> points = getPointsLocal();
	for(int j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		x0 = points.at(i).x;
		y0 = points.at(i).y;
		x1 = points.at(j).x;
		y1 = points.at(j).y;
		a = x0*y1 - x1*y0;
		signedArea += a;
		center.x += (x0 + x1)*a;
		center.y += (y0 + y1)*a;
	}

	signedArea *= 0.5;
	center.x /= (6.0f*signedArea);
	center.y /= (6.0f*signedArea);

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
	if(size() > 0)
		return points.at(0);
	return Vector3D(true);
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
	Vector3D local = points.at(n);
	float x = orientation.multiplyX(local);
}

float Form::getY(int n) const
{
	assert(n < size());
}

Vector3D Form::get() const
{
	return get(0);
}

Vector3D Form::get(int n) const
{
	assert(n < size());
}

float Form::getCenterX() const
{
}

float Form::getCenterY() const
{
}

Vector3D Form::getCenter() const
{
}

int* Form::getXIntArray() const
{
}

int* Form::getYIntArray() const
{
}

float Form::getMinX() const
{
}

float Form::getMinY() const
{
}

float Form::getMaxX() const
{
}

float Form::getMaxY() const
{
}

Vector3D* Form::getVectorsSatLocal() const
{
}

Vector3D* Form::getVectorsLocal() const
{
}

Vector3D* Form::getVectorsWorld() const
{
}

Vector3D* Form::getPointsLocal() const
{
}

Vector3D* Form::getPointsWorld() const
{
}

Vector3D Form::transform(const Vector3D& vertex, const Vector3D& p,
		const Vector3D& v, const Matrix4& orientation, float& t) const
{
}

Vector3D Form::handleEdgePoint(const Vector3D& PA, const Vector3D& PB,
		const Vector3D& PB2) const
{
}

Vector3D& Form::operator [](int i)
{
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
}

void Form::setPoint(int n, const Vector3D& p)
{
}

void Form::addPointFree(const Vector3D& p)
{
}

void Form::addPoint(const Vector3D& p)
{
}

void Form::removePoint(int i)
{
}

void Form::removeLast()
{
}

Vector3D Form::transformLocalToWorld(const Vector3D& point) const
{
}

Vector3D Form::transformWorldToLocal(const Vector3D& point) const
{
}

void Form::translate(const Vector3D& v)
{
}

void Form::translateX(float x)
{
}

void Form::translateY(float y)
{
}

void Form::rotateDegrees(float omega, const Vector3D& center)
{
}

void Form::rotateRadians(float omega, const Vector3D& center)
{
}

void Form::scaleF(float factor, const Vector3D& center)
{
}

void Form::flipHF(const Vector3D& center)
{
}

void Form::flipVF(const Vector3D& center)
{
}

void Form::setPos(const Vector3D& v)
{
}

void Form::setRadians(float omega)
{
}

void Form::setScale(float scale)
{
}

void Form::setFlipH(bool flipH)
{
}

void Form::setFlipV(bool flipV)
{
}

void Form::calculateSurface()
{
}

bool Form::collisionSat(const Form& form) const
{
}

bool Form::collisionSat(const Form& form, const Vector3D& VA,
		const Vector3D& VB, const Vector3D& push, float& t) const
{
}

bool Form::collisionSatFree(const Form& B, const Vector3D& VA,
		const Vector3D& VB)
{
}

bool Form::intervalIntersectionFree(const Vector3D& axis,
		const Vector3D* pointsA, int sizeA, const Vector3D* pointsB,
		const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI)
{
}

bool Form::collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB,
		const Vector3D& push, float& t)
{
}

bool Form::intervalIntersection(const Vector3D& axis, const Vector3D* pointsA,
		int sizeA, const Vector3D* pointsB, const Vector3D& relPos,
		const Vector3D& relVel, const Matrix4& orientI, AxesSat& axes, float& t)
{
}

bool Form::getInterval(const Vector3D& axis, const Vector3D* points, int size)
{
}

void Form::getPushVector(AxesSat& axesSat, Vector3D& push, float& t)
{
}

bool Form::isConvex() const
{
}

int Form::getClockwise() const
{
}

Edge* Form::getEdgesLocal() const
{
}

void Form::triangulate()
{
}

std::vector<Form> Form::makeMonotone()
{
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
