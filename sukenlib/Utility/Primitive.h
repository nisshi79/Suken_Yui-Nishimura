#pragma once

#include "../Manager.h"
#include "../GameEngine/Object/Transform.h"

namespace suken {

	struct Vector2D :public Twin<float> {
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Twin<>& vec);
		~Vector2D();

		bool IsVertical(const Vector2D& vec)const;
		bool IsParallel(const Vector2D& vec)const;
		bool IsSharpAngle(const Vector2D& vec)const;
	};

	struct Line2D {
		Point2D p;
		Vector2D v;
		Line2D();
		Line2D(const Point2D& p, const Vector2D& v);
		~Line2D();

		Line2D operator+(const Twin<float>& vec)const;

		Point2D GetPoint(float t)const;
	};

	struct Segment2D :public Line2D {
		Segment2D();
		Segment2D(const Point2D& p, const Vector2D& v);
		Segment2D(const Point2D& p1, const Point2D& p2);

		Segment2D operator+(const Twin<float>& vec)const;

		Twin<float> GetEndPoint()const;
	};

	struct Circle2D {
		Point2D p;
		float r;

		Circle2D operator+(const Twin<float>& vec)const;

		Circle2D();
		Circle2D(const Point2D& p, float r);
		~Circle2D();
	};

	struct Capsule2D {
		Segment2D s;
		float r;

		Capsule2D operator+(const Twin<float>& vec)const;

		Capsule2D();
		Capsule2D(const Segment2D& s, float r);
		Capsule2D(const Point2D& p1, const Point2D& p2, float r);
		~Capsule2D();
	};

	struct AABB2D{
		Point2D p;
		Twin<float> hl;
		AABB2D();
		AABB2D(const Point2D& p, const Twin<float>& hl);
		AABB2D(const Vector2D& upperLeft, const Vector2D& lowerRight);

		float GetLengthX();
		float GetLengthY();
	};

	bool Hit(Point2D p1, Point2D p2);

	bool Hit(Segment2D s, Point2D p);

	bool Hit(Circle2D c, Point2D p);

	bool Hit(Circle2D c1, Circle2D c2);

	bool Hit(Circle2D c, Segment2D s);

	/**
	*	@brief	’·•ûŒ`•`‰æ
	*/
	void DrawBox(Vector2D upperLeft, Vector2D lowerRight, unsigned int color, bool fillFlag);

	/**
	*	@brief	ŽlŠpŒ`•`‰æ
	*/
	void DrawQuadrangle(Vector2D upperLeft, Vector2D upperRight, Vector2D lowerRight, Vector2D lowerLeft, unsigned int color, bool fillFlag);
}