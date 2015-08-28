#version 330 core

// input vertex data, check the corresponding index in vertex array
layout(location = 0) in vec3 vertexPos_m;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNor_m;

// output data, will be interpolated for each fragment
out vec2 UV;
out vec3 vertexPos_w;
out vec3 vertexNor_c;
out vec3 eyeDir_c;
out vec3 lightDir_c; 

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPos_w;


void main() {
	// position of vertex in clip space
	gl_Position = MVP * vec4(vertexPos_m, 1);
	
	// position of the vertex in world space
	vertexPos_w = ( M * vec4(vertexPos_m, 1) ).xyz;
	
	// vector that goes from the vertex to the camera in camera space
	// In camera space, the camera is at (0, 0, 0)
	vec3 vertexPos_c = ( V * M * vec4(vertexPos_m, 1) ).xyz;
	eyeDir_c = vec3(0, 0, 0) - vertexPos_c;
	
	// vector that goes from the vertex to the light in camera space
	// M is omitted because it's identical
	vec3 lightPos_c = ( V * vec4(lightPos_w, 1) ).xyz;
	lightDir_c = lightPos_c + eyeDir_c;
	
	// normal of the vertex in camera space
	// Only correct if ModelMatrix does not scale the model! 
	// Use its inverse transpose if not.
	vertexNor_c = ( V * M * vec4(vertexNor_m, 0) ).xyz;
	
	// UV of the vertex, no space property
	UV = vertexUV;	
}