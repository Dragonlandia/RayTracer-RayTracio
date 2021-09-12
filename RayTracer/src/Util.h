#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <cmath>
#include <limits>

#include <random>

#define RANDOM_MAX_VALUE 100.0f

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

const float degreesToRadians(const float& deegres)
{
	return deegres * pi / 180.0f;
}

inline float randomFloat()
{
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	static std::mt19937 randomEngine;
	return distribution(randomEngine);
}

inline float randomFloat(const float& min, const float& max)
{
	return min + (max - min) * randomFloat();
}

const float clamp(const float& x, const float& min, const float& max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}