#include "editor.h"

Editor::Editor() {
    hier = Hierarchy();
    details = Details();
    gameWindow = GameWindow();
    project = Project();
}
void Editor::display(GLuint shaderProgram, glm::mat4 view, glm::mat4 projection) {
    hier.window();
    details.window(hier.getSelectedGameObject());
    gameWindow.window(shaderProgram, view, projection);
    project.window();
}

void Editor::init(GLFWwindow * window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //ImFont* font_normal = io.Fonts->AddFontFromFileTTF("path/to/your/font.ttf", 18.0f);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    gameWindow.create_framebuffer();
}
void Editor::startFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Editor::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Editor::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
