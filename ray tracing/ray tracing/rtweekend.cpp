#include "rtweekend.h"



float rtweekend::degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0;
}

float rtweekend::clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

float rtweekend::random_double()
{
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0);
}

float rtweekend::random_double(float min, float max)
{
	// Returns a random real in [min,max).
	return min + (max - min) * random_double();
}

