#ifndef PROJECT_H
#define PROJECT_H
#include "../../external/imgui-docking/imgui.h"
#include "../../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../../src/Assets/Assets.h"

struct Project {
    Assets assets;
    Project();
    void window();
};
#endif
