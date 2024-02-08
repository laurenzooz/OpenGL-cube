#version 460 core


in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform float ambient;

uniform vec3 eyePos;
uniform vec3 lightPos;

out vec4 fragColor; 


void main()
{
	// Light direction and view direction vectors
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(eyePos - fragPos);

	float diffuse = max(dot(normal, lightDir), 0.0f);

	// specular
	float specularLight = 0.20f;	
	vec3 reflectionDir = reflect(-lightDir, normal);
	
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 5);
	float specular = specAmount * specularLight;
	
	fragColor = vec4(0.5f, 0.4f, 0.3f, 1.0f) * vec4(lightColor, 1.0f) * (diffuse + ambient + specular);
}