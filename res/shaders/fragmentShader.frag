#version 460 core

out vec4 fragColor; 

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texImg;

void main()
{
	//fragColor = vec4(vertexColor, 1.0f);
	fragColor = texture(texImg, texCoord);
}