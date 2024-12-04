#version 330 core

in vec3 Normal;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
out vec4 FragColor;

void main() {
    vec3 asd = u_LightPos + u_ViewPos;
    FragColor = u_LightColor;
}