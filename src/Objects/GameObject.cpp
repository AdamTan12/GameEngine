#include "GameObject.h"

GameObject::GameObject() {
    transform = Transform(this);
    if (Scene::activeScene != nullptr)
        Scene::activeScene->addObject(this);
}
GameObject::~GameObject() {
    parent = nullptr;
    components.clear();
}