#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <memory>
#include <vector>
#include "Hittable.h"

using namespace std;

static const float kInfinity = numeric_limits<float>::max();

class Triangle : public Hittable
{
public:
    Triangle() {}
    Triangle(vector<vec3> vertex, vec3 Ka, vec3 Kd, vec3 Ks, vector<vec2> uvTextureVal)
    {
        vertices = vertex;
        ka = Ka;
        kd = Kd;
        ks = Ks;
        // uvTextCoords = uvTextureVal;
    }

    ~Triangle() {}

    // test triangle ray intersection
    virtual bool intersect(const Ray &r, float t_min, float t_max, Hit &rec, float tNear) const override;

    vector<vec3> vertices; // vertex index array

    vec3 ka;
    vec3 kd;
    vec3 ks;
};

bool Triangle::intersect(const Ray &r, float t_min, float t_max, Hit &rec, float tNear) const
{

    float t, b0, b1, b2;

    // cout << "\nv2" << vertices[2].x << "," << vertices[2].y << "," << vertices[2].z;
    vec3 e1 = vertices[1] - vertices[0];
    vec3 e2 = vertices[2] - vertices[0];
    vec3 e3 = vertices[2] - vertices[1];
    vec3 s = r.origin - vertices[0];
    vec3 temp = cross(r.direction, e2);

    float det = dot(temp, e1);

    float invDet = 1 / det;

    vec3 temp1 = cross(s, e1);
    vec3 temp2 = cross(r.direction, e2);

    t = invDet * dot(temp1, e2);
    b1 = invDet * dot(temp2, s);
    b2 = invDet * dot(temp1, r.direction);
    vec3 normal = cross(e1, e3);

    b0 = 1 - b1 - b2;

    if (b1 >= 0 && b2 >= 0 && (b1 + b2) <= 1 && t > t_min && t < t_max)
    {

        vec3 p = b0 * vertices[0] + b1 * vertices[1] + b2 * vertices[2];

        rec.t = t;
        rec.point = p;
        rec.normal = normal;
        rec.color = kd;
        rec.specSize = 35;

        return true;
    }

    return false;
}
#endif