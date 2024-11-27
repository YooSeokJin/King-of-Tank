#version 330 core

// 어트리뷰트 인
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

// 유니폼 값

uniform mat4 u_Model;
uniform mat4 u_Viewing;
uniform mat4 u_Projection;


void main()
{
	vec4 newPos = vec4(a_Position, 1.0f);
	gl_Position = u_Projection * u_Viewing * u_Model * newPos;
}
