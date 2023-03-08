#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {

public:
    point3 center;
    float radius;
    std::shared_ptr<material> mat_ptr;

public:
    sphere();
    sphere(point3 cen, float r, std::shared_ptr<material> m);

    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec) const override;


};
