#pragma once

#include "Maths.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Math::Point3& rayOrigin, const Math::Vector3& direction) : 
		m_RayOrigin(rayOrigin), m_Direction(direction)
	{}

	Math::Point3 origin() const { return m_RayOrigin; }
	Math::Vector3 direction() const { return m_Direction; }

	Math::Vector3 pos(const float& t) const
	{
		return m_RayOrigin + t * m_Direction;
	}
private:
	Math::Point3 m_RayOrigin;
	Math::Vector3 m_Direction;
};