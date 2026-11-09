//
// Created by marinus on 11/7/26.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H
#include <memory>
#include <utility>

#include "Object.h"
#include "Ray.h"

class Scene {
public:
    template <typename T, typename... Args>
    T& emplace(Args&&... args) {
        auto object = std::make_unique<T>(std::forward<Args>(args)...);
        T& rObject = *object;
        rObject.owner_scene = this;
        objects.push_back(std::move(object));
        return rObject;
    }

    [[nodiscard]] HitInfo hit_point(const Ray& ray) const;

private:
    std::vector<std::unique_ptr<Object>> objects;
};


#endif //RAY_TRACER_SCENE_H
