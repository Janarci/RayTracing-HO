#pragma once
#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {

private:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

public:


public:
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec3* vector);


    float getX() const;
    float getY() const;
    float getZ() const;



    vec3& operator*=(const float t);
    vec3 operator*(const vec3 u) const;
    vec3 operator*(const float t) const;


    vec3& operator+=(const vec3& v);
    vec3 operator+(const vec3& v) const;
    vec3 operator+(const float t) const;

    vec3 operator-() const;
    vec3 operator-(const vec3& v) const;
    vec3 operator-(const float t) const;

    vec3 operator/(float t);

    /*
    vec3& operator/=(const float t) {
        return *this *= 1 / t;
    }*/

    float length() const;
    float length_squared() const;


    static vec3 random();
    static vec3 random(float min, float max);

    bool near_zero() const;

    static float dot(const vec3& u, const vec3& v);
    static vec3 cross(const vec3& u, const vec3& v);
    static vec3 unit_vector(vec3 v);
    static vec3 random_in_unit_sphere();
    static vec3 random_unit_vector();

    static vec3 random_in_hemisphere(const vec3& normal);

    static vec3 reflect(const vec3& v, const vec3& n);

    static vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat);

    static vec3 random_in_unit_disk();
};
// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
