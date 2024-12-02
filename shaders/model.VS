#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

uniform mat4 u_Model;
uniform mat4 u_Viewing;
uniform mat4 u_Projection;

out vec3 Normal;
out vec3 FragPos;
out vec4 Color;
void main()
{
	vec4 newPos = vec4(a_Position, 1.0f);
	gl_Position = u_Projection * u_Viewing * u_Model * newPos;
	FragPos = (u_Model * newPos).xyz;
	Normal = a_Normal;
    Color = a_Color;
}
