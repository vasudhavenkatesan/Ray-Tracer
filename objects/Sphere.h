#ifndef SPHERE_H
#define SPHERE_H
#include "Hittable.h"
#include <iostream>

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(vec3 cent, float rad, vec3 col)
    {
        center = cent;
        radius = rad;
        color = col;
    }

    ~Sphere() {}

    // test sphere ray intersection
    virtual bool intersect(const Ray &r, float t_min, float t_max, Hit &rec, float tNear) const override;

    // calculate roots of quadratic equation
    bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const;

    vec3 center;
    float radius;
    vec3 color;
};

bool Sphere::intersect(const Ray &ray, float t_min, float t_max, Hit &rec, float tNear) const
{
    float t0, t1;
    vec3 L = ray.origin - center;

    auto a = dot(ray.direction, ray.direction);
    auto b = 2 * dot(L, ray.direction);

    auto c = dot(L, L) - (radius * radius);

    // std::cout << "\na -" << a << " b -" << b << " c -" << c;
    if (!solveQuadratic(a, b, c, t0, t1))
        return false;

    if (t0 > t1)
        std::swap(t0, t1);

    if (t0 < 0)
    {
        t0 = t1;      // if t0 is negative, let's use t1 instead
        return false; // both t0 and t1 are negative
    }

    float d = b * b - 4 * a * c;

    if (t0 < t_min || t_max < t0)
    {
        t0 = (-(b * 0.5) + sqrt(d)) / a;
        if (t0 < t_min || t_max < t0)
            return false;
    }

    rec.t = t0;
    rec.point = ray.at(rec.t);
    rec.normal = (rec.point - center) / radius;
    rec.color = color;
    rec.specSize = 14;
    return true;
}
bool Sphere::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const
{
    float discr = b * b - 4 * a * c;
    if (discr < 0)
        return false;
    else if (discr == 0)
    {
        x0 = x1 = -0.5 * b / a;
    }
    else
    {
        float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }

    return true;
}

#endif