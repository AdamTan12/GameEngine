#ifndef HIERARCHY_H
#define HIERARCHY_H
#include "../../external/imgui-docking/imgui.h"
#include "../../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../../src/Objects/GameObject.h"

struct Hierarchy {
    GameObject* currGameObject = nullptr;
    void window();
    GameObject* getSelectedGameObject();
};

#endif