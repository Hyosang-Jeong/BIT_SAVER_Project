#version 450 core
layout (location = 0) in vec2 vVertexPosition;

uniform mat3 uModelToNDC;

void main() 
{
	gl_Position = vec4(vec2(uModelToNDC * vec3(vVertexPosition, 1.f)), 0.0,
	1.0);
}