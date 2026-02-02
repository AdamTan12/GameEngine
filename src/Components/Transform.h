#ifndef TRANSFORM_H
#define TRANSFROM_H
#include "Component.h"
#include "glm/glm.hpp"

struct Transform : public Component {
    glm::vec2 position;
    Transform();
    Transform(GameObject*);
    Transform(GameObject*, Transform*);
    ~Transform();
};

#endif