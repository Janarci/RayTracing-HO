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

vec3::vec3(const vec3* vector)
{
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
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

vec3 vec3::operator*(const float num) const
{
	return vec3(this->x * num, this->y * num, this->z * num);
}

vec3 vec3::operator*(const vec3 vec) const
{
	return vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vec3 vec3::operator+(const vec3 vec) const
{
	return vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

vec3 vec3::operator+(float num) const
{
	return vec3(this->x + num, this->y + num, this->z + num);
}

vec3 vec3::operator-(float num) const
{
	return vec3(this->x - num, this->y - num, this->z - num);
}

vec3 vec3::operator-() const
{
	return vec3(-this->x, -this->y, -this->z);
}

vec3 vec3::operator-(const vec3 vec) const
{
	return vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

vec3 vec3::operator/(const vec3 vec) const
{
	//return vec3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	return zeros();
}

vec3 vec3::operator/(const float num) const
{
	return vec3(this->x, this->y, this->z) * (1 / num);
}

float vec3::length() const
{
	return sqrt(this->lengthSquared());
}

float vec3::lengthSquared() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

bool vec3::nearZero() const
{
	float s = 1e-8;
	return(fabs(this->x) < s && fabs(this->y) < s && fabs(this->z) < s);
}

float vec3::dot(const vec3 u, const vec3 v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec3 vec3::cross(const vec3 u, const vec3 v)
{
	return vec3(u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x);
}

vec3 vec3::unitVector(const vec3 v)
{
	return v / v.length();
}

vec3 vec3::random()
{
	return vec3(rtweekend::random_double(), rtweekend::random_double(), rtweekend::random_double());
}

vec3 vec3::random(float min, float max)
{

	return vec3(rtweekend::random_double(min, max), rtweekend::random_double(min, max), rtweekend::random_double(min, max));
}

vec3 vec3::randomUnitVector()
{
	return unitVector(randomInUnitSphere());
}

vec3 vec3::randomInUnitSphere()
{
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

vec3 vec3::randomInUnitDisk()
{
	while (true) {
		auto p = vec3(rtweekend::random_double(-1, 1), rtweekend::random_double(-1, 1), 0);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

vec3 vec3::randomInHemisphere(const vec3 normal)
{
	vec3 in_unit_sphere = randomInUnitSphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

vec3 vec3::reflect(const vec3 v, const vec3 n)
{
	return v - n * 2 * dot(v, n);
}

vec3 vec3::refract(const vec3 uv, const vec3 n, float etaiOverEtat)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = (uv + n * cos_theta) * etaiOverEtat;
	vec3 r_out_parallel = n * -sqrt(fabs(1.0 - r_out_perp.lengthSquared()));
	return r_out_perp + r_out_parallel;
}

vec3 vec3::lerp(const vec3 start, const vec3 end, float delta)
{
	vec3 v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);
	v.z = start.z * (1.0f - delta) + end.z * (delta);

	return v;
}

vec3 vec3::zeros()
{
	return vec3(0.0f, 0.0f, 0.0f);
}

vec3 vec3::ones()
{
	return vec3(1.0f, 1.0f, 1.0f);
}
//
//
//vec3 vec3::operator*(const vec3& v, double t)
//{
//	return v*t;
//}
//
//vec3& vec3::operator+=(const vec3& v)
//{
//	e[0] += v.e[0];
//	e[1] += v.e[1];
//	e[2] += v.e[2];
//	return *this;
//}
//
//vec3 vec3::operator+(const vec3& u, const vec3& v)
//{
//	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
//}
