#version 330 core

in vec4 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 u_MeshColor;
uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main()
{
	// Ambient
	float ambientIntensity = 0.8f; // Change Light Intensity
	vec4 lightColor = u_LightColor;
	vec4 ambient = ambientIntensity * lightColor;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = diff * lightColor.xyz;

	// Specular
	float specularStrength = 0.9f;
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), 32); // Highlight's shininess : 32
	vec3 specular = specularStrength * spec * lightColor.xyz;

	vec3 result = (ambient.xyz + diffuse + specular) * u_MeshColor.xyz;
	FragColor = vec4(result, 1.0f);
}