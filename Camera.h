#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
const long double pi = acos(-1.L);

class Camera
{
public:
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio)
    {
        auto theta = (vfov * pi) / 180;
        float h = tan(theta / 2);
        float viewport_height = 2.0 * h;
        float viewport_width = aspect_ratio * viewport_height;

        auto w = normalize(lookfrom - lookat);
        auto u = normalize(cross(vup, w));
        auto v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - w;
    }

    Ray get_ray(float s, float t) const
    {
        return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif