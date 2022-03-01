#ifndef TRIANGLE_MESH_H
#define TRAINGLE_MESH_H

#include "Triangle.h"
class TriangleMesh : public Triangle
{

public:
    TriangleMesh() {}
    TriangleMesh(vector<vec3> vert, vector<vec2> uv)
    {
        objVertices = vert;
        uvTextCoords = uv;
    }

    ~TriangleMesh() {}

    vector<vec3> objVertices;
    vector<vec2> uvTextCoords;
};

#endif