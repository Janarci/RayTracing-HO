#pragma once
#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {

public:
    double e[3];


public:
    vec3() : e{ 0,0,0 } {}
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;



    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator*=(const double t);
    vec3 operator*(const vec3 u) const;
    vec3 operator*(const double t) const;


    vec3& operator+=(const vec3& v);
    vec3 operator+(const vec3& v) const;
    vec3 operator+(const double t) const;

    vec3 operator-() const;
    vec3 operator-(const vec3& v) const;
    vec3 operator-(const double t) const;

    vec3 operator/(double t);

    /*
    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }*/

    double length() const;
    double length_squared() const;


    static vec3 random();
    static vec3 random(double min, double max);

    bool near_zero() const;

    static double dot(const vec3& u, const vec3& v);
    static vec3 cross(const vec3& u, const vec3& v);
    static vec3 unit_vector(vec3 v);
    static vec3 random_in_unit_sphere();
    static vec3 random_unit_vector();

    static vec3 random_in_hemisphere(const vec3& normal);

    static vec3 reflect(const vec3& v, const vec3& n);

    static vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);

    static vec3 random_in_unit_disk();
};
// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
