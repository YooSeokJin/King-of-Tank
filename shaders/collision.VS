#version 330 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_Viewing;
uniform mat4 u_Projection;

out vec4 v_Color;

void main()
{
	vec4 newPos = vec4(a_Position, 1.0f);
	gl_Position = u_Projection * u_Viewing * u_Model * newPos; 
}