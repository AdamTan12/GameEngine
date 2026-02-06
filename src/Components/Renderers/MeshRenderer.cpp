#include "MeshRenderer.h"
#include <iostream>

MeshRenderer::MeshRenderer() : mesh(nullptr), VAO(0), VBO(0), EBO(0) {}
MeshRenderer::MeshRenderer(GameObject *p) : Component(p, p->transform), mesh(nullptr), VAO(0), VBO(0), EBO(0) {
    if (Scene::activeScene != nullptr)
        Scene::activeScene->renderers.push_back(this);
}
MeshRenderer::~MeshRenderer() {
    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}
void MeshRenderer::setMesh(Mesh *mesh) {
    if (!mesh) return;
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
        // glm::mat4 model = glm::mat4_cast(transform->rotation);
        // model = glm::translate(model, transform->position);
        // model = glm::scale(model, transform->scale);
        glm::mat4 model = transform->getWorldMatrix();
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
void MeshRenderer::displayComponent() {
    if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
        
        ImGui::Text("Mesh");
        ImGui::SameLine();
        string meshName = "meshymeshy";
        if (mesh == nullptr)
            meshName = "Empty";
        ImGui::Button(meshName.c_str());

        if (mesh != nullptr && ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload("Mesh", mesh, sizeof(mesh));
            ImGui::Text("MESH");
            ImGui::EndDragDropSource();
        }
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Mesh")) {
                Mesh* castedMesh = *(Mesh**)payload->Data;
                setMesh(castedMesh);
            }
            ImGui::EndDragDropTarget();
        }
    }
}