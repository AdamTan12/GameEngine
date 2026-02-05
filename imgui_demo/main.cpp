#include "../imgui-docking/imgui.h"
#include "../imgui-docking/backends/imgui_impl_glfw.h"
#include "../imgui-docking/backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Objects/GameObject.h"
#include "Components/Renderers/MeshRenderer.h"
#include "Assets/Mesh.h"
#include "Scenes/Scene.h"
#include "../editor_imgui/Editor.h"

// Shader loading helper functions
std::string loadShaderSource(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint compileShader(GLenum type, const std::string& src) {
    GLuint shader = glCreateShader(type);
    const char* cstr = src.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cout << "Shader compile error:\n" << info << std::endl;
    }
    return shader;
}

GLuint createShaderProgram(const std::string& vertPath, const std::string& fragPath) {
    std::string vertSrc = loadShaderSource(vertPath);
    std::string fragSrc = loadShaderSource(fragPath);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::cout << "Program link error:\n" << info << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main() {
    // ---------------- GLFW & OpenGL ----------------
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Engine + ImGui", nullptr, nullptr);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Editor* e = new Editor();
    // ---------------- ImGui ----------------
    e->init(window);
    // ---------------- Shader ----------------
    GLuint shaderProgram = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    // ---------------- Scene -----------------
    Scene* scene = new Scene();
    Scene::activeScene = scene;
    // ---------------- Mesh ----------------
    
    // ---------------- GameObject & Renderer ----------------
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0, -3));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

    int x = 0;
    // ---------------- Main Loop ----------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        e->startFrame();

        // Clear buffers
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        e->display(shaderProgram, view, projection);
        // Render ImGui on top
        e->render();
        
        glfwSwapBuffers(window);
    }

    // ---------------- Cleanup ----------------
    e->shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
