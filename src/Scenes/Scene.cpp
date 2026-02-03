#include "Scene.h"
#include "../Components/Renderers/MeshRenderer.h"
#include <iostream>

Scene* Scene::activeScene = nullptr;
Scene::Scene() {}
bool Scene::addObject(GameObject* o) {
    if (o == nullptr) return false;
    objects.push_back(o);
    return true;
}
void Scene::updateRenderers(GLuint shader) {
    for (MeshRenderer* r : renderers) {
        r->Draw(shader);
    }

}