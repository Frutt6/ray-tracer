#ifndef RAY_TRACER_OBJECT_H
#define RAY_TRACER_OBJECT_H

#include <optional>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Ray.h"

class Scene;

class Object {
public:
    glm::dvec3 position;	// x, y, z in meters
    glm::quat orientation;	// w, x, y, z quaternions

    explicit Object(const glm::dvec3& position,
                    const glm::dquat& orientation = glm::dquat(1,0,0,0))
        : position(position), orientation(orientation) {}

    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    virtual ~Object() = default;

    [[nodiscard]] Scene& get_owner_scene() const { return *owner_scene; }
    [[nodiscard]] virtual std::optional<double> ray_hit(const Ray& ray) const { return std::nullopt; } // no hit by default

private:
    friend class Scene;
    Scene* owner_scene = nullptr;
};


#endif //RAY_TRACER_OBJECT_H
