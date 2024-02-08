#version 460 core


in vec3 vertexNormal;
in vec3 lightDir;

uniform vec3 lightColor;

out vec4 fragColor; 


void main()
{
	float diffuse = max(dot(vertexNormal, lightDir), 0.0f); // scalar to scale the light intensity
	float ambient = 0.10f;

	fragColor = vec4(0.5f, 0.4f, 0.3f, 1.0f) * vec4(lightColor, 1.0f) * (diffuse + ambient);
}