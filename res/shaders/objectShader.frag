#version 460 core

out vec4 fragColor; 

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texImg;

uniform vec3 lightColor;

uniform bool useTexture; // Wheter to use normal color or a texture

void main()
{
	if (useTexture) 
		fragColor = texture(texImg, texCoord);
	else 
		fragColor = vec4(vertexColor, 1.0f);
	
	fragColor = fragColor * vec4(lightColor, 1.0f);
}