#version 330 core
uniform vec3 uColor;
out vec4 FragColor;

void main() {
    // Blink bright red so you can’t miss it
    FragColor = vec4(uColor, 1.0);
}
