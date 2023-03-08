#include "vec3.h"

#include "rtweekend.h"

vec3::vec3()
{
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::vec3(const vec3* vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
}

float vec3::getX() const
{
	return this->x;
}

float vec3::getY() const
{
	return this->y;
}

float vec3::getZ() const
{
	return this->z;
}



vec3& vec3::operator*=(const float t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

vec3 vec3::operator*(const vec3 v) const
{
	return vec3(x * v.getX(), y * v.getY(), z * v.getZ());
}

vec3 vec3::operator*(const float t) const
{
	return vec3(x * t, y * t, z * t);

}

vec3& vec3::operator+=(const vec3& v)
{
	x += v.getX();
	y += v.getY();
	z += v.getZ();
	return *this;
}


vec3 vec3::operator+(const vec3& v) const
{
	return vec3(x + v.x, y + v.y, z + v.z);


}

vec3 vec3::operator+(const float t) const
{
	return vec3(x + t, y + t, z + t);

}


vec3 vec3::operator-() const
{
	return vec3(-x, -y, -z);
}

vec3 vec3::operator-(const vec3& v) const
{
	return vec3(x - v.x, y - v.y, z - v.z);

}

vec3 vec3::operator-(const float t) const
{
	return vec3(x - t, y - t, z - t);

}

vec3 vec3::operator/(float t)
{
	return this->operator*(1/t);
}

float vec3::length() const
{
	return sqrt(length_squared());
}

float vec3::length_squared() const
{
	return x * x + y * y + z * z;
}

vec3 vec3::random()
{
	return vec3(rtweekend::random_double(), rtweekend::random_double(), rtweekend::random_double());
}

vec3 vec3::random(float min, float max)
{
	return vec3(rtweekend::random_double(min, max), rtweekend::random_double(min, max), rtweekend::random_double(min, max));

}

bool vec3::near_zero() const
{
	// Return true if the vector is close to zero in all dimensions.
	const auto s = 1e-8;
	return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
}

float vec3::dot(const vec3& u, const vec3& v)
{
	return u.x * v.x
		+ u.y * v.y
		+ u.z * v.z;
}

vec3 vec3::cross(const vec3& u, const vec3& v)
{
	return vec3(u.y * v.z - u.z * v.y,
	            u.z * v.x - u.x * v.z,
	            u.x * v.y - u.y * v.x);
}

vec3 vec3::unit_vector(vec3 v)
{
	return v / v.length();
}

vec3 vec3::random_in_unit_sphere()
{
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

vec3 vec3::random_unit_vector()
{
	return unit_vector(random_in_unit_sphere());
}

vec3 vec3::random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

vec3 vec3::reflect(const vec3& v, const vec3& n)
{
	return v - n * 2 * dot(v, n);
}

vec3 vec3::refract(const vec3& uv, const vec3& n, float etai_over_etat)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp =  (uv + n * cos_theta ) * etai_over_etat;
	vec3 r_out_parallel = n * -sqrt(fabs(1.0 - r_out_perp.length_squared()));
	return r_out_perp + r_out_parallel;
}

vec3 vec3::random_in_unit_disk()
{
	while (true) {
		auto p = vec3(rtweekend::random_double(-1, 1), rtweekend::random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

//
//
//vec3 vec3::operator*(const vec3& v, float t)
//{
//	return v*t;
//}
//
//vec3& vec3::operator+=(const vec3& v)
//{
//	x += v.x;
//	y += v.y;
//	z += v.z;
//	return *this;
//}
//
//vec3 vec3::operator+(const vec3& u, const vec3& v)
//{
//	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
//}
