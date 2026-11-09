#include "Camera.h"
#include "Image.h"
#include "Scene.h"
#include <stdexcept>
#include <cmath>

Camera::Camera(const glm::dvec3& position, const glm::dquat& orientation, double fov_degrees, double plane_distance)
    : Object(position, orientation), fov(fov_degrees), plane_distance(plane_distance) {
    if (!(fov > 0.0f && fov < 180.0f)) throw std::invalid_argument("FOV can't be 0 or a multiple of 180!");
}

Image Camera::render_image(int width, int height) const {
    Image img(width, height);

    float aspect = (float)width / (float)height;
    float plane_height = 2.0f * plane_distance * std::tan(glm::radians(fov) * 0.5f);	// in meters
    float plane_width = plane_height * aspect;	// in meters

    float pixel_width  = plane_width  / (float)width;	// in meters
    float pixel_height = plane_height / (float)height;	// in meters

    // define right, up and forward vectors
    glm::dvec3 right	= orientation * glm::vec3(1, 0, 0);
    glm::dvec3 up		= orientation * glm::vec3(0, 1, 0);
    glm::dvec3 forward	= orientation * glm::vec3(0, 0, 1);

    double z_local = plane_distance;
    for (int px = 0; px < width; px++) {
        for (int py = 0; py < height; py++) {
            double x_local =   pixel_width /2 + pixel_width  * (double)px - plane_width /2;
            double y_local = -(pixel_height/2 + pixel_height * (double)py - plane_height/2);

            glm::dvec3 direction = x_local * right + y_local * up + z_local * forward;
            direction = glm::normalize(direction);

            Ray ray(position, direction);
            if (HitInfo hit_point = get_owner_scene().hit_point(ray); hit_point.did_hit) {
                img.set_pixel(px, py, Pixel(255,0,0));
            }
        }
    }
    return img;
}