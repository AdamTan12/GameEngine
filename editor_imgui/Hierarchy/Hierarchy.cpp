#include "Hierarchy.h"

void Hierarchy::window() {
    ImGui::Begin("Hierarchy");
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Add New GameObject")) {
            GameObject* go = new GameObject();
            //go->AddComponent<MeshRenderer>()->setMesh(new Mesh());
        }
        ImGui::EndPopup();
    }
    for (GameObject* go : Scene::activeScene->objects) {
        bool isSelected = go == currGameObject;
        if (ImGui::Selectable(go->name.c_str(), isSelected)) {
            currGameObject = go;
        }
    }
    ImGui::End();
}
GameObject* Hierarchy::getSelectedGameObject() {
    return currGameObject;
}