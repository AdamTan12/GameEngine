#include "editor.h"
//forward dec
void addMeshRenderer(GameObject* currGameObject);

Editor::Editor() {
    buttonToComponent["MeshRenderer"] = addMeshRenderer;
}
void addMeshRenderer(GameObject* currGameObject) {
    Mesh* mesh = new Mesh();
    currGameObject->AddComponent<MeshRenderer>()->setMesh(mesh);
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
    create_framebuffer();
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
void Editor::hierarchy() {
    ImGui::Begin("Hierarchy");
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Add New GameObject")) {
            GameObject* go = new GameObject();
            //go->AddComponent<MeshRenderer>()->setMesh(new Mesh());
        }
        ImGui::EndPopup();
    }
    for (GameObject* go : Scene::activeScene->objects) {
        bool isSelected = go == currGameObject;
        if (ImGui::Selectable(go->name.c_str(), isSelected)) {
            currGameObject = go;
        }
    }
    ImGui::End();
}
void Editor::details() {
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
    addComponent();
    ImGui::End();
}
void Editor::game(GLuint shaderProgram, glm::mat4 view, glm::mat4 projection) {
    ImGui::Begin("Game");
    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;
    ImVec2 pos = ImGui::GetCursorScreenPos();
    bind_framebuffer();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    GLint viewLoc = glGetUniformLocation(shaderProgram, "u_view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "u_perspective");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    Scene::activeScene->updateRenderers(shaderProgram);
    unbind_framebuffer();
    ImGui::GetWindowDrawList()->AddImage(
        (void *)texture_id, 
        ImVec2(pos.x, pos.y), 
        ImVec2(pos.x + window_width, pos.y + window_height), 
        ImVec2(0, 1), 
        ImVec2(1, 0)
    );
    ImGui::End();
}
void Editor::transform(Transform* transform) {
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
void Editor::addComponent() {
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


void Editor::create_framebuffer()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

// here we bind our framebuffer
void Editor::bind_framebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

// here we unbind our framebuffer
void Editor::unbind_framebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// and we rescale the buffer, so we're able to resize the window
void Editor::rescale_framebuffer(float width, float height)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}