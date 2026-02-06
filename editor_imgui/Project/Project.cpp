#include "Project.h"
#include "iostream"

Project::Project() {
    assets = Assets();
    assets.initMeshes();
}
void Project::window() {
    ImGui::Begin("Project");
    for (Mesh* &mesh : assets.meshes) {
        ImGui::Button("button");
        if (ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload("Mesh", &mesh, sizeof(mesh));
            ImGui::Text("MESH");
            ImGui::EndDragDropSource();
        }
    }
    ImGui::End();
}