#pragma once
#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {

public:
	vec3();

	vec3(float x, float y, float z);
	vec3(const vec3* vector);

	float getX() const;
	float getY() const;
	float getZ() const;

	vec3 operator *(const float num) const;
	vec3 operator *(const vec3 vec) const;
	vec3 operator +(const vec3 vec) const;
	vec3 operator +(float num) const;
	vec3 operator -(const vec3 vec) const;
	vec3 operator -(float num) const;
	vec3 operator -() const;
	vec3 operator /(const vec3 vec) const;
	vec3 operator /(const float num) const;

	float length() const;
	float lengthSquared() const;
	bool nearZero() const;

	static vec3 lerp(const vec3 start, const vec3 end, float delta);
	static vec3 zeros();
	static vec3 ones();
	static float dot(const vec3 u, const vec3 v);
	static vec3 cross(const vec3 u, const vec3 v);
	static vec3 unitVector(const vec3 v);
	static vec3 random();
	static vec3 random(float min, float max);
	static vec3 randomUnitVector();
	static vec3 randomInHemisphere(const vec3 normal);
	static vec3 randomInUnitSphere();
	static vec3 randomInUnitDisk();

	static vec3 reflect(const vec3 v, const vec3 n);
	static vec3 refract(const vec3 uv, const vec3 n, float etaiOverEtat);



private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
