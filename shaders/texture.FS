#version 330 core

struct Material {
	vec4 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material u_Material;

struct Light {
	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform Light u_Light;

in vec4 Color;
in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main()
{
	// Ambient
	// float ambientIntensity = 1.2f; // Change Light Intensity
	vec4 lightColor = u_LightColor;
	vec3 ambient = u_Light.ambient.xyz * vec3(texture(u_Material.diffuse, TexCoords));
	
	// Diffuse
	vec3 norm = normalize(Normal);
	// vec3 lightDir = normalize(u_Light.position - FragPos);
	vec3 lightDir = normalize(-u_Light.direction);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = u_Light.diffuse.xyz * diff * vec3(texture(u_Material.diffuse, TexCoords));

	// Specular
	float specularStrength = 0.9f;
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), u_Material.shininess); // Highlight's shininess : 32
	vec3 specular = u_Light.specular.xyz * spec * vec3(texture(u_Material.specular, TexCoords));

	vec3 result = ambient.xyz + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}