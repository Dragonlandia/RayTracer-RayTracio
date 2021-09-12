#pragma once

#include "Ray.h"
#include "Maths.h"

class Material;

struct Hit_Rec
{
	Math::Point3 point;
	Math::Vector3 normal;
	bool isFrontFace;
	float t;

	std::shared_ptr<Material> m_Materialptr;

	inline void setFaceNormal(const Ray& ray, const Math::Vector3& outwardNormal)
	{
		isFrontFace = Math::dot(ray.direction(), outwardNormal) < 0.0f;
		normal = (isFrontFace ? outwardNormal : -outwardNormal);
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& ray, float tMin, float tMax, Hit_Rec& data) const = 0;
};