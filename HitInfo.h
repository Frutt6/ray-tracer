//
// Created by marinus on 11/9/26.
//

#ifndef RAY_TRACER_HIT_H
#define RAY_TRACER_HIT_H
#include <glm/glm.hpp>

#include "Material.h"


struct HitInfo {
    bool did_hit = false;
    double distance = 0.0;
    glm::dvec3 hit_point = glm::dvec3();
    glm::dvec3 normal = glm::dvec3();
    Material material = Material();

    HitInfo() = default;
};


#endif //RAY_TRACER_HIT_H
