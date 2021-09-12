#pragma once
#include "Util.h"

#include <cmath>
#include <ostream>

namespace Math {

	float sqr(const float& v)
	{
		return v * v;
	}

	class Vector3
	{
	public:
		Vector3() : m_Values{ 0.0f, 0.0f, 0.0f } {}
		Vector3(const float& x, const float& y, const float& z) : m_Values{ x, y, z } {}
		virtual ~Vector3() = default;

		inline float x() { return m_Values[0]; }
		inline float y() { return m_Values[1]; }
		inline float z() { return m_Values[2]; }

		//Vector3& operator-(Vector3& v) {  -v.m_Values[0], -v.m_Values[1], -v.m_Values[2]; }
		float operator[](int index) const { return m_Values[index]; }
		float& operator[](int index) { return m_Values[index]; }

		Vector3& operator+=(const Vector3& v)
		{
			m_Values[0] += v.m_Values[0];
			m_Values[1] += v.m_Values[1];
			m_Values[2] += v.m_Values[2];

			return *this;
		}

		Vector3& operator*=(const float& t)
		{
			m_Values[0] *= t;
			m_Values[1] *= t;
			m_Values[2] *= t;

			return *this;
		}

		Vector3& operator/=(const float& t)
		{
			return *this *= 1 / t;
		}

		float length() const
		{
			return std::sqrt(lengthSquared());
		}

		float lengthSquared() const
		{
			return sqr(m_Values[0]) + sqr(m_Values[1]) + sqr(m_Values[2]);
		}

		bool near_zero() const
		{
			const auto s =  1e-8;
			return (fabs(m_Values[0] < s) && fabs(m_Values[1] < s) && fabs(m_Values[2]) < s);
		}

	public:
		inline static Vector3 random()
		{
			return Vector3(randomFloat(), randomFloat(), randomFloat());
		}

		inline static Vector3 random(const float& min, const float& max)
		{
			return Vector3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
		}

	public:
		float m_Values[3];
	};

	inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
	{
		return out << v.m_Values[0] << ' ' << v.m_Values[1] << ' ' << v.m_Values[2];
	}

	inline Vector3 operator+(const Vector3& v, const Vector3& v2)
	{
		return Vector3(v.m_Values[0] + v2.m_Values[0],
			v.m_Values[1] + v2.m_Values[1],
			v.m_Values[2] + v2.m_Values[2]);
	}

	inline Vector3 operator-(const Vector3& v, const Vector3& v2)
	{
		return Vector3(v.m_Values[0] - v2.m_Values[0],
			v.m_Values[1] - v2.m_Values[1],
			v.m_Values[2] - v2.m_Values[2]);
	}

	inline Vector3 operator*(const Vector3& v, const Vector3& v2)
	{
		return Vector3(v.m_Values[0] * v2.m_Values[0],
			v.m_Values[1] * v2.m_Values[1],
			v.m_Values[2] * v2.m_Values[2]);
	}

	inline Vector3 operator*(const float& t, const Vector3& v)
	{
		return Vector3(t * v.m_Values[0],
			t * v.m_Values[1],
			t * v.m_Values[2]);
	}

	inline Vector3 operator*(const Vector3& v, const float& t)
	{
		return t * v;
	}

	inline Vector3 operator/(const Vector3& v, const float& t)
	{
		return (1.0f / t) * v;
	}

	inline Vector3 operator-(const Vector3& v)
	{
		return Vector3(-v.m_Values[0], -v.m_Values[1], -v.m_Values[2]);
	}

	inline float dot(const Vector3& u, const Vector3& v)
	{
		return u.m_Values[0] * v.m_Values[0] +
			u.m_Values[1] * v.m_Values[1] +
			u.m_Values[2] * v.m_Values[2];
	}

	inline Vector3 cross(const Vector3& v, const Vector3& v2)
	{
		return Vector3(v.m_Values[0] * v2.m_Values[0] - v.m_Values[0] * v2.m_Values[0],
			v.m_Values[1] * v2.m_Values[1] - v.m_Values[1] * v2.m_Values[1],
			v.m_Values[2] * v2.m_Values[2] - v.m_Values[2] * v2.m_Values[2]);
	}

	inline Vector3 unitVector(const Vector3& v)
	{
		return v / v.length();
	}

	Vector3 random_in_unit_sphere()
	{
		while (true)
		{
			auto p = Vector3::random(-1.0f, 1.0f);
			if (p.lengthSquared() >= 1.0f) continue;
			return p;
		}
	}

	Vector3 random_unit_vector()
	{
		return unitVector(random_in_unit_sphere());
	}

	Vector3 random_in_hemisphere(const Vector3& normal)
	{
		Vector3 in_unit_sphere = random_in_unit_sphere();
		if (dot(in_unit_sphere, normal) > 0.0f)
			return in_unit_sphere;
		else
			return -in_unit_sphere;
	}

	Vector3 reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2 * dot(v, n) * n;
	}

	using Point3 = Vector3;
	using Color = Vector3;
}
