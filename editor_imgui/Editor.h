#ifndef EDITOR_H
#define EDITOR_H
#include "../external/imgui-docking/imgui.h"
#include "../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../src/Objects/GameObject.h"
#include "../src/Scenes/Scene.h"
#include "../src/Components/Renderers/MeshRenderer.h"
#include "../src/Components/Transform.h"
#include "../src/Assets/Mesh.h"
using namespace std;
class Editor {
    private:
        GameObject* currGameObject = nullptr;
        GLuint FBO;        // framebuffer object
        GLuint RBO;        // renderbuffer object (for depth/stencil)
        GLuint texture_id; // color attachment texture
        const unsigned int WIDTH = 800;
        const unsigned int HEIGHT = 600;
        
        void create_framebuffer();
        void bind_framebuffer();
        void unbind_framebuffer();
        void rescale_framebuffer(float, float);
    public:
        // imgui set up
        void init(GLFWwindow *);
        void startFrame();
        void render();
        void shutdown();

        void hierarchy();
        void details();
        void game(GLuint, glm::mat4, glm::mat4);
        void transform(Transform* transform);
};

#endif EDITOR_H