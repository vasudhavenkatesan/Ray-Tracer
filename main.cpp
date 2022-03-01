#include <iostream>
#include <fstream>
#include <memory>
#include <iostream>
#include <typeinfo>

#include "objects/HittableList.h"
#include "objects/Sphere.h"
#include "objects/Plane.h"

#include "Color.h"
#include "Camera.h"
#include "Shader.h"
#include "ObjFileReader.h"

// Function declaration
bool getObjFileValues(string filePath);

enum RayType
{
    PRIMARY_RAY,
    REFLECTION_RAY
};

vec3 ray_color(const Ray &r, const Hittable &objects, Light lights[], float tNear, RayType type, int depth);

using vec3 = glm::vec3;
using vec2 = glm::vec2;
using namespace std;
int main()
{
    cout << "Ray casting implementation";

    //Image options
    const int imageWidth = 400;
    const auto aspectRatio = 16.0 / 9.0;
    const int imageHeight = (int)imageWidth / aspectRatio;

    //setting the camera options
    Camera options(vec3(0, 1, 2), vec3(0, 0, 0), vec3(0, 1, 0), 90, aspectRatio);

    // Light declaration
    Light lights[4];
    Light light0(vec3(-2, 1, 1), vec3(1, 1, 1));
    Light light1(vec3(0, 1, 2), vec3(1, 1, 1));
    Light light2(vec3(2, 0.5, 0.5), vec3(1, 1, 1));

    lights[0] = light0;
    lights[1] = light1;
    lights[2] = light2;

    // Objects
    Sphere sphere1(vec3(2, 1.25, -1.5), 0.65, vec3(0, 1, 0));

    Plane plane(vec3(0, 2, 1), vec3(-1, 0, 0), vec3(0.65, 0, 0.75));

    ObjFileReader objFileReader;
    vector<Triangle> triangles;

    if (!objFileReader.loadInoutFile(triangles))
    {
        cout << "Error reading Obj file";
        exit(0);
    }

    HittableList objects;

    objects.add(make_shared<Plane>(plane));
    objects.add(make_shared<Sphere>(sphere1));

    for (Triangle t : triangles)
    {
        objects.add(make_shared<Triangle>(t));
    }

    // Render
    ofstream out("out1.ppm");
    out << "P3\n"
        << imageWidth << " " << imageHeight << "\n255\n";
    cout << "\nEach ray traced position\n";
    float tNear = kInfinity;
    for (int j = imageHeight - 1; j >= 0; --j)
    {
        for (int i = 0; i < imageWidth; ++i)
        {
            float u = double(i) / (imageWidth - 1);
            float v = double(j) / (imageHeight - 1);
            Ray r = options.get_ray(u, v);

            vec3 color = ray_color(r, objects, lights, tNear, PRIMARY_RAY, 0);
            writeColor(out, color);
        }
    }
    cout << "\nCompleted";

    return 1;
}
vec3 ray_color(const Ray &r, const Hittable &objects, Light lights[], float tNear, RayType type, int depth)
{
    Hit rec;
    Shader phong;
    vec3 color(0);
    switch (type)
    {
    case PRIMARY_RAY:
        if (objects.intersect(r, 0, kInfinity, rec, tNear) && rec.t < tNear)
        {
            tNear = rec.t;
            return phong.phongShadingModel(r, lights, 2, rec);
        }

        color = vec3(0.3, 0.3, 0.3);
        break;
    }

    return color;
}

