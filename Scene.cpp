#include "Scene.h"
#include <vector>

HitInfo Scene::hit_point(const Ray& ray) const {
    std::vector<HitInfo> hits;

    for (const auto& object : objects) {
        const HitInfo hit_point = object->ray_hit(ray);
        if ( hit_point.did_hit && (!closest_hit.did_hit
            || hit_point.distance < closest_hit.distance)) closest_hit = hit_point;
    }

    return closest_hit;
}