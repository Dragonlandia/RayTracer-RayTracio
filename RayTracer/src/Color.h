#pragma once

#include "Maths.h"

void writePixel(std::ostream& out, Math::Color pixelColor, const int& samplesPerPixel)
{
	float r = pixelColor.x();
	float g = pixelColor.y();
	float b = pixelColor.z();

	auto scale = 1.0f / samplesPerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	out << static_cast<int>(256.0f * clamp(r, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(256.0f * clamp(g, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(256.0f * clamp(b, 0.0f, 0.999f)) << '\n';
}