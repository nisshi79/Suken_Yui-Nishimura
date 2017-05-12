#pragma once

#include "../../Manager.h"

namespace suken {
	/**
	*	@brief 二次元ベクトル構造体の最終形態
	*/
	template<typename T = float>
	struct Twin {
		T x, y;

		Twin() {
			x = 0;
			y = 0;
		}

		Twin(T x, T y) {
			this->x = x;
			this->y = y;
		}

		template<typename T2>
		operator Twin<T2>() {
			return Twin<T2>((T2)x, (T2)y);
		}

		virtual ~Twin() {}

		Twin<T>& operator=(const Twin<T>& vec) {
			x = vec.x;
			y = vec.y;
			return *this;
		}

		Twin<T> operator+(const Twin<T>& vec)const {
			return Twin<T>(x + vec.x, y + vec.y);
		}

		Twin<T>& operator+=(const Twin<T>& vec) {
			x += vec.x;
			y += vec.y;
			return *this;
		}

		Twin<T> operator-(const Twin<T>& vec)const {
			return Twin<T>(x - vec.x, y - vec.y);
		}

		Twin<T>& operator-=(const Twin<T>& vec) {
			x -= vec.x;
			y -= vec.y;
			return *this;
		}

		Twin<T> operator-()const {
			return Twin<T>(-x, -y);
		}

		Twin<T> operator*(const Twin<T>& vec)const {
			return Twin<T>(x * vec.x, y * vec.y);
		}

		Twin<T>& operator*=(const Twin<T>& vec) {
			x *= vec.x;
			y *= vec.y;
			return *this;
		}

		Twin<T> operator/(const Twin<T>& vec)const {
			return Twin<T>(x / vec.x, y / vec.y);
		}

		Twin<T>& operator/=(const Twin<T>& vec) {
			x /= vec.x;
			y /= vec.y;
			return *this;
		}

		Twin<T> operator*(T arg)const {
			return Twin<T>(x * arg, y * arg);
		}

		Twin<T>& operator*=(T arg) {
			x *= arg;
			y *= arg;
			return *this;
		}

		Twin<T> operator/(T arg)const {
			return Twin<T>(x / arg, y / arg);
		}

		Twin<T>& operator/=(T arg) {
			x /= arg;
			y /= arg;
			return *this;
		}

		void Set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		T Dot(const Twin<T>& vec)const {
			return x*vec.x + y*vec.y;
		}

		T Cross(const Twin<T>& vec)const {
			return x*vec.y - y*vec.x;
		}

		T GetLength()const {
			return sqrtf(x*x + y*y);
		}

		T GetLengthSq()const {
			return x*x + y*y;
		}

		void Norm() {
			const T len = GetLength();
			if (len > 0.0f) {
				x /= len;
				y /= len;
			}
		}

		Twin<T> GetNorm()const {
			const T len = GetLength();
			if (len > 0.0f) {
				return Twin<T>(x / len, y / len);
			}
			return Twin<T>(0.0f, 0.0f);
		}

		Twin<T> Rotation(T rad)const {
			return Twin<T>(x*cosf(rad) - y*sinf(rad), x*sinf(rad) + y*cosf(rad));
		}

		bool IsZero() {
			if (x != 0 || y != 0) {
				return false;
			}
			else {
				return true;
			}
		}
	};

	struct TransformBase {
	public:
		virtual const Twin<float> GetPosition() { return Twin<float>(0, 0); }

		virtual const float GetRotation() { return 0; }

		virtual const Twin<float> GetScale() { return Twin<float>(1, 1); }

		virtual void SetPosition(Twin<float> position) {}

		virtual void SetRotation(float rotation) {}

		virtual void SetScale(Twin<float> scale) {}
	};
	
	struct Transform :TransformBase{
	public:
		Twin<float> position;
		float rotation;
		Twin<float> scale;

		Transform() :position(0, 0), rotation(0), scale(1, 1) {}
		Transform(Twin<float> position, float rotation = 1, Twin<float> scale = Twin<float>(0, 0)) :position(position), rotation(rotation), scale(scale) {}
		Transform(float posX, float posY, float rotation = 1, float scaleX = 1, float scaleY = 1) :position(posX, posY), rotation(rotation), scale(scaleX, scaleY) {}

		const Twin<float> GetPosition() {
			return position;
		}
		const float GetRotation() {
			return rotation;
		}
		const Twin<float> GetScale() {
			return scale;
		}
		void SetPosition(Twin<float> position) { this->position = position; }
		void SetRotation(float rotation) { this->rotation = rotation; }
		void SetScale(Twin<float> scale) { this->scale = scale; }
	};
}