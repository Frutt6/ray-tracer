#ifndef RAY_TRACER_IMAGE_H
#define RAY_TRACER_IMAGE_H

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

struct Pixel {
    std::uint8_t r, g, b;
    Pixel(const std::uint8_t r = 0, const std::uint8_t g = 0, const std::uint8_t b = 0) : r(r), g(g), b(b) {}
};

class Image {
public:
    Image(int width, int height);

    [[nodiscard]] std::size_t get_width()  const { return resolution.x; }
    [[nodiscard]] std::size_t get_height() const { return resolution.y; }

    void set_pixel(std::size_t x, std::size_t y, const Pixel& pixel);
    void write_ppm(const std::string& filename) const;

private:
    glm::uvec2 resolution{};
    std::vector<Pixel> data;
};


#endif //RAY_TRACER_IMAGE_H
