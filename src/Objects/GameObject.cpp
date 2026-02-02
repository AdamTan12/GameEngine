#include "GameObject.h"
#include "../Components/Transform.h"

GameObject::GameObject() {
    transform = new Transform(this);
}
GameObject::~GameObject() {
    delete transform;
    transform = nullptr;
    parent = nullptr;
}