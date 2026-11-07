//
// Created by marinus on 11/7/26.
//

#include "Image.h"
#include <fstream>
#include <stdexcept>

Image::Image(const int width, const int height) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("Image width and height must be above 0!");
    resolution = glm::uvec2(width, height);
    data.resize(static_cast<std::size_t>(width) * height);
}

void Image::set_pixel(std::size_t x, std::size_t y, const Pixel &pixel) {
    if (x >= resolution.x || y >= resolution.y) throw std::invalid_argument("The provided point is outside the image!");
    data[y * resolution.x + x] = pixel;
}

void Image::write_ppm(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" << resolution.x << " " << resolution.y << "\n255\n";
    for (const Pixel& p : data) {
        file.put(p.r); file.put(p.g); file.put(p.b);
    }
}