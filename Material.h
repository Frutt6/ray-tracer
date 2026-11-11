//
// Created by marinus on 11/9/26.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H
#include <glm/glm.hpp>

#include "Image.h"


struct Material {
    glm::dvec4 color; // Unit RGBA

    explicit Material(const glm::dvec4 &color = glm::dvec4(0.0)) : color(color) {}

    [[nodiscard]] Pixel to_pixel() const {
        const auto r = static_cast<uint8_t>(color.r * 255);
        const auto g = static_cast<uint8_t>(color.g * 255);
        const auto b = static_cast<uint8_t>(color.b * 255);

        return Pixel(r, g, b);
    }
};


#endif //RAY_TRACER_MATERIAL_H
