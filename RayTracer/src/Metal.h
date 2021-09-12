#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Math::Color& albedo) : m_Albedo(albedo) {}

	virtual bool Scatter(const Ray& rayIn, const Hit_Rec& rec, Math::Color& attenuation, Ray& scattered) const override
	{
		Math::Vector3 reflect = Math::reflect(unitVector(rayIn.direction()), rec.normal);
		scattered = Ray(rec.point, reflect);
		attenuation = m_Albedo;
		return (Math::dot(scattered.direction(), rec.normal) > 0.0f);
	}

private:
	Math::Color m_Albedo;
};