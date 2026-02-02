#ifndef TRANSFORM_H
#define TRANSFROM_H
#include "Component.h"
#include "glm/glm.hpp"

struct Transform : Component {
    glm::vec2 position;
    Transform();
    Transform(GameObject*);
    Transform(GameObject*, Transform*);
    ~Transform();
};

#endif