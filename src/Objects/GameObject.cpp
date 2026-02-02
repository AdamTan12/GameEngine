#include "GameObject.h"

GameObject::GameObject() {
    transform = new Transform(this);
}
GameObject::~GameObject() {
    delete transform;
    transform = nullptr;
    parent = nullptr;
}