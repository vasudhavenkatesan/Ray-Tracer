#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "include/glm-0.9.9.8/glm/glm.hpp"

using namespace glm;
inline double checkValue(double val)
{
    if (val < 0.0)
        return 0;
    else
        return val;
}

void writeColor(std::ostream &out, glm::vec3 color)
{
    out << static_cast<int>(checkValue(255 * color.x)) << ' '
        << static_cast<int>(checkValue(255 * color.y)) << ' '
        << static_cast<int>(checkValue(255 * color.z)) << '\n';
}

#endif