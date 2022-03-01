#ifndef CHECKER_H
#define CHECKER_H

#include "../include/glm-0.9.9.8/glm/glm.hpp"

using vec3 = glm::vec3;
using vec2 = glm::vec2;
class Checker
{
public:
    Checker()
    {
        color1 = vec3(1.0, 1.0, 1.0);
        color2 = vec3(0.3, 0.3, 0.3);
    }

    Checker(vec3 col1, vec3 col2)
    {
        color1 = col1;
        color2 = col2;
    }
    vec3 getColor(vec3 iPoint)
    {
        int x = (int)(floor(iPoint.x)) % 2;
        int z = (int)(floor(iPoint.z)) % 2;

        if ((x && z) || (x == 0 && z == 0))
            return color1;
        else
            return color2;
    }

private:
    vec3 color1;
    vec3 color2;
};
#endif