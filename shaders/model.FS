#version 330 core

in vec3 Normal; // VS에서 Normal값

out vec4 FragColor;

uniform vec4 u_MeshColor;
uniform vec4 u_LightColor;
void main()
{
	// 조명
	float ambientIntensity = 0.7f; // 빛의 강도를 바꿔보다!
	vec4 lightColor = u_LightColor;
	vec4 ambient = ambientIntensity * lightColor;

	vec4 result = ambient * u_MeshColor;
	FragColor = result;
	// FragColor = u_ObjectColor;
}