#include "Sphere.h"
#include <cmath>

HitInfo Sphere::ray_hit(const Ray& ray) const {
    HitInfo hit_info;
    const glm::dvec3 relative_origin = ray.origin - position;

    // Quadratic formula
    const double a = glm::dot(ray.direction, ray.direction);  // should be 1
    const double b = 2 * glm::dot(relative_origin, ray.direction);
    const double c = glm::dot(relative_origin, relative_origin) - radius * radius;

    const double D = b*b - 4 * a * c;  // discriminant
    if (D < 0) return hit_info;
    else hit_info.did_hit = true;

    const double distance1 = (-b + std::sqrt(D)) / (2*a);
    const double distance2 = (-b - std::sqrt(D)) / (2*a);

    if (distance1 > 0)      hit_info.distance = distance1; // nearer
    else if (distance2 > 0) hit_info.distance = distance2; // farther
    else hit_info.did_hit = false;

    hit_info.hit_point = ray.origin + ray.direction * hit_info.distance;
    hit_info.normal = glm::normalize(hit_info.hit_point - position);

    hit_info.material = this->material;

    return hit_info;
}