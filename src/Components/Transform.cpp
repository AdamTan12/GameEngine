#include "Transform.h"

Transform::Transform() : Component() {
    position = glm::vec2(0, 0);
}
Transform::Transform(GameObject* go) {
    gameObject = go;
    position = glm::vec2(0, 0);
}
Transform::Transform(GameObject* go, Transform* t) {
    gameObject = go;
    transform = this;
    position = glm::vec2(0, 0);
}
Transform::~Transform() {

}