#ifndef HITTABLE_H
#define HITTABLE_H
#include "../include/glm-0.9.9.8/glm/glm.hpp"
#include "../Ray.h"

using vec3 = glm::vec3;
using vec2 = glm::vec2;
struct Hit
{
    vec3 point;
    vec3 normal;
    float t;
    vec3 color;
    int specSize;
};

class Hittable
{
public:
    virtual bool intersect(const Ray &ray, float t_min, float t_max, Hit &hitVal, float tNear) const = 0;
};

#endif