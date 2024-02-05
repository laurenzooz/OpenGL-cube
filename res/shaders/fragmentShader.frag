#version 460 core
// determine the open gl shader language version

out vec4 fragColor; 

in vec4 vertexColor;



void main()
{
	
	//fragColor = vertexColor; // RGBa, skaalattu 0..1 välille	
	fragColor = vec4(0, 0, 1, 1);

}