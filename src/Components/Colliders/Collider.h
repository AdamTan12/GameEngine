#ifndef COLLIDER_H
#define COLLIDER_H
#include "glm/glm.hpp"

struct Collider {
    glm::vec2 offset;
    glm::vec2 scale;
    float rotation;
    Collider();
    virtual bool collideWith(Collider* other) = 0;
};
#endif