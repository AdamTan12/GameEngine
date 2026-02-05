#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../external/imgui-docking/imgui.h"
#include "../../external/imgui-docking/backends/imgui_impl_opengl3.h"
#include "../../external/imgui-docking/backends/imgui_impl_glfw.h"
#include <glad/glad.h>
#include "../src/Scenes/Scene.h"

struct GameWindow {
    GLuint FBO;        // framebuffer object
    GLuint RBO;        // renderbuffer object (for depth/stencil)
    GLuint texture_id; // color attachment texture
    unsigned int WIDTH = 800;
    unsigned int HEIGHT = 600;

    void window(GLuint, glm::mat4, glm::mat4);
    void create_framebuffer();
    void bind_framebuffer();
    void unbind_framebuffer();
    void rescale_framebuffer(float, float);
};
#endif