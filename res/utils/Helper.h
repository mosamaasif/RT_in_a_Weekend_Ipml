#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <functional>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385f;

// Utility Functions

inline double degToRad(double degrees) {
	return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double randDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator =
		std::bind(distribution, generator);
	return rand_generator();
}

inline double randDouble(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min) * randDouble();
}

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Common Headers

#include "Ray.h"
#include "Vec3.h"