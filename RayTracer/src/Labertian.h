#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Math::Color& albedo) : m_Albedo(albedo) {}

	virtual bool Scatter(const Ray& rayIn, const Hit_Rec& rec, Math::Color& attenuation, Ray& scattered) const override
	{
		Math::Vector3 scatterDirection = rec.normal + Math::random_unit_vector();

		if (scatterDirection.near_zero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.point, scatterDirection);
		attenuation = m_Albedo;
		return true;
	}

private:
	Math::Color m_Albedo;
};