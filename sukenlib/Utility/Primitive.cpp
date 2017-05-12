#include "Primitive.h"
#include <math.h>
#include <DxLib.h>

const float EPSILON = 0.000001f;

suken::Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}

suken::Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

suken::Vector2D::Vector2D(const Twin<float>& vec) :Twin<float>(vec) {}

suken::Vector2D::~Vector2D() {}

bool suken::Vector2D::IsVertical(const Vector2D& vec)const {
	float buf = Dot(vec);
	return (-EPSILON < buf && buf < EPSILON);
}

bool suken::Vector2D::IsParallel(const Vector2D& vec)const {
	float buf = Cross(vec);
	return (-EPSILON < buf && buf < EPSILON);
}

bool suken::Vector2D::IsSharpAngle(const Vector2D& vec)const {
	return (Dot(vec) >= 0.0f);
}

suken::Line2D::Line2D() :p(0.0f, 0.0f),v(1.0f, 0.0f) {}

suken::Line2D::Line2D(const Point2D& p, const Vector2D& v) : p(p), v(v) {}

suken::Line2D::~Line2D() {}

suken::Line2D suken::Line2D::operator+(const Twin<float>& vec)const {
	return Line2D(p + vec, v);
}

suken::Point2D suken::Line2D::GetPoint(float t)const {
	return p + v * t;
}

suken::Segment2D::Segment2D():Line2D() {}

suken::Segment2D::Segment2D(const Point2D& p, const Vector2D& v) : Line2D(p, v) {}

suken::Segment2D::Segment2D(const Point2D& p1, const Point2D& p2) : Line2D(p1, p2 - p1) {}

suken::Segment2D suken::Segment2D::operator+(const Twin<float>& vec)const {
	return Segment2D(p + vec, v);
}

suken::Twin<float> suken::Segment2D::GetEndPoint()const {
	return p + v;
}

suken::Circle2D::Circle2D() :p(0.0f, 0.0f), r(0.5f) {}

suken::Circle2D::Circle2D(const Point2D& p, float r) : p(p), r(r) {}

suken::Circle2D::~Circle2D() {}

suken::Circle2D suken::Circle2D::operator+(const Twin<float>& vec)const {
	return Circle2D(p + vec, r);
}

suken::Capsule2D::Capsule2D() :r(0.5f) {}

suken::Capsule2D::Capsule2D(const Segment2D& s, float r) : s(s), r(r) {}

suken::Capsule2D::Capsule2D(const Point2D& p1, const Point2D& p2, float r) : s(p1, p2), r(r) {}

suken::Capsule2D::~Capsule2D() {}

suken::Capsule2D suken::Capsule2D::operator+(const Twin<float>& vec)const {
	return Capsule2D(s + vec, r);
}

suken::AABB2D::AABB2D() {}

suken::AABB2D::AABB2D(const Point2D& p, const Twin<float>& hl) :p(p), hl(hl) {}

suken::AABB2D::AABB2D(const Vector2D& upperLeft, const Vector2D& lowerRight) {
	p = (upperLeft + lowerRight) / 2;
	hl = (upperLeft - lowerRight) / 2;
	hl.x = fabsf(hl.x);
	hl.y = fabsf(hl.y);
}

float suken::AABB2D::GetLengthX() {
	return (hl.x * 2.0f);
}

float suken::AABB2D::GetLengthY() {
	return (hl.y * 2.0f);
}


bool suken::Hit(Point2D p1, Point2D p2) {
	return (fabsf(p1.x - p1.y) < EPSILON) && (fabsf(p2.x - p2.y) < EPSILON);
}

bool suken::Hit(Segment2D s, Point2D p) {
	Vector2D vecBuf = (p - s.p);
	if (s.v.GetLengthSq() < vecBuf.GetLengthSq()) {
		return false;
	}
	return EPSILON > fabsf(powf(s.v.Dot(vecBuf),2.0f) - s.v.GetLengthSq() * vecBuf.GetLengthSq());
}

bool suken::Hit(Circle2D c, Point2D p) {
	return powf((c.p.x - p.x), 2.0f) + powf((c.p.y - p.y), 2.0f) <= powf(c.r, 2.0f);
}

bool suken::Hit(Circle2D c1, Circle2D c2) {
	return powf((c1.p.x - c2.p.x), 2.0f) + powf((c1.p.y - c2.p.y), 2.0f) <= powf(c1.r + c2.r, 2.0f);
}

bool suken::Hit(Circle2D c, Segment2D s) {
	if (powf(s.v.Cross(c.p - s.p), 2.0f) / s.v.GetLengthSq() > powf(c.r, 2.0f)) {
		return false;
	}
	if (s.v.Dot(c.p - s.p) * s.v.Dot(c.p - s.GetEndPoint()) <= 0) {
		return true;
	}
	return (c.r*c.r > (c.p - s.p).GetLengthSq() || c.r*c.r > (c.p - s.GetEndPoint()).GetLengthSq());
}

void suken::DrawBox(suken::Vector2D upperLeft, suken::Vector2D lowerRight, unsigned int color, bool fillFlag) {
	DxLib::DrawBox((int)upperLeft.x, (int)upperLeft.y, (int)lowerRight.x, (int)lowerRight.y, color, fillFlag);
}

void suken::DrawQuadrangle(suken::Vector2D upperLeft, suken::Vector2D upperRight, suken::Vector2D lowerRight, suken::Vector2D lowerLeft, unsigned int color, bool fillFlag) {
	DxLib::DrawQuadrangle((int)upperLeft.x, (int)upperLeft.y, (int)upperRight.x, (int)upperRight.y, (int)lowerRight.x, (int)lowerRight.y, (int)lowerLeft.x, (int)lowerLeft.y, color, fillFlag);
}