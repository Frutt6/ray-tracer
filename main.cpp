#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"

constexpr double PI = 3.14159265358979323846;
constexpr double g = 9.81;

int main() {
	Scene scene;

	auto& sphere = scene.emplace<Sphere>(2.0, glm::dvec3(0, 0, 4));
	auto& camera = scene.emplace<Camera>(glm::dvec3(0, 0, 0), glm::dquat(1, 0, 0, 0), 90);

	Image image = camera.render_image();

	image.write_ppm("output.ppm");

	return 0;
}