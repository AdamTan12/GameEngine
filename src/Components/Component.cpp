#include "Component.h"

Component::Component() {

}
Component::Component(GameObject* go, Transform* t) {
    gameObject = go;
    transform = t;
}
Component::~Component() {
    gameObject = nullptr;
    transform = nullptr;
}