#version 330 core

in vec3 Normal;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;

out vec4 FragColor;

void main() {
    FragColor = u_LightColor;
}