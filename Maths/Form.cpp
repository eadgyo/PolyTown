
#include "Form.h"

Form::Form()
{
	// TODO Auto-generated constructor stub

}

Form::~Form()
{
	// TODO Auto-generated destructor stub
}

Form::Form(int size)
{
}

Form::Form(const Form& form)
{
}

Form Form::clone()
{
}

void Form::resetTransformations()
{
}

void Form::clearTransformations()
{
}

void Form::setInit(Form form)
{
}

const Matrix4& Form::getOrientation() const
{
}

Matrix4 Form::getOrientationInverse() const
{
}

Vector3D Form::getCentroidWorld() const
{
}

Vector3D Form::getCentroidLocal() const
{
}

float Form::getLocalX() const
{
}

float Form::getLocalY() const
{
}

const Vector3D& Form::getLocal() const
{
}

float Form::getLocalX(int n) const
{
}

float Form::getLocalY(int n) const
{
}

Vector3D Form::getLocal(int n) const
{
}

float Form::getX() const
{
}

float Form::getY() const
{
}

float Form::getX(int n) const
{
}

float Form::getY(int n) const
{
}

Vector3D Form::get() const
{
}

Vector3D Form::get(int n) const
{
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
}

void Form::updateOrientation()
{
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

const std::vector<Form>& Form::getConvexForms()
{
}

void Form::updateConvexForms()
{
}
