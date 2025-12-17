#pragma once
#include "shape.h"

#include <memory>
#include <vector>

#include "ray.h"

using std::make_shared;
using std::shared_ptr;

class shape_list : public shape {
public:
    std::vector<shared_ptr<shape>> objects;

    shape_list() = default;
    explicit shape_list(const shared_ptr<shape>& object) { add(object); }

    void clear() { objects.clear(); }

    void add(const shared_ptr<shape>& object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, shape_record& rec) const {
        shape_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};
