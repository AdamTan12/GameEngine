#include "Details.h"
// forward declarations
void addMeshRenderer(GameObject* currGameObject);

Details::Details() {
    buttonToComponent["MeshRenderer"] = addMeshRenderer;
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
    //display transform
    transform(currGameObject->transform);
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
void addMeshRenderer(GameObject* currGameObject) {
    Mesh* mesh = new Mesh();
    currGameObject->AddComponent<MeshRenderer>()->setMesh(mesh);
}
void Details::transform(Transform* transform) {
    if (transform == nullptr)
        return;
    if (!ImGui::CollapsingHeader("Transform")) {
        ImGui::Text("Position");
        ImGui::Text("x");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##x", &transform->position.x);
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        ImGui::Text("y");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##y", &transform->position.y);
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("z");
        ImGui::SameLine();
        ImGui::PushItemWidth(75);
        ImGui::InputFloat("##z", &transform->position.z);
        ImGui::PopItemWidth();
    }
}
