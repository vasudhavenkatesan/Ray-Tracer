#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "include/glm-0.9.9.8/glm/glm.hpp"

using namespace glm;

void writeColor(std::ostream &out, glm::vec3 color)
{
    out << static_cast<int>(glm::max(0.0f, 255 * color.x)) << ' '
        << static_cast<int>(glm::max(0.0f, 255 * color.y)) << ' '
        << static_cast<int>(glm::max(0.0f, 255 * color.z)) << '\n';
}

#endif