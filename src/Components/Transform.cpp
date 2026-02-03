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