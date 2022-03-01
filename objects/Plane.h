#ifndef PLAN_H
#define PLANE_H

#include "Hittable.h"
#include "../textures/Checker.h"
class Plane : public Hittable
{
public:
    Plane() {}
    Plane(vec3 norm, vec3 R, vec3 col)
    {
        normal = norm;
        r = R;
        color = col;
    }

    ~Plane() {}

    // test plane ray intersection
    virtual bool intersect(const Ray &r, float t_min, float t_max, Hit &rec, float tNear) const override;

    vec3 normal;
    vec3 r;
    vec3 color;
};

bool Plane::intersect(const Ray &ray, float t_min, float t_max, Hit &rec, float tNear) const
{
    float d = dot(normal, ray.direction);
    Checker checker;

    if (abs(d) > 0)
    {
        float t = (dot(r - ray.origin, normal)) / d;
        if (t >= 0)
        {
            rec.t = t;
            rec.point = ray.origin + (t * ray.direction);
            // std::cout << "\nPlane " << rec.point.x << "," << rec.point.y << "," << rec.point.z;
            rec.normal = normal;
            rec.color = checker.getColor(rec.point);
            rec.specSize = 0;
            return true;
        }
    }
    return false;
}
#endif