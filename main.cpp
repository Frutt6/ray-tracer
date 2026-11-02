#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

constexpr double PI = 3.14159265358979323846;
constexpr double g = 9.81f;

struct Pixel {
	std::uint8_t r, g, b;

	Pixel(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0) : r(r), g(g), b(b) {}
};

class Image {
public:
	Image(int width, int height)
		: resolution(glm::uvec2(validate_dimension(width), validate_dimension(height))), data(width * height) {}

	[[nodiscard]] size_t get_width()  const { return resolution.x; }
	[[nodiscard]] size_t get_height() const { return resolution.y; }

	void set_pixel(const glm::uvec2 point, const Pixel& pixel) {
		at(point) = pixel;
	}
	void set_pixel(const size_t x, const size_t y, const Pixel& pixel) { set_pixel( glm::uvec2(x, y), pixel); }

	Pixel& at(const glm::uvec2 point) {
		std::cout << "Pixel at " << point.x << " " << point.y << std::endl;
		if (point.x >= resolution.x || point.y >= resolution.y) throw std::invalid_argument("The provided point is outside the image!");
		return data[index(point)];
	}
	Pixel& at(const size_t x, const size_t y) { return at(glm::uvec2(x, y)); }
		
	void write_ppm(const std::string& filename) const {
		std::ofstream file(filename, std::ios::binary);
		file << "P6\n" << resolution.x << " " << resolution.y << "\n255\n";
		for (const Pixel& pixel : data) {
			file.put(pixel.r); file.put(pixel.g); file.put(pixel.b);
		}
	}
	
private:
	glm::uvec2 resolution;
	std::vector<Pixel> data;

	static size_t validate_dimension(const size_t value) {
		if (value <= 0) throw std::invalid_argument("Image width and height must be above 0!");
		return value;
	}

	[[nodiscard]] size_t index(const glm::uvec2 point) const { return point.y * resolution.x + point.x; }
};

class Camera {
public:
	glm::vec3 position; // x,y,z (in meters)
	glm::quat orientation; // quaternions

	Camera(glm::vec3 position, glm::quat orientation, float field_of_view, float plane_distance = 1)
	   	: position(position), orientation(orientation), fov(field_of_view), plane_distance(plane_distance) {}

	void set_fov(float field_of_view) { // (field_of_view in degrees)
		fov = field_of_view;
	}
	void set_plane_dis(float plane_dis) { // (plane_distance in meters)
		plane_distance = plane_dis;
	}

	[[nodiscard]] float get_fov() 		const { return fov; }
	[[nodiscard]] float get_plane_dis()	const { return plane_distance; }

	[[nodiscard]] Image render_image(int width, int height) const {
		Image img(width, height);

		float aspect = (float)width / (float)height;
		float plane_height = 2.0f * plane_distance * std::tan(glm::radians(fov) * 0.5f);	// in meters
		float plane_width = plane_height * aspect;	// in meters

		float pixel_width  = plane_width  / (float)width;	// in meters
		float pixel_height = plane_height / (float)height;	// in meters

		// define right, up and forward vectors
		glm::vec3 right		= orientation * glm::vec3(1, 0, 0);
		glm::vec3 up		= orientation * glm::vec3(0, 1, 0);
		glm::vec3 forward	= orientation * glm::vec3(0, 0, 1);

		float z_local = plane_distance;
		for (int px = 0; px < width; px++) {
			for (int py = 0; py < height; py++) {
				float x_local =   pixel_width /2 + pixel_width  * (float)px - plane_width /2;
				float y_local = -(pixel_height/2 + pixel_height * (float)px - plane_height/2);

				glm::vec3 dir = x_local * right + y_local * up + z_local * forward;

				// ray step loop
				img.set_pixel(px, py, Pixel((float)px / width * 255, (float)py / height * 255,0));
			}
		}
		return img;
	}
	[[nodiscard]] Image render_image(const glm::ivec2 resolution) const { return render_image(resolution.x, resolution.y); }

private:
	float fov; // Field of view (in degrees)
	float plane_distance; // (in meters)

	static float check_fov(float field_of_view) {
		if (!(field_of_view > 0.0f && field_of_view < 180.0f)) throw std::invalid_argument("FOV can't be 0 or a multiple of 180!");
		return field_of_view;
	}
};

class Object {
public:
	Object(glm::vec3 position, glm::vec3 velocity = glm::vec3(0,0,0), glm::vec3 net_force = glm::vec3(0,0,0), glm::quat orientation = glm::quat(1,0,0,0), float mass = 1.0f)
		: position(position), velocity(velocity), net_force(net_force), orientation(orientation), mass(mass) {}

	[[nodiscard]] glm::dvec3 get_position() const { return position; }
	[[nodiscard]] glm::dvec3 get_velocity() const { return velocity; }
	[[nodiscard]] glm::dvec3 get_net_force() const { return net_force; }
	[[nodiscard]] glm::quat get_orientation() const { return orientation; }

	void apply_force(const glm::dvec3& force) {
		net_force = net_force + force;
	}

	void tick(const double delta_time) {
		apply_force(mass * glm::dvec3(0.0f, -g, 0.0f));	// apply gravity

		glm::dvec3 acceleration = net_force / mass;
		velocity += acceleration * delta_time;
		position += velocity * delta_time;
	}
	void tick(const float delta_time) {tick((double)delta_time);}

private:
	glm::dvec3 position;	// in meters
	glm::dvec3 velocity;	// in meters per second
	glm::dvec3 net_force;	// in Newtons
	glm::quat orientation;	// quaternions

	double mass;			// in kilograms
};

int main() {
	Camera camera(glm::vec3(0,0,0),glm::quat(1,0,0,0),90);

	glm::ivec2 p720(1280, 720);
	Image img = camera.render_image(p720);
	img.write_ppm("output.ppm");

	return 0;
}