cmake_minimum_required(VERSION 3.15)
project(ImGuiDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Engine source files
# -------------------------------
set(COMPONENT_SRC
    src/Components/Component.cpp
    src/Components/Transform.cpp
    src/Components/Renderers/MeshRenderer.cpp
)

set(OBJECT_SRC
    src/Objects/GameObject.cpp
)

set(ASSET_SRC
    src/Assets/Mesh.cpp
    src/Assets/Assets.cpp
)

set(SCENE_SRC
    src/Scenes/Scene.cpp
)
set (EDITOR_SRC
    editor_imgui/editor.cpp
    editor_imgui/Details/Details.cpp
    editor_imgui/Hierarchy/Hierarchy.cpp
    editor_imgui/GameWindow/GameWindow.cpp
    editor_imgui/Project/Project.cpp           
)

# -------------------------------
# ImGui sources
# -------------------------------
set(IMGUI_SRC
    external/imgui-docking/imgui.cpp
    external/imgui-docking/imgui_draw.cpp
    external/imgui-docking/imgui_widgets.cpp
    external/imgui-docking/imgui_tables.cpp
    external/imgui-docking/backends/imgui_impl_glfw.cpp
    external/imgui-docking/backends/imgui_impl_opengl3.cpp
)

# -------------------------------
# GLAD
# -------------------------------
set(GLAD_SRC
    external/glad/src/glad.c
)
set(GLAD_INCLUDE
    external/glad/include
)

# -------------------------------
# GLFW
# -------------------------------
set(GLFW_INCLUDE
    external/glfw-3.4-win/include
)
set(GLFW_LIB
    ../external/glfw-3.4-win/lib-vc2022/glfw3
)

# -------------------------------
# GLM
# -------------------------------
set(GLM_INCLUDE
    external/glm-1.0.1
)

# -------------------------------
# Include directories
# -------------------------------
include_directories(
    src
    external/imgui-docking
    external/imgui-docking/backends
    ${GLAD_INCLUDE}
    ${GLFW_INCLUDE}
    ${GLM_INCLUDE}
)

# -------------------------------
# Build executable
# -------------------------------
add_executable(ImGuiDemo
    imgui_demo/main.cpp
    #main.cpp
    ${COMPONENT_SRC}
    ${OBJECT_SRC}
    ${ASSET_SRC}
    ${SCENE_SRC}
    ${EDITOR_SRC}
    ${IMGUI_SRC}
    ${GLAD_SRC}
)

# -------------------------------
# Link libraries
# -------------------------------
target_link_libraries(ImGuiDemo
    "${GLFW_LIB}"
    opengl32
)
