#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include "Light.h"
#include "Ray.h"
#include "objects/Hittable.h"

class Shader
{
public:
    Shader()
    {
        kd = 1;
        ks = 0;
    }
    vec3 phongShadingModel(Ray ray, Light lightSources[], int noOfLight, Hit &rec)
    {
        vec3 phongValue(0, 0, 0);
        float invPi = 1 / (pi);
        uint32_t i = 0;

        for (; i < noOfLight; i++)
        {
            lightSources[i].direction = lightSources[i].position - rec.point;

            auto surfaceIllumination = glm::max(dot(normalize(rec.normal), normalize(lightSources[i].direction)), 0.0f);
            vec3 diffuse = invPi * rec.color;

            vec3 r = (2 * (dot(normalize(lightSources[i].direction), normalize(rec.normal))) * rec.normal) - lightSources[i].direction;
            vec3 v = -1.0f * (rec.point - ray.origin);
            if (rec.specSize == 0)
            {
                ks = 0;
            }
            float specReflection = (pow(dot(normalize(r), normalize(v)), rec.specSize));
            vec3 spec = lightSources[i].color * specReflection;
            phongValue = phongValue + (lightSources[i].color * surfaceIllumination * ((kd * diffuse) + (ks * spec)));
        }
        return phongValue;
    }

private:
    float kd, ks;
};
#endif