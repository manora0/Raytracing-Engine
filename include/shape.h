#pragma once
#include "ray.h"

struct shape_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Outward_normal should be a unit vector
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    };
};

class shape {
public:
    virtual ~shape()=default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, shape_record& rec) const = 0;
};
