#pragma once
#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {

public:
    std::vector<shared_ptr<hittable>> objects;

public:
    hittable_list() = default;
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);

	bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec) const override;

   
};

