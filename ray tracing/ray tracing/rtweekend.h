#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include <cstdlib>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;
// Constants
static const float infinity = std::numeric_limits<float>::infinity();
static const float pi = 3.1415926535897932385;

class rtweekend
{
public:

	


	static float degrees_to_radians(float degrees);
	static float clamp(float x, float min, float max);
    static float random_double();
	static float random_double(float min, float max);
};

// Common Headers

#include "ray.h"
#include "vec3.h"


