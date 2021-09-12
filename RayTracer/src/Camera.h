#pragma once

#include "Util.h"
#include "Ray.h"

class Camera
{
public:
	Camera()
	{
		// Camera
		const auto aspectRatio = 16.0f / 9.0f;
		const float viewportHeight = 2.0f;
		const float viewportWidth = aspectRatio * viewportHeight;
		const float focalLength = 1.0f;

		cameraOrigin = Math::Point3(0.0f, 0.0f, 0.0f);
		cameraWidth = Math::Vector3(viewportWidth, 0.0f, 0.0f);
		cameraHeight = Math::Vector3(0.0f, viewportHeight, 0.0f);
		camera_left_corner = cameraOrigin - cameraWidth / 2 - cameraHeight / 2 - Math::Vector3(0.0f, 0.0f, focalLength);
	}

	Ray getRay(float u, float v)
	{
		return Ray(cameraOrigin, camera_left_corner + u * cameraWidth + v * cameraHeight - cameraOrigin);
	}

private:
	Math::Point3 cameraOrigin;
	Math::Vector3 cameraWidth, cameraHeight;
	Math::Vector3 camera_left_corner;

};