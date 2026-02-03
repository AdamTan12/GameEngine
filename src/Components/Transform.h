#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp> 

struct Transform : public Component {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    Transform();
    Transform(GameObject*);
    Transform(GameObject*, Transform*);
    ~Transform();

    glm::mat4 getWorldMatrix();
};

#endif