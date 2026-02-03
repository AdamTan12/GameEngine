#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <string>
#include "../Components/Component.h"
#include "../Components/Transform.h"
#include "../Scenes/Scene.h"

using namespace std;

struct GameObject {
    private:
        vector<Component*> components;
    public:
        string name = "";
        GameObject* parent = nullptr;
        Transform* transform;
        GameObject();
        ~GameObject();
        template<typename T>

    T* AddComponent() {
        static_assert(std::is_base_of<Component, T>::value, "AddComponent<T>: T must inherit from Component");
        T* component = new T(this);
        components.push_back(component);
        
        // Collider* collider = dynamic_cast<Collider*>(component);
        // if (collider) {
        //     CollisionSystem::colliders.push_back(collider);
        // }
        // RigidBody* rigidbody = dynamic_cast<RigidBody*>(component);
        // if (rigidbody) {
        //     CollisionSystem::rigidbodies.push_back(rigidbody);
        // }

        return component;
    };
    template<typename T>
    T* GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "AddComponent<T>: T must inherit from Component");
        for (Component* c : components) {
            if (T* casted = dynamic_cast<T*>(c)) {
                return casted;
            }
        }
        return nullptr;
    }
};

#endif