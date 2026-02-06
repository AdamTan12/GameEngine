#include "Details.h"
#include <iostream>
// forward declarations
void addMeshRenderer(GameObject* currGameObject);

Details::Details() {
    buttonToComponent["MeshRenderer"] = [](GameObject* obj) {
        obj->AddComponent<MeshRenderer>();
    };
}
void Details::window(GameObject* currGameObject) {
    ImGui::Begin("Details");
    if (currGameObject == nullptr) {
        ImGui::End();
        return;
    }

    // name
    char name[128];
    strcpy(name, currGameObject->name.c_str());
    name[sizeof(name) - 1] = '\0';
    ImGui::Text("Name");
    ImGui::SameLine();
    if (ImGui::InputText("##transform", name, sizeof(name))) {
        currGameObject->name = name;
    }

    // display transform
    if (currGameObject->transform != nullptr) {
        currGameObject->transform->displayComponent();
    }
    for (Component* component : currGameObject->allComponents()) {
        component->displayComponent();
    }
    addComponent(currGameObject);
    ImGui::End();
}
void Details::addComponent(GameObject* currGameObject) {
    if (ImGui::Button("Add Component")) {
        showMap = !showMap;
    }
    if (showMap) {
        ImGui::BeginChild("Components");
        for (const auto& pair : buttonToComponent) {
            if (ImGui::Button(pair.first.c_str())) {
                buttonToComponent[pair.first](currGameObject);
            }
        }
        ImGui::EndChild();
    }
}

