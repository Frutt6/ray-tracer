#include "Sphere.h"
#include <cmath>

std::optional<double> Sphere::ray_hit(const Ray& ray) const {
    const glm::dvec3 relative_origin = ray.origin - position;

    // Quadratic formula
    const double a = glm::dot(ray.direction, ray.direction);  // should be 1
    const double b = 2 * glm::dot(relative_origin, ray.direction);
    const double c = glm::dot(relative_origin, relative_origin) - radius * radius;

    const double D = b * b - 4 * a * c;  // discriminant
    if (D < 0) return std::nullopt;

    const double distance1 = (-b + std::sqrt(D)) / (2*a);
    const double distance2 = (-b - std::sqrt(D)) / (2*a);

    if (distance1 > 0) return distance1; // nearer
    if (distance2 > 0) return distance2; // farther
    return std::nullopt;
}