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
)

set(SCENE_SRC
    src/Scenes/Scene.cpp
)

# -------------------------------
# ImGui sources
# -------------------------------
set(IMGUI_SRC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
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
    external/imgui
    external/imgui/backends
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
