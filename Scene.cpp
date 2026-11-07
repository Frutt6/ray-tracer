#include "Scene.h"

std::optional<double> Scene::hit_point(const Ray& ray) const {
    std::optional<double> closest_hit;

    for (const auto& object : objects) {
        if (auto hit_point = object->ray_hit(ray)) {
            if (!closest_hit || *hit_point < *closest_hit) closest_hit = hit_point;
        }
    }

    return closest_hit;
}