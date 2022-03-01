#ifndef OBJ_FILE_READER_H
#define OBJ_FILE_READER_H

// OBJ_Loader - .obj Loader
#define TINYOBJLOADER_IMPLEMENTATION
#include "include/tiny_obj_loader.h"
#include "include/glm-0.9.9.8/glm/gtc/matrix_transform.hpp"
#include "objects/Triangle.h"
#include <iostream>
#include <sstream>

using namespace tinyobj;
using vec4 = glm::vec4;
class ObjFileReader
{
public:
    bool loadInoutFile(vector<Triangle> &triangles)
    {

        vector<string> inputs;
        vector<Triangle> object;

        inputs.push_back("C:\\Users\\vasud\\Documents\\Graphics_Code\\Code\\Raycasting\\objFiles\\cube.obj");
        inputs.push_back("C:\\Users\\vasud\\Documents\\Graphics_Code\\Code\\Raycasting\\objFiles\\BMW_M3_GTR.obj");

        tinyobj::ObjReaderConfig reader_config;
        //Path to material file
        reader_config.mtl_search_path = "C:\\Users\\vasud\\Documents\\Graphics_Code\\Code\\Raycasting\\objFiles";
        tinyobj::ObjReader reader;

        for (int i = 0; i < inputs.size(); i++)
        {

            if (!reader.ParseFromFile(inputs.at(i), reader_config))
            {
                if (!reader.Error().empty())
                {
                    std::cerr << "TinyObjReader: " << reader.Error();
                    return false;
                }
                exit(1);
            }

            if (!reader.Warning().empty())
            {
                std::cout << "\nTinyObjReader warning: " << reader.Warning();
            }

            auto &attrib = reader.GetAttrib();
            auto &shapes = reader.GetShapes();
            auto &materials = reader.GetMaterials();

            for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
            {

                vec3 vertex;
                vertex.x = static_cast<const double>(attrib.vertices[3 * v + 0]);
                vertex.y = static_cast<const double>(attrib.vertices[3 * v + 1]);
                vertex.z = static_cast<const double>(attrib.vertices[3 * v + 2]);
                uniqVertices.push_back(vertex);
            }

            //for each shape
            for (size_t i = 0; i < shapes.size(); i++)
            {
                size_t index_offset = 0;

                Triangle triangle;

                //for each face
                for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++)
                {
                    size_t fnum = shapes[i].mesh.num_face_vertices[f];

                    vector<vec3> vertices;
                    vector<vec2> textCoords;
                    // For each vertex in the face
                    for (size_t v = 0; v < fnum; v++)
                    {
                        vec3 vertex;
                        vec3 normal;
                        tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];

                        vertex.x = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                        vertex.y = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                        vertex.z = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                        vertices.push_back(vertex);
                    }

                    int materialId = shapes[i].mesh.material_ids[f];
                    vec3 ka;

                    ka.x = materials[materialId].ambient[0];
                    ka.y = materials[materialId].ambient[1];
                    ka.z = materials[materialId].ambient[2];

                    vec3 kd;
                    kd.x = materials[materialId].diffuse[0];
                    kd.y = materials[materialId].diffuse[1];
                    kd.z = materials[materialId].diffuse[2];

                    vec3 ks;
                    ks.x = materials[materialId].specular[0];
                    ks.y = materials[materialId].specular[1];
                    ks.z = materials[materialId].specular[2];

                    triangle.vertices = vertices;
                    triangle.ka = ka;
                    triangle.kd = kd;
                    triangle.ks = ks;

                    index_offset += fnum;
                    object.push_back(triangle);
                }
            }
            if (i == 0)
            {
                transformObject(object, i, vec4(1.5, 0, 2, 1), 0);
            }
            else
                transformObject(object, i, vec4(-1.5, 0.25, -1, 1), 0);

            triangles.insert(triangles.end(), object.begin(), object.end());
            object.clear();
        }

        cout << "\nNumber of triangles : " << triangles.size();

        return true;
    }

    bool transformObject(vector<Triangle> &triangles, int objType, vec4 translation, float angle)
    {
        glm::mat4x4 transformMat(1.0f), translMat(1.0f), invTranslMat(1.0f), scalMat(1.0f);
        cout << "\nTransformations";
        float rotationAngle = 0;
        vec3 min, max;
        float scaleLength = 1;
        calculateBoundingBox(min, max);
        vec3 center = calcCenter(min, max, scaleLength);
      
        transformMat = glm::rotate(transformMat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        scalMat = glm::scale(glm::mat4(1.0), glm::vec3(1/scaleLength, 1/scaleLength, 1/scaleLength));
        translMat[3] = translation;
        for (int i = 0; i < triangles.size(); i++)
        {
            //apply transform for each vertex in the triangle
            for (int j = 0; j < 3; j++)
            {
                vec4 temp(triangles[i].vertices[j].x, triangles[i].vertices[j].y, triangles[i].vertices[j].z, 1);

                temp = translMat * transformMat * scalMat * temp;
                triangles[i].vertices[j] = vec3(temp.x / temp.w, temp.y / temp.w, temp.z / temp.w);
            }
        }
        return true;
       
    }

    void calculateBoundingBox(vec3 &min, vec3 &max)
    {
        min.x = max.x = uniqVertices.at(0).x;
        min.y = max.y = uniqVertices.at(0).y;
        min.z = max.z = uniqVertices.at(0).z;
        for (vec3 v : uniqVertices)
        {
            if (v.x < min.x)
                min.x = v.x;
            if (v.x > max.x)
                max.x = v.x;
            if (v.y < min.y)
                min.y = v.y;
            if (v.y > max.y)
                max.y = v.y;
            if (v.z < min.z)
                min.z = v.z;
            if (v.z > max.z)
                max.z = v.z;
        }
    }

    vec3 calcCenter(vec3 min, vec3 max, float &scaleLength)
    {
        vec3 center;
        center.x = max.x - min.x;
        center.y = max.y - min.y;
        center.z = max.z - min.z;

        scaleLength = center.z < (center.x < center.y ? center.x : center.y) ? center.z : ((center.x < center.y) ? center.x : center.y);
        std::cout << "\nlength : " << center.x << " " << center.y << " " << center.z;
        if (scaleLength < 1)
            scaleLength = 1;
        center.x = min.x + (center.x / 2);
        center.y = min.y + (center.y / 2);
        center.z = min.z + (center.z / 2);
        return center;
    }

public:
    vector<vec3> uniqVertices;
};
#endif