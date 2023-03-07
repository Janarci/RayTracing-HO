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
static const double infinity = std::numeric_limits<double>::infinity();
static const double pi = 3.1415926535897932385;

class rtweekend
{
public:

	


	static double degrees_to_radians(double degrees);
	static double clamp(double x, double min, double max);
    static double random_double();
	static double random_double(double min, double max);
};

// Common Headers

#include "ray.h"
#include "vec3.h"


