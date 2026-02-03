#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_model;
uniform mat4 u_perspective;
uniform mat4 u_view;

void main() {
    vec4 newPosition = u_perspective * u_view * u_model * vec4(position, 1.0);
    gl_Position = newPosition;
}