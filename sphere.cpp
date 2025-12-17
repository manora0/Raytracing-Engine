#include "sphere.h"
#include "ray.h"
#include "vec3.h"

bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, shape_record& rec) const {
    // from the equation (P - C) dot (P - C) = r^2 where P is a point and C is camera center
    // if the discriminant is above zero, it passes through the circle that many times
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto b = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = b*b - a*c;

    if (discriminant < 0) {
        return false;
    }

    // finds the nearest point to render
    auto root = (b - std::sqrt(discriminant)) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (b + std::sqrt(discriminant)) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    const vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    return true;
}