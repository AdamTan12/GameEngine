#include "GameObject.h"

GameObject::GameObject() {
    transform = new Transform(this);
    name = "GameObject " + std::to_string(Scene::activeScene->objects.size());
    if (Scene::activeScene != nullptr)
        Scene::activeScene->addObject(this);
}
GameObject::~GameObject() {
    parent = nullptr;
    components.clear();
}
vector<Component*> GameObject::allComponents() {
    return components;
}