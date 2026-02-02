#include "MeshRenderer.h"
#include "../Objects/GameObject.h"   
MeshRenderer::MeshRenderer() {}
MeshRenderer::MeshRenderer(Object *p) : Component(p, p->transform) {
}
void MeshRenderer::setMesh(Mesh *mesh) {
    this->mesh = mesh;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);   

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(glm::vec3), mesh->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            mesh->indices.size() * sizeof(unsigned int),
            mesh->indices.data(),
            GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}
void MeshRenderer::Draw(GLuint shaderProgram) {
    if (mesh != nullptr) {
        // u_model
        glm::mat4 model = glm::mat4_cast(transform->rotation);
        model = glm::translate(model, transform->position);
        model = glm::scale(model, transform->scale);

        GLint loc = glGetUniformLocation(shaderProgram, "u_model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
        glDrawElements(GL_TRIANGLES,                  // mode
               mesh->indices.size(),          // count (number of indices)
               GL_UNSIGNED_INT,               // type of index
               0); 

    }
}