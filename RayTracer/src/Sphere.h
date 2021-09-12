#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(const Math::Point3& center, const float& radius, const std::shared_ptr<Material>& material) : 
		m_Center(center), m_Radius(radius), m_Material(material)
	{}

	virtual bool hit(const Ray& ray, float tMin, float tMax, Hit_Rec& data) const override;

private:
	Math::Point3 m_Center;
	float m_Radius;
	std::shared_ptr<Material> m_Material;
};

bool Sphere::hit(const Ray& ray, float tMin, float tMax, Hit_Rec& rec) const
{
	Math::Vector3 oc = ray.origin() - m_Center;
	float a = ray.direction().lengthSquared(); // b * b
	float b_half = Math::dot(oc, ray.direction());
	float c = oc.lengthSquared() - m_Radius * m_Radius; // (A-C)3 - r2

	float discriminant = b_half * b_half - a * c; // t2 - 4 * b*b * (A-C)3 - r2
	if(discriminant < 0.0f) return false;
	float sqrd = std::sqrt(discriminant);

	auto root = (-b_half - sqrd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-b_half + sqrd) / a;
		if (root < tMin || root < tMax)
			return false;
	}

	rec.t = root;
	rec.point = ray.pos(rec.t);
	Math::Vector3 outwardFace = (rec.point - m_Center) / m_Radius;
	rec.setFaceNormal(ray, outwardFace);
	rec.m_Materialptr = m_Material;

	return true;
}
