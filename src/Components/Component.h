#ifndef COMPONENT_H
#define COMPONENT_H

struct GameObject;
struct Transform;
/**
 * base class for everything that is attached to a gameObject
 * defines behaviour that gameObejct can perform
 * a component is always attached to a game object
 */
struct Component {
    // pointer to gameobject that this component is attached to
    GameObject* gameObject = nullptr;
    // pointer to the transform of the gameobject that this component is attached to
    Transform* transform = nullptr;

    Component();
    Component(GameObject*, Transform*);
    virtual ~Component();

};

#endif