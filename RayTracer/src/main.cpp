#include <iostream>
#include <cmath>

#include "Util.h"
#include "Math.h"
#include "Color.h"
#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"

#include "Material.h"
#include "Metal.h"
#include "Labertian.h"

// Hittable
#include "Sphere.h"

Math::Color rayColor(const Ray& ray, const Hittable& world, int depth)
{
	Hit_Rec rec;

	if (depth <= 0)
		return Math::Color(0.0f, 0.0f, 0.0f);

	if (world.hit(ray, 0.0f, infinity, rec))
	{
		Ray scattered;
		Math::Color attenuation;
		if (rec.m_Materialptr->Scatter(ray, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);
		return Math::Color(0.0f, 0.0f, 0.0f);
	}

	Math::Vector3 unitDirection = unitVector(ray.direction());
	auto t = 0.5f * (unitDirection.y() + 1.0f);
	return (1.0f - t) * Math::Color(1.0f, 1.0f, 1.0f) + t * Math::Color(0.2f, 0.1f, 0.8f);
}

int main()
{
	// Image
	const float aspectRatio = 16.0f / 9.0f;
	const int imageWidth = 720;
	const int imageHeight = imageWidth / aspectRatio;
	const int samplesPerPixel = 500;
	const int maxDepth = 50;

	// World
	auto groundMaterial = std::make_shared<Lambertian>(Math::Color(0.3f, 1.0f, 0.2f));
	auto leftSphereMaterial = std::make_shared<Metal>(Math::Color(0.9f, 0.9f, 0.3f));
	auto centerSphereMaterial = std::make_shared<Metal>(Math::Color(1.0f, 1.0f, 1.0f));
	auto rightSphereMaterial = std::make_shared<Metal>(Math::Color(0.8f, 0.1f, 0.2f));

	HittableList world;
	world.Add(std::make_shared<Sphere>(Math::Point3(0.0f, -100.5f, -1.0f), 100.0f, groundMaterial));
	world.Add(std::make_shared<Sphere>(Math::Point3(0.0f, 0.0f, -1.0f), 0.3f, leftSphereMaterial));
	world.Add(std::make_shared<Sphere>(Math::Point3(0.0f, 0.5f, -1.0f), 0.2f, centerSphereMaterial));
	world.Add(std::make_shared<Sphere>(Math::Point3(0.0f, 1.0f, -1.0f), 0.2f, rightSphereMaterial));

	// Camera
	Camera camera;

	// Render
	// Adding support for .bmp
	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int y = imageHeight - 1; y >= 0; y--)
	{
		std::cerr << "\rScanlines Remaining: " << y << ' ' << std::flush;
		for (int x = 0; x < imageWidth; x++)
		{
			Math::Color pixelColor(0.0f, 0.0f, 0.0f);
			for (int i = 0; i < samplesPerPixel; i++)
			{
				auto u = float(x + randomFloat()) / (imageWidth - 1);
				auto v = float(y + randomFloat()) / (imageHeight - 1);

				Ray ray = camera.getRay(u, v);
				pixelColor += rayColor(ray, world, maxDepth);
			}
			writePixel(std::cout, pixelColor, samplesPerPixel);
		}
	}
	std::cerr << "\nDone\n";
}