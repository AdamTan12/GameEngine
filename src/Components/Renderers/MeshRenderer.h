#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "../Assets/Mesh.h"
#include "Component.h"

using namespace std;

class Object; //forward declaration
/**
 * @brief Inherits from Component.
 * 
 * this component renders meshes in the game world.
 */
struct MeshRenderer : public Component {
    /**
     * @brief VBO stores vertex data (positions, vertices...).
     * 
     * VAO stores the configuration of vertex attribute pointers.
     */
    GLuint VBO, VAO, EBO;
    /**
     * @brief Pointer to the mesh to draw.
     */
    Mesh *mesh = nullptr;
    /**
     * @brief Default constructor.
     */
    MeshRenderer();
    /**
     * @brief Constructs a MeshRenderer
     * 
     * Sets gameObject to gameObject.
     * 
     * Sets transform to gameObject's transform.
     * 
     * @param gameObject Object this MeshRenderer is attached to.
     */
    MeshRenderer(Object* gameObject);
    /**
     * @brief Renders the mesh that *mesh points to.
     * @param shader The shader that is used for rendering.
     */
    void Draw(GLuint shader);
    /**
     * @brief Sets the mesh to render.
     * @param mesh The mesh to render.
     */
    void setMesh(Mesh *mesh);
};
#endif