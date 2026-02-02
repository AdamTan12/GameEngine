#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include "../Components/Component.h"

using namespace std;

struct GameObject {
    private:
        vector<Component*> components;
    public:
        Transform* transform = nullptr;
        GameObject();
        ~GameObject();
    
};

#endif