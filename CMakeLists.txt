cmake_minimum_required(VERSION 3.15)
project(ImGuiDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# ImGui sources
# -------------------------------
set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# Include ImGui headers
include_directories(imgui imgui/backends)

# -------------------------------
# GLFW paths
# -------------------------------
set(GLFW_INCLUDE "C:/glfw-3.4-win/include")
set(GLFW_LIB "C:/glfw-3.4-win/lib-vc2022/glfw3.lib")

include_directories(${GLFW_INCLUDE})

# -------------------------------
# Build executable
# -------------------------------
add_executable(ImGuiDemo
    imgui_demo/main.cpp
    ${IMGUI_SRC}
)

# Link GLFW and OpenGL
target_link_libraries(ImGuiDemo
    "${GLFW_LIB}"
    opengl32
)
