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
	return vec3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
}

vec3 vec3::operator/(const float num) const
{
	return vec3(this->x / num, this->y / num, this->z / num);
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
	float x = rtweekend::random_double();
	float y = rtweekend::random_double();
	float z = rtweekend::random_double();
	return vec3(x, y, z);
}

vec3 vec3::random(float min, float max)
{
	float x = rtweekend::random_double(min, max);
	float y = rtweekend::random_double(min, max);
	float z = rtweekend::random_double(min, max);

	return vec3(x, y, z);
}

vec3 vec3::randomUnitVector()
{
	return unitVector(randomInUnitSphere());
}

vec3 vec3::randomInUnitSphere()
{
	while (true)
	{
		vec3 p = vec3::random(-1.0f, 1.0f);
		if (p.lengthSquared() >= 1.0f) continue;
		return p;
	}
}

vec3 vec3::randomInUnitDisk()
{
	while (true)
	{
		vec3 p = vec3(rtweekend::random_double(-1.0f, 1.0f), rtweekend::random_double(-1.0f, 1.0f), 0.0f);
		if (p.lengthSquared() >= 1.0f) continue;
		return p;
	}
}

vec3 vec3::randomInHemisphere(const vec3 normal)
{
	vec3 inUnitSphere = randomInUnitSphere();
	if (dot(inUnitSphere, normal) > 0.0f)
	{
		return inUnitSphere;
	}
	else
	{
		return -inUnitSphere;
	}
}

vec3 vec3::reflect(const vec3 v, const vec3 n)
{
	return v - n * 2 * dot(v, n);
}

vec3 vec3::refract(const vec3 uv, const vec3 n, float etaiOverEtat)
{
	float cosTheta = fmin(dot(-uv, n), 1.0f);
	vec3 rPerpendicular = (uv + n * cosTheta) * etaiOverEtat;
	vec3 rParallel = n * -sqrt(fabs(1.0f - rPerpendicular.lengthSquared()));
	return rPerpendicular + rParallel;
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
