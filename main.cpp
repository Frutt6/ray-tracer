#include <iostream>
#include <string>
#include <chrono>
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"

constexpr double PI = 3.14159265358979323846;
constexpr double g = 9.81;

int main() {
	Scene scene;

	auto& sphere = scene.emplace<Sphere>(2.0, glm::dvec3(0, 0, 0));
	auto& camera = scene.emplace<Camera>(glm::dvec3(0, 0, -540), glm::dquat(1, 0, 0, 0), 60);

	for (int i = 0; i < 240; i++) {
		auto start = std::chrono::steady_clock::now();

		camera.position += glm::dvec3(0, 0, 2.5); // 60 m/s = 216 km/h
		Image image = camera.render_image(1280,720);
		auto rendered = std::chrono::steady_clock::now();

		std::string filename = "frames/frame" + std::to_string(i) + ".ppm";
		image.write_ppm(filename);
		auto written = std::chrono::steady_clock::now();

		std::chrono::duration<double, std::milli> render_ms = rendered - start;
		std::chrono::duration<double, std::milli> write_ms  = written  - start;
		std::cout << "Frame " << i << " took " << render_ms.count() << " ms to render and " << write_ms.count() << " ms to write.\n";
	}

	return 0;
}