#ifndef LIGHT_H
#define LIGHT_H
#include "include/glm-0.9.9.8/glm/glm.hpp"

using vec3 = glm::vec3;
class Light
{
public:
    Light() {}
    Light(const vec3 &pos, const vec3 &col)
    {
        position = pos;
        color = col;
    }

    vec3 position;
    vec3 color;
    vec3 direction;
};
#endif