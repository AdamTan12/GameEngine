#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "../Objects/GameObject.h"
#include <glad/glad.h>

using namespace std;
struct MeshRenderer;

class Scene {
    public:
        static Scene* activeScene;
        // ------------ UPDATE LISTS ----------------
        vector<GameObject*> objects;
        vector<MeshRenderer*> renderers;
        Scene();
        bool addObject(GameObject* o);
        void updateRenderers(GLuint shader);
};
#endif