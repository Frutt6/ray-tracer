#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "Object.h"
#include "Image.h"

class Camera : public Object {
public:
    Camera(const glm::dvec3& position, const glm::dquat& orientation, double fov_degrees, double plane_distance = 1.0);

    [[nodiscard]] Image render_image(int width, int height) const;

private:
    double fov;
    double plane_distance;
};


#endif //RAY_TRACER_CAMERA_H
