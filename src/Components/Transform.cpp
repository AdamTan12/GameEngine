#include "Transform.h"
#include "../Objects/GameObject.h"

Transform::Transform() : Component() {
    position = glm::vec3(0, 0, 0);
    rotation = glm::quat();
    scale = glm::vec3(1, 1, 1);
}
Transform::Transform(GameObject* go) : Component(gameObject, this) {
    gameObject = go;
    position = glm::vec3(0, 0, 0);
    rotation = glm::quat();
    scale = glm::vec3(1, 1, 1);
}
Transform::Transform(GameObject* go, Transform* t) {
    gameObject = go;
    transform = this;
    position = glm::vec3(0, 0, 0);
    rotation = glm::quat();
    scale = glm::vec3(1, 1, 1);
}
Transform::~Transform() {

}
glm::mat4 Transform::getWorldMatrix() {
    glm::mat4 local = glm::translate(glm::mat4(1.0f), position)
                    * glm::mat4_cast(rotation)
                    * glm::scale(glm::mat4(1.0f), scale);
    GameObject* parent = gameObject->parent;
    while(parent != nullptr) {
        glm::mat4 parentMatrix = glm::translate(glm::mat4(1.0f), parent->transform->position)
                    * glm::mat4_cast(parent->transform->rotation)
                    * glm::scale(glm::mat4(1.0f), parent->transform->scale);
        local = parentMatrix * local;
        parent = parent->parent;
    }
    return local;
}
void Transform::displayComponent() {
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
        #pragma region pos
        ImGui::Text("Position");
        ImGui::Text("x");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##x", &position.x);
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        ImGui::Text("y");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##y", &position.y);
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("z");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##z", &position.z);
        ImGui::PopItemWidth();
        #pragma endregion
        #pragma region scale
        ImGui::Text("Scale");
        ImGui::Text("x");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##xScale", &scale.x);
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        ImGui::Text("y");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##yScale", &scale.y);
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("z");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##zScale", &scale.z);
        ImGui::PopItemWidth();
        #pragma endregion
        #pragma region rotation
        glm::vec3 euler = glm::degrees(glm::eulerAngles(rotation));
        ImGui::Text("Rotation");
        ImGui::Text("x");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##xRot", &euler.x);
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        ImGui::Text("y");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##yRot", &euler.y);
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("z");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##zRot", &euler.z);
        ImGui::PopItemWidth();
        rotation = glm::quat(glm::radians(euler));
        #pragma endregion
    }
}