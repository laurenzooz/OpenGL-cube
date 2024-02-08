#version 460 core


in vec3 vertexColor;
in vec2 texCoord;

in vec3 normal;
in vec3 fragPos;

uniform sampler2D texImg;

uniform vec3 lightColor;
uniform float ambient;

uniform vec3 eyePos;
uniform vec3 lightPos;

uniform bool useTexture; // Wheter to use normal color or a texture

out vec4 fragColor; 

void main()
{
	if (useTexture) 
		fragColor = texture(texImg, texCoord);
	else 
		fragColor = vec4(vertexColor, 1.0f);
	
	// Lighting
	// Light direction and view direction vectors
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(eyePos - fragPos);

	float diffuse = max(dot(normal, lightDir), 0.0f); // scalar to scale the light intensity

	// specular
	float specularLight = 0.70f;	
	vec3 reflectionDir = reflect(-lightDir, normal);
	
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 15);
	float specular = specAmount * specularLight;

	// Final color of the fragment
	fragColor = fragColor * vec4(lightColor, 1.0f) * (diffuse + ambient + specular);
}