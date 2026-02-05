#ifndef EDITOR_H
#define EDITOR_H
#include <unordered_map>
#include <string>
#include "../external/imgui-docking/imgui.h"
#include "../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../external/imgui-docking/backends/imgui_impl_glfw.h"

#include "Details/Details.h"
#include "GameWindow/GameWindow.h"
#include "Hierarchy/Hierarchy.h"

using namespace std;
class Editor {
    public:
        Editor();
        Details details;
        GameWindow gameWindow;
        Hierarchy hier;
        // imgui set up
        void init(GLFWwindow *);
        void startFrame();
        void render();
        void shutdown();

        void display(GLuint, glm::mat4, glm::mat4);
};

#endif EDITOR_H