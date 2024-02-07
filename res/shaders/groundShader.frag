#version 460 core

out vec4 fragColor; 

uniform vec3 lightColor;


void main()
{
	fragColor = vec4(0.5f, 0.4f, 0.3f, 1.0f) * vec4(lightColor, 1.0f);
}