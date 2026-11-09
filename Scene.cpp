#include "Scene.h"

HitInfo Scene::hit_point(const Ray& ray) const {
    HitInfo closest_hit;

    for (const auto& object : objects) {
        if (const HitInfo hit_point = object->ray_hit(ray); hit_point.did_hit && (!closest_hit.did_hit
            || hit_point.distance < closest_hit.distance)) closest_hit = hit_point;
    }

    return closest_hit;
}