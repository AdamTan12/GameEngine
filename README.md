# GameEngine
refactoring my game engine!

# Custom Game Engine

A lightweight, component-based 3D game engine built in C++ using OpenGL, designed to support flexible scene composition and modular game objects.

## Features

- **Component-Based Architecture**  
  Reusable modules such as `MeshRenderer`, `MeshCollider`, and `Transform` allow flexible attachment to game objects.

- **Mesh Rendering**  
  Supports loading and rendering 3D meshes with vertex buffers and element buffers.

- **Collision Detection**  
  Implements SAT (Separating Axis Theorem) for precise collision detection between convex meshes.

- **Transform System**  
  Hierarchical transforms with support for position, rotation (quaternion), and scaling. Supports parent-child relationships.

- **Modularity & Reusability**  
  Components can be attached or removed from game objects at runtime for flexible behavior composition.

- **World & Local Space Handling**  
  Vertices, edges, and normals properly transformed from local to world space for rendering and physics.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/custom-game-engine.git
    ```
2. You do not need OpenGL, GLFW, GLAD, and GLM installed since all required files are in the external folder.
3. Compile the engine using g++ and cmake:
    ```bash
    mkdir build
    cd build
    cmake --build .
    ./Debug/ImGuiDemo.exe
    ```
