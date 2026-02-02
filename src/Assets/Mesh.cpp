#include "Mesh.h"
using namespace std;
Face::Face() {

};
Face::Face(int i1, int i2, int i3) {
    this->i1 = i1;
    this->i2 = i2;
    this->i3 = i3;
}
Mesh::Mesh() {
    // vertices
    vector<glm::vec3> vertices {
        { -0.5f, -0.5f, -0.5f }, // 0: left-bottom-back
        {  0.5f, -0.5f, -0.5f }, // 1: right-bottom-back
        {  0.5f,  0.5f, -0.5f }, // 2: right-top-back
        { -0.5f,  0.5f, -0.5f }, // 3: left-top-back
        { -0.5f, -0.5f,  0.5f }, // 4: left-bottom-front
        {  0.5f, -0.5f,  0.5f }, // 5: right-bottom-front
        {  0.5f,  0.5f,  0.5f }, // 6: right-top-front
        { -0.5f,  0.5f,  0.5f }
    };
    this->vertices = vertices;

    //indices
    vector<unsigned int> indices {
        // back face (z = -0.5)
        0, 1, 2,
        2, 3, 0,
        // front face (z = +0.5)
        4, 5, 6,
        6, 7, 4,
        // left face (x = -0.5)
        0, 3, 7,
        7, 4, 0,
        // right face (x = +0.5)
        1, 5, 6,
        6, 2, 1,
        // bottom face (y = -0.5)
        0, 1, 5,
        5, 4, 0,
        // top face (y = +0.5)
        3, 2, 6,
        6, 7, 3
    };
    this->indices = indices;
    //faces
    vector<Face> faces;
    for (int i = 0; i < indices.size(); i += 3) {
        int i1 = indices[i];
        int i2 = indices[i + 1];
        int i3 = indices[i + 2];
        Face face(i1, i2, i3);
        glm::vec3 edge1 = vertices[i1] - vertices[i2];
        glm::vec3 edge2 = vertices[i1] - vertices[i3];
        face.norm = glm::cross(edge1, edge2);
        faces.push_back(face);
    }
    this->faces = faces;

    for (int i = 0; i < faces.size(); i ++) {
        Face face = faces[i];
        glm::vec3 edge1 = vertices[face.i2] - vertices[face.i1];
        glm::vec3 edge2 = vertices[face.i3] - vertices[face.i1];
        glm::vec3 edge3 = vertices[face.i3] - vertices[face.i2];
        edges.push_back(edge1);
        edges.push_back(edge2);
        edges.push_back(edge3);
    }
}