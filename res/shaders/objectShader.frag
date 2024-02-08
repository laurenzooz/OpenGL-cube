#version 460 core


in vec3 vertexColor;
in vec2 texCoord;

in vec3 vertexNormal;
in vec3 lightDir;

uniform sampler2D texImg;

uniform vec3 lightColor;
uniform float ambient;

uniform bool useTexture; // Wheter to use normal color or a texture

out vec4 fragColor; 

void main()
{
	if (useTexture) 
		fragColor = texture(texImg, texCoord);
	else 
		fragColor = vec4(vertexColor, 1.0f);
	

	float diffuse = max(dot(vertexNormal, lightDir), 0.0f); // scalar to scale the light intensity

	fragColor = fragColor * vec4(lightColor, 1.0f) * (diffuse + ambient);
}