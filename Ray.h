#ifndef RAY_H
#define RAY_H
#include "include/glm-0.9.9.8/glm/glm.hpp"

using vec3 = glm::vec3;
class Ray
{
public:
    Ray() {}
    Ray(const vec3 orig, const vec3 dir)
    {
        origin = orig;
        direction = dir;
    }

    vec3 at(float t) const
    {
        return origin + (t * direction);
    }

    vec3 origin;
    vec3 direction;
};

#endif