#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Object.h"
#include "HitInfo.h"

class Sphere : public Object {
public:
    double radius; // in meters

    Sphere(const double radius, const glm::vec3& position,
        const glm::dquat& orientation = glm::quat(1,0,0,0),
        const Material& material = Material(glm::dvec4(1.0)))
        : Object(position, orientation, material), radius(radius) {}

    [[nodiscard]] HitInfo ray_hit(const Ray& ray) const override;
};


#endif //RAY_TRACER_SPHERE_H
