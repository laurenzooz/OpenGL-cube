#version 460 core


in vec3 vertexNormal;
in vec3 eyePos;

uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 fragColor; 


void main()
{
	vec3 lightDir = normalize(lightPos - eyePos);

	float diffuse = max(dot(normalize(vertexNormal), lightDir), 0.0f); // scalar to scale the light intensity
	

	fragColor = vec4(0.5f, 0.4f, 0.3f, 1.0f) * vec4(lightColor, 1.0f) * diffuse;
}