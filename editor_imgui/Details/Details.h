#ifndef DETAILS_H
#define DETAILS_H
#include <unordered_map>
#include <string>
#include "../../external/imgui-docking/imgui.h"
#include "../../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../../src/Objects/GameObject.h"
#include "../../src/Components/Renderers/MeshRenderer.h"
#include "../../src/Assets/Mesh.h"
using namespace std;

struct Details {
    unordered_map<string, void(*)(GameObject*)> buttonToComponent;
    bool showMap = false;
    Details();
    void window(GameObject*);
    void addComponent(GameObject*);
    void transform(Transform* transform);
};

#endif