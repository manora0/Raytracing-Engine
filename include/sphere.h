#pragma once

#include "ray.h"
#include "shape.h"
#include "vec3.h"


struct shape_record;

class sphere : public shape {
    point3 center;
    double radius;

public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}
    bool hit(const ray& r, double ray_tmin, double ray_tmax, shape_record& rec) const override;
};