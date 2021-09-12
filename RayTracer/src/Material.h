#pragma once

#include "Ray.h"
#include "Maths.h"

#include "Hittable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const Hit_Rec& rec, Math::Color& attenuation, Ray& scattered) const = 0;
};